
#ifndef NFA_H
#define NFA_H

#include <string>
#include <map>
#include <vector>
#include <iostream>

#include "nfa_transition.hpp"

#define LAMBDA '^'

typedef std::vector<NFATransition*> trans_vec;

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
    void set_final_state(int final_state);
    bool is_final_state(int state);

    // Alphabet
    std::vector<char> get_alphabet();
    void set_alphabet(std::vector<char> alphabet);

    // Transitions
    void add_transition(int state, char letter, int next);
    void append_transitions(trans_vec transitions);
    trans_vec get_transitions();
    void reset_transition_table();

    // Overwrites
    friend std::ostream& operator<<(std::ostream& os, const NFA& nfa);

  private:
    std::vector<int> states;
    std::vector<int> final_states;
    std::vector<char> alphabet;
    trans_vec transitions;
};

#endif // NFA_H
