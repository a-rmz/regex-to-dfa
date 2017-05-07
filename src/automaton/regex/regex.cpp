
#include "regex.h"

/**
  * Constructor
  */
Regex::Regex(std::string raw) {
  this->set_raw(raw);
};

std::string Regex::get_raw() {
  return this->raw_value;
}

void Regex::set_raw(std::string raw) {
  this->raw_value = raw;
}

/**
  * Destructor
  */
Regex::~Regex() { };

/**
  * Compile the raw regex into a NFA
  */
NFA* Regex::compile_regex() {
  std::vector<NFA*> operands;
  std::vector<char> operators;

  NFA* new_nfa;
  std::vector<int> fs;

  for(char symbol : this->get_raw()) {

    switch (symbol) {
      case '(':
      case '.':
      case '|':
        operators.push_back(symbol);
      break;
      case '*': {
        NFA* top_operand = operands.back();
        operands.pop_back();
        operands.push_back(this->kleene(top_operand));
      }
      break;
      
      case ')': {
        int operator_count = 0;
        char curr_operator = operators.back();
        if(curr_operator == '(') continue;
        // Pop all the following parens
        do {
          operators.pop_back();
          operator_count++;
        } while(operators.back() != '(');
        operators.pop_back();

        NFA* operand1;
        NFA* operand2;

        nfa_vec selections;
        switch (curr_operator) {
          case '.':
            // Iterate through the characters of the parens
            for(int i = 0; i < operator_count; i++) {
              operand2 = operands.back();
              operands.pop_back();
              operand1 = operands.back();
              operands.pop_back();
              operands.push_back(this->concat(operand1, operand2));
            }
            break;
          case '|':
            selections.assign(operator_count + 1, new NFA());
            int tracker = operator_count;

            for(int i = 0; i < operator_count + 1; i++) {
              selections.at(tracker) = operands.back();
              tracker--;
              operands.pop_back();
            }

            operands.push_back(this->or_operator(selections, operator_count + 1));
            break;
        }
      }
      break;

      default: {
        new_nfa = new NFA();
        new_nfa->set_states(2);
        new_nfa->add_transition(0, symbol, 1);
        fs = {1};
        new_nfa->set_final_states(fs);
        operands.push_back(new_nfa);
      }
      break;
    }
  }

  return operands.back();
};

NFA* Regex::concat(NFA* a, NFA* b) {
  NFA* result = new NFA();

  int state_count = a->get_state_count() + b->get_state_count();
  result->set_states(state_count);

  result->append_transitions(a->get_transitions());

  // state, letter, next
  for (int state : a->get_final_states()) {
    result->add_transition(state, LAMBDA, a->get_state_count());
  }

  // Add transitions to the final states
  for(NFATransition* transition: b->get_transitions()) {
    // state, letter, next
    result->add_transition(
      transition->current + a->get_state_count(),
      transition->symbol,
      transition->next + a->get_state_count()
    );
  }

  // Set the final state
  result->set_final_state(a->get_state_count() + b->get_state_count() - 1);

  return result;
}

NFA* Regex::kleene(NFA* a) {
  NFA* result = new NFA();

  result->set_states(2);
  result->add_transition(0, LAMBDA, 1);

  for(NFATransition* t : a->get_transitions()) {
    result->add_transition(t->current + 1, t->symbol, t->next + 1);
  }

  // Transition to last state
  result->add_transition(a->get_state_count(), LAMBDA, a->get_state_count() + 1);
  // Return with Lambda to the first state of a
  result->add_transition(a->get_state_count(), LAMBDA, 1);
  // No value found, jump to the last
  result->add_transition(0, LAMBDA, a->get_state_count() + 1);

  result->set_final_state(a->get_state_count() + 1);

  return result;
}

NFA* Regex::or_operator(nfa_vec opts, int no_of_selections) {
  NFA* result = new NFA();
  int state_count = 2;

  for(NFA* option : opts) {
    state_count += option->get_state_count();
  }

  result->set_states(state_count);

  int adder_track = 1;

  for(NFA* option : opts) {
    result->add_transition(0, LAMBDA, adder_track);

    for(auto transition: option->get_transitions()) {
      result->add_transition(transition->current + adder_track, transition->symbol, transition->next + adder_track);
    }
    adder_track += option->get_state_count();

    result->add_transition(adder_track - 1, LAMBDA, state_count - 1);
  }

  // Move the final state
  result->set_final_state(state_count - 1);

  return result;
}
