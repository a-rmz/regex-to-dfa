#ifndef NFA_TRANSITION_H
#define NFA_TRANSITION_H

class NFATransition {
  public:
    NFATransition(int curr_state, char symbol, int next_state) {
      this->curr_state = curr_state;
      this->next_state = next_state;
      this->symbol = symbol;
    };

    ~NFATransition() {};

  private:
    int curr_state;
    int next_state;
    char symbol;
}

#endif
