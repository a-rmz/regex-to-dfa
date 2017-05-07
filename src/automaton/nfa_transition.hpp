#ifndef NFA_TRANSITION_H
#define NFA_TRANSITION_H

class NFATransition {
  public:
    int current;
    int next;
    char symbol;
    
    NFATransition(int current, char symbol, int next) {
      this->current = current;
      this->next = next;
      this->symbol = symbol;
    };

    ~NFATransition() {};

    friend std::ostream& operator<<(std::ostream& os, const NFATransition& t) {
      os << "q" << t.current << " --" << t.symbol << "--> " << "q" << t.next << std::endl;
    }

};

#endif
