#ifndef DFA_STATE_H
#define DFA_STATE_H

#include <map>
#include <vector>

class DFAState {
  public:
    DFAState(bool marked, std::vector<int> states, int tag) {
      this->marked = marked;
      this->states = states;
      this->tag = tag;
    };

    bool marked;
    int tag;
    std::vector<int> states;
    std::map<char, int> transitions;
};

#endif // DFA_STATE_H
