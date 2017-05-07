#ifndef DFA_H
#define DFA_H

#include <vector>
#include "dfa_state.h"

class DFA {
  public:
    DFA() {};

    void set_marked(int index);
    void set_state(int index, DFAState* state);

    void set_final_states(std::vector<int> final_states);

    void add_transition(int current, char symbol, int next);

    std::vector<char> get_alphabet();
    void set_alphabet(std::vector<char> alphabet);
    std::map<int, DFAState*> get_transition_table();
    void show_transition_table();

    int state_listed(std::vector<int> state);
    int state_unmarked();

    std::map<std::string, int> get_reduced_table();
    void reduce_table();
    void print_reduced_table();

    bool is_word_valid(std::string word);
    bool is_final_state(int state);

  private:
    std::vector<int> states;
    std::vector<int> final_states;
    std::vector<char> alphabet;
    std::map<int, DFAState*> transition_table;
    std::map<std::string, int> reduced_table;
    void add_transition(std::string key, int next);

};

#endif // DFA_H
