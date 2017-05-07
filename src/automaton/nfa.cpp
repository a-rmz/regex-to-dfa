
#include "nfa.h"
#include <algorithm>
#include <numeric>

/**
  * Constructor
  */
NFA::NFA() {}

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

/**
  * Setter: States
  */
void NFA::set_states(std::vector<int> states) {
  this->states = states;
};

void NFA::set_states(int number) {
  std::vector<int> v(number);
  std::iota(v.begin(), v.end(), 0);
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
  * Check if a given state is a final state
  */
bool NFA::is_final_state(int state) {
  // If the iterator returned is different to the end,
  // a final state was found
  return std::find(
    this->final_states.begin(),
    this->final_states.end(),
    state
  ) != this->final_states.end();
};

/**
  * Add a new transition to the transition table. This is the most important
  * part of the NFA, this is what creates the transition table which determines
  * the value of a word.
  *
  */
void NFA::add_transition(int state, char letter, int next) {
  NFATransition* t = new NFATransition(state, letter, next);
  this->transitions.push_back(t);
}

void NFA::append_transitions(trans_vec transitions) {
  this->transitions.insert(this->transitions.end(), transitions.begin(), transitions.end());
}

/**
  * Clears the content of the transition table
  */
void NFA::reset_transition_table() {
  this->transitions.clear();
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
