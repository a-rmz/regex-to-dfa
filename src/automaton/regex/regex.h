
#include <string>
#include <vector>
#include "../nfa.h"

typedef std::vector<NFA*> nfa_vec;

class Regex {

public:
  Regex(std::string raw);
  virtual ~Regex();
  void set_raw(std::string raw);
  std::string get_raw();
  NFA* compile_regex();

  // Operators
  NFA* concat(NFA* a, NFA* b);
  NFA* kleene(NFA* a);
  NFA* or_operator(nfa_vec opts, int operator_count);

private:
  std::string raw_value;

};
