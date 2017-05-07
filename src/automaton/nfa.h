
#ifndef NFA_H
#define NFA_H

#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>

#include "nfa_transition.h"

#define LAMBDA "^"

class NFA {

  public:
    // Constants

    NFA();
    virtual ~NFA();
    // States
    std::vector<int> get_states();
    void set_states(std::vector<int> states);
    void set_states(int number);
    int get_state_count();

    // Final states
    std::vector<int> get_final_states();
    void set_final_states(std::vector<int> final_states);
    bool is_final_state(int state);

    // Alphabet
    std::vector<std::string> get_alphabet();
    void set_alphabet(std::vector<std::string> alphabet);

    // Transitions
    void add_transition(int state, std::string letter, int next);
    void append_transitions(std::unordered_map<std::string, int> transition_table);
    std::unordered_map<std::string, int> get_transitions();
    void reset_transition_table();

    // Methods
    bool is_word_valid(std::string word);
    bool is_letter_in_alphabet(std::string letter);

    // Overwrites
    friend std::ostream& operator<<(std::ostream& os, const NFA& nfa);

  private:
    std::vector<int> states;
    std::vector<int> final_states;
    std::vector<std::string> alphabet;
    std::unordered_map<std::string, int> state_transition_table;
    // std::vector<NFATransition> transitions;
};

#endif // NFA_H
