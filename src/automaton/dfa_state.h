#ifndef DFA_STATE_H
#define DFA_STATE_H

#include <vector>
#include <map>

class DFAState {
  public:
    bool marked;
    std::vector<int> states;
    std::map<char, int> moves;
};

#endif // DFA_STATE_H
