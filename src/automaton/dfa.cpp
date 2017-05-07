
#include "dfa.h"
#include "nfa.h"
#include <algorithm>

std::map<int, DFAState*> DFA::get_transition_table() {
  return this->transition_table;
}

void DFA::show_transition_table() {
  for(auto state : this->get_transition_table()) {
    std::cout << state.first << ":\n";
    DFAState* curr = state.second;
    std::cout << "States: ";
    for(int member : curr->states) {
      std::cout << member << " ";
    }
    std::cout << "\nTransitions:\n";
    for(auto trans: curr->transitions) {
      std::cout << trans.first << " --> " << trans.second << '\n';
    }
  }
}

void DFA::set_alphabet(std::vector<char> alphabet) {
  this->alphabet = alphabet;
}

std::vector<char> DFA::get_alphabet() {
  return this->alphabet;
}

void DFA::set_state(int index, DFAState* state) {
  this->transition_table[index] = state;
}

void DFA::set_final_states(std::vector<int> final_states) {
  this->final_states = final_states;
}

void DFA::set_marked(int index) {
  this->transition_table[index]->marked = true;
}

void DFA::add_transition(int current, char symbol, int next) {
  this->transition_table[current]->transitions[symbol] = next;
}

int DFA::state_unmarked(){
  int size = this->get_transition_table().size();
  for(int i = 0; i < size; i++){
    DFAState* current = this->get_transition_table()[i];
    if(!(current->marked)){
      return i;
    }
  }
  // When everything is marked
  return -1;
}

int DFA::state_listed(std::vector<int> state) {
  int size = this->get_transition_table().size();
  for(int i = 0; i < size; i++){
    DFAState* current = this->get_transition_table()[i];
    if(current->states == state) return i;
  }
  // State's not in the list
  return -1;
}

void DFA::reduce_table() {
  int count = this->get_transition_table().size();
  for (int i = 0; i < count; i++) {
    for (auto t : this->get_transition_table()[i]->transitions) {
      std::string key = std::to_string(i) + t.first;
      int next = t.second;
      this->add_transition(key, next);
    }
  }
}

 std::map<std::string, int> DFA::get_reduced_table() {
  return this->reduced_table;
}

void DFA::add_transition(std::string key, int next) {
  this->reduced_table[key] = next;
}

void DFA::print_reduced_table() {
  for (auto transition : this->get_reduced_table()) {
    std::cout << transition.first << "--> " << transition.second << '\n';
  }
}


/**
  * Determines if a given word is valid for the DFA.
  * Iterates through the characters of the word, and swipes
  * the transition table going from one state to the next concatenating
  * the consumed char with the state retreived from the transition table.
  *
  * Lastly, checks if the last retreived state is a final state.
  */
bool DFA::is_word_valid(std::string word) {
  // Gets the first state
  int current_state = 0;
  
  // Iterate through the word
  for(int i = 0; i < word.length(); i++) {
    // Get the current char (as string)
    char current_symbol = word.at(i);
    // Create the key of the current state
    std::string current_key = std::to_string(current_state) + current_symbol;
    // Retreive the next state from the transition table
    current_state = this->reduced_table[current_key];
  }

  // Return the value of the last state
  return is_final_state(current_state);
}

/**
  * Check if a given state is a final state
  */
bool DFA::is_final_state(int state) {
  // If the iterator returned is different to the end,
  // a final state was found
  return std::find(
    this->final_states.begin(),
    this->final_states.end(),
    state
  ) != this->final_states.end();
};