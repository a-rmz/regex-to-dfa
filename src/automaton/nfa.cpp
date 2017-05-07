
#include "nfa.h"
#include <algorithm>
#include <unordered_map>
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
std::vector<std::string> NFA::get_alphabet() {
  return this->alphabet;
};

/**
  * Getter: Transition table
  */
std::unordered_map<std::string, int> NFA::get_transitions() {
  return this->state_transition_table;
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

/**
  * Setter: alphabet
  */
void NFA::set_alphabet(std::vector<std::string> alphabet) {
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
void NFA::add_transition(int state, std::string letter, int next) {
  // Create the key concatenating the current state and the current letter
  std::string key = std::to_string(state) + letter;
  // Add the key to the table with the next state as value
  this->state_transition_table[key] = next;
}

/**
  * Append transitions from one table to self's
  */
void NFA::append_transitions(std::unordered_map<std::string, int> transition_table) {
  this->state_transition_table.insert(transition_table.begin(), transition_table.end());
}

/**
  * Clears the content of the transition table
  */
void NFA::reset_transition_table() {
  this->state_transition_table.clear();
}

/**
  * Determines if a given word is valid for the NFA.
  * Iterates through the characters of the word, and swipes
  * the transition table going from one state to the next concatenating
  * the consumed char with the state retreived from the transition table.
  *
  * Lastly, checks if the last retreived state is a final state.
  */
bool NFA::is_word_valid(std::string word) {
  // Set the first state
  int current_state = 0;

  // Iterate through the word
  for(int i = 0; i < word.length(); i++) {
    // Get the current char (as string)
    std::string current_char = std::string(1, word.at(i));
    // Create the key of the current state
    std::string current_key = std::to_string(current_state) + current_char;
    // Retreive the next state from the transition table
    current_state = this->state_transition_table[current_key];
  }

  // Return the value of the last state
  return is_final_state(current_state);
}

std::ostream& operator<<(std::ostream& os, const NFA& nfa) {
  for(auto it : nfa.state_transition_table) {
    std::string key = it.first;
    std::string state = key.substr(0, key.length() - 1);
    std::string symbol = key.substr(key.length() - 1, key.length());

    os << "q" << state << " --> " << "q" << it.second << "  symbol: " << symbol << std::endl;
	}

  os << std::endl << "The final states are:" << std::endl;
  for(auto state : nfa.final_states) {
    os << "q" << state << std::endl;
	}

  return os;
}
