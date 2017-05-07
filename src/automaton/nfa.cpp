
#include "nfa.h"
#include "../utils.cpp"
#include <algorithm>
#include <numeric>
#include <stack>
#include <set>

/**
  * Constructor
  */
NFA::NFA() {
  char alpha[] = "abcdefghijklmnopqrstuvwxyz";//ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::vector<char> alphabet(alpha, alpha + sizeof(alpha) - 1);
  this->set_alphabet(alphabet);
}

/**
  * Destructor
  */
NFA::~NFA() {}

/**
  * Getter: States
  */
std::vector<int> NFA::get_states() {
  return this->states;
};

/**
  * Getter: State count
  */
int NFA::get_state_count() {
  return this->states.size();
}

/**
  * Getter: Final states
  */
std::vector<int> NFA::get_final_states() {
  return this->final_states;
};

/**
  * Getter: alphabet
  */
std::vector<char> NFA::get_alphabet() {
  return this->alphabet;
};

/**
  * Getter: Transition table
  */
std::vector<NFATransition*> NFA::get_transitions() {
  return this->transitions;
}

NFATransTable NFA::get_transition_table() {
  return this->transition_table;
}

/**
  * Setter: States
  */
void NFA::set_states(std::vector<int> states) {
  this->states = states;
};

void NFA::set_states(int number) {
  std::vector<int> v(number);
  std::iota(v.begin(), v.end(), 1);
  this->states = v;
}

/**
  * Setter: Final states
  */
void NFA::set_final_states(std::vector<int> final_states) {
  this->final_states = final_states;
};

void NFA::set_final_state(int final_state) {
  std::vector<int> final_states;
  final_states = {final_state};
  this->final_states = final_states;
}

/**
  * Setter: alphabet
  */
void NFA::set_alphabet(std::vector<char> alphabet) {
  this->alphabet = alphabet;
};

/**
  * Add a new transition to the transition table. This is the most important
  * part of the NFA, this is what creates the transition table which determines
  * the value of a word.
  *
  */
void NFA::add_transition(int state, char symbol, int next) {
  NFATransition* t = new NFATransition(state, symbol, next);
  this->transition_table[state][symbol].push_back(next);
  this->transitions.push_back(t);
}

void NFA::append_transitions(trans_vec transitions) {
  this->transitions.insert(this->transitions.end(), transitions.begin(), transitions.end());
  for (NFATransition* t : transitions) {
    this->transition_table[t->current][t->symbol].push_back(t->next);
  }
}

/**
  * Clears the content of the transition table
  */
void NFA::reset_transition_table() {
  this->transitions.clear();
}

void NFA::show_transition_table() {
  for(auto stateIt : this->get_transition_table()) {
    std::cout << "{" << stateIt.first <<"}" << '\n';
    for(auto transIt : stateIt.second) {
      std::cout << transIt.first << ": [ ";
      for(int state : transIt.second) {
        std::cout << state << ' ';
      }
      std::cout << "]" << '\n';
      this->eclosure(transIt.second);
    }
  }
}

std::vector<int> NFA::eclosure(std::vector<int> state) {
  std::vector<int> eclosure;
  std::stack<int> stack;

  // Initialize the eclosure vector and the stack with the state values
  for(int s : state) {
    eclosure.push_back(s);
    stack.push(s);
  }

  while(!stack.empty()) {
    int current_state = stack.top();
    stack.pop();

    // Get all the states accessible with Lambda (Epsilon)
    std::vector<int> reachable_states = this->get_transition_table()[current_state][LAMBDA];
    for(int s : reachable_states) {
      auto inEClosure = std::find(eclosure.begin(), eclosure.end(), s);
      // If the current state wasn't found in the eclosure vector
      if(inEClosure == eclosure.end()) {
        eclosure.push_back(s);
        stack.push(s);
      }
    }
  }

  //for consistency in comparison, sort the eclosure
  std::sort(eclosure.begin(),eclosure.end());
  return eclosure;
};

