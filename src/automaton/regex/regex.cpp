
#include <vector>
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

void print_nfa_vec(std::vector<NFA*> v) {
  std::cout << "Operands:\n";
  std::cout << "=========================\n";
  for (auto elem : v) {
    std::cout << *elem << std::endl;
  }
  std::cout << "=========================\n\n";
}

void print_char_vec(std::vector<char> v) {
  std::cout << "Operators:\n";
  std::cout << "=========================\n";
  for (char elem : v) {
    std::cout << elem << std::endl;
  }
  std::cout << "=========================\n\n";
}

NFA* Regex::compile_regex() {
  std::vector<NFA*> operands;
  std::vector<char> operators;

  NFA* new_nfa;
  std::vector<int> fs;

  for(char symbol : this->get_raw()) {
    print_nfa_vec(operands);
    print_char_vec(operators);

    std::cout << symbol << '\n';
    switch (symbol) {
      case '(':
      case '.':
      case '|':
        // std::cout << "back: " << *operands.back();
        operators.push_back(symbol);
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
              std::cout << "op2: " << *operand2 << '\n';
              operands.pop_back();
              operand1 = operands.back();
              operands.pop_back();
              // std::cout<<"\n*****\t*****\t*****\n";
              // std::cout << *res;
              // std::cout<<"\n*****\t*****\t*****\n";
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
        std::cout << "Push: " << '\n';
        std::cout<<"\n***************\n";
        std::cout << *operands.back();
        std::cout<<"\n***************\n";
      }
      break;
    }
  }
  std::cout << *operands.back() << std::endl;

  return operands.back();
};

NFA* Regex::concat(NFA* a, NFA* b) {
  NFA* result = new NFA();
  std::cout<<"\n***************\n";
  std::cout << *a;
  std::cout << *b;
  std::cout<<"\n***************\n";

  int state_count = a->get_state_count() + b->get_state_count();
  result->set_states(state_count);

  result->append_transitions(a->get_transitions());

  // state, letter, next
  for (int state : a->get_final_states()) {
    result->add_transition(state, LAMBDA, a->get_state_count());
  }

  // Add transitions to the final states
  for(auto transition: b->get_transitions()) {
    // state, letter, next
    result->add_transition(
      transition->current + a->get_state_count(),
      transition->symbol,
      transition->next + a->get_state_count()
    );
  }

  // Set the final state
  std::vector<int> final_state = {a->get_state_count() + b->get_state_count() - 1};
  result->set_final_states(final_state);

  return result;
}

NFA* kleene(NFA* a) {
  NFA* res = new NFA();

  return res;
}

NFA* Regex::or_operator(nfa_vec opts, int no_of_selections) {
  NFA* result = new NFA();
  int state_count = 2;

  for(NFA* option : opts) {
    state_count += option->get_state_count();
  }

  std::cout << "state_count: " << state_count << '\n';
  result->set_states(state_count);

  int adder_track = 1;

  for(NFA* option : opts) {
    std::cout << "adder_track: " << adder_track << '\n';
    result->add_transition(0, LAMBDA, adder_track);
    std::cout << "+++++++++++++++++++++++++" << '\n';
    for(auto transition: result->get_transitions()) {
      std::cout << *transition;
    }
    std::cout << "+++++++++++++++++++++++++" << '\n';

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
