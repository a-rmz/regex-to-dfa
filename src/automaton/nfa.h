
#ifndef NFA_H
#define NFA_H

#include <string>
#include <map>
#include <vector>
#include <set>
#include <iostream>

#include "nfa_transition.hpp"
#include "dfa.h"

#define LAMBDA '^'

typedef std::vector<NFATransition*> trans_vec;
typedef std::map<int, std::map<char, std::vector<int>>> NFATransTable;

class NFA {

  public:
    // Constants

    NFA();
    virtual ~NFA();
    // States
    std::set<int> get_states();
    void set_states(std::set<int> states);
    void set_states(int number);
    int get_state_count();

    // Final states
    std::vector<int> get_final_states();
    void set_final_states(std::vector<int> final_states);
    void set_final_state(int final_state);

    // Alphabet
    std::vector<char> get_alphabet();
    void set_alphabet(std::vector<char> alphabet);

    // Transitions
    void add_transition(int state, char letter, int next);
    void append_transitions(trans_vec transitions);
    trans_vec get_transitions();
    NFATransTable get_transition_table();
    void reset_transition_table();

    // Overwrites
    friend std::ostream& operator<<(std::ostream& os, const NFA& nfa);

    // Conversion
    void show_transition_table();
    std::vector<int> eclosure(std::vector<int> state);
    std::vector<int> movements(std::vector<int> state, char symbol);
    DFA* to_dfa();


  private:
    std::set<int> states;
    std::vector<int> final_states;
    std::vector<char> alphabet;
    trans_vec transitions;
    NFATransTable transition_table;
};

#endif // NFA_H