/**
  * Return all the reachable states with the given symbol
  */
std::vector<int> NFA::movements(std::vector<int> state, char symbol) {
  std::set<int> movements;

  for (int s : state) {
    std::vector<int> reachable_states = this->get_transition_table()[s][symbol];
    for(int i : reachable_states) {
      movements.insert(i);
    }
  }

  std::vector<int> result (movements.begin(), movements.end());
  std::sort(result.begin(), result.end());
  // std::cout << "\nMovements:\n=-=-=-=-=-=-=-=-=\n";
  // print_vec(result);
  // std::cout << "\n=-=-=-=-=-=-=-=-=\n";
  return result;
}

/**
  * Create a new DFA based on the current NFA
  */
DFA* NFA::to_dfa() {
  DFA* dfa = new DFA();
  dfa->set_alphabet(this->get_alphabet());

  int current_dfa_state = 0;
  std::vector<int> initial_state = { 0 };
  std::vector<int> initial_eclosure = this->eclosure(initial_state);

  DFAState* s = new DFAState(false, initial_eclosure, 0);
  dfa->set_state(current_dfa_state, s);

  current_dfa_state++;

  while(dfa->state_unmarked() >= 0) {
    int state_unmarked = dfa->state_unmarked();
    dfa->set_marked(state_unmarked);

    std::cout << "States for " << state_unmarked << ":\n";
    print_vec(dfa->get_transition_table()[state_unmarked]->states);
    std::cout << "\n/-/-/-/-/-/-/-/-/-/-/\n";

    for(char symbol : dfa->get_alphabet()) {
      std::vector<int> moves = this->movements(dfa->get_transition_table()[state_unmarked]->states, symbol);
      std::vector<int> eclosure = this->eclosure(moves);

      // if (symbol == 'a' || symbol == 'b' || symbol == 'c') {
      //   std::cout << "+-+-+-+-+-+-+-+-+-+-+" << '\n';
      //   dfa->show_transition_table();
      //   std::cout << "+-+-+-+-+-+-+-+-+-+-+" << '\n';
      // }

      int next = dfa->state_listed(eclosure);
      if (next >= 0) {
        dfa->add_transition(state_unmarked, symbol, next);
      // If the EClosure tag is not empty
      } else if (!eclosure.empty()) {
        // Add the EClosure as new state
        DFAState* eclosure_state = new DFAState(false, eclosure, current_dfa_state);
        dfa->set_state(current_dfa_state, eclosure_state);
        dfa->add_transition(state_unmarked, symbol, current_dfa_state);
        current_dfa_state++;
      } else {
        dfa->add_transition(state_unmarked, symbol, -1);
      }
    }
  }

  // Set the final states
  std::set<int> nfa_final_states;
  for (int final_state : this->get_final_states()) {
    nfa_final_states.insert(final_state);
  }
  
  std::set<int>::iterator end = nfa_final_states.end();
  std::set<int> dfa_final_states;
  for (auto state: dfa->get_transition_table()) {
    DFAState* current = state.second;
    for (int s : current->states) {
      if (nfa_final_states.find(s) != end) {
        dfa_final_states.insert(current->tag);
      }
    }
  }

  std::vector<int> dfa_final_states_vec (dfa_final_states.begin(), dfa_final_states.end());
  std::sort(dfa_final_states_vec.begin(), dfa_final_states_vec.end());
  dfa->set_final_states(dfa_final_states_vec);
  dfa->reduce_table();
  return dfa;
}

std::ostream& operator<<(std::ostream& os, const NFA& nfa) {
  for(auto trans : nfa.transitions) {
    os << *trans;
	}

  os << std::endl << "The final states are:" << std::endl;
  std::cout << "{";
  for(auto state : nfa.final_states) {
    os << " q" << state << " ";
	}
  std::cout << "}" << '\n';

  return os;
}
