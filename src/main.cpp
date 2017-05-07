
#include "automaton/nfa.h"
#include "automaton/dfa.h"
#include "automaton/regex/regex.h"

// void nfa_func();
// void nfa_lets();
void regex_func();

int main(int argc, char const *argv[]) {
  regex_func();

  return 0;
}

void regex_func() {
  // Regex* regex = new Regex("(a.b.c)");
  // NFA* nfa =  regex->compile_regex();

  std::string regex;
  std::cout << "Enter the regex: ";
  std::cin >> regex;
  Regex* regex_or = new Regex(regex);
  NFA* nfa_or = regex_or->compile_regex();
  // std::cout << "===============================\n";
  // std::cout << *nfa_or;
  // nfa_or->show_transition_table();

  DFA* dfa = nfa_or->to_dfa();

  while (true) {
    std::cout << "\n\nEnter the word to test: ";
    std::cin >> regex;
    std::cout << regex << ": " << dfa->is_word_valid(regex);
  }
 /* std::cout << "a: " << dfa->is_word_valid("a") << std::endl;
  std::cout << "b: " << dfa->is_word_valid("b") << std::endl;
  std::cout << "c: " << dfa->is_word_valid("c") << std::endl;
  std::cout << "ab: " << dfa->is_word_valid("ab") << std::endl;
  std::cout << "ca: " << dfa->is_word_valid("ca") << std::endl;
  std::cout << "cb: " << dfa->is_word_valid("cb") << std::endl;
  std::cout << "cc: " << dfa->is_word_valid("cc") << std::endl;*/
}
/*
void nfa_lets() {
  NFA *nfa = new NFA();

  std::vector<int> final_states;
  final_states = {2, 3};

  std::vector<char> alphabet;
  alphabet = {'a', 'b', 'c'};

  nfa->set_states(4);
  nfa->set_final_states(final_states);
  nfa->set_alphabet(alphabet);

  nfa->add_transition(0, 'a', 1);

  nfa->add_transition(1, 'b', 2);
  nfa->add_transition(1, 'c', 3);

  std::cout << "With nfa:" << std::endl;
  std::cout << *nfa << std::endl << std::endl;

  // std::cout << "ab: " << nfa->is_word_valid("ab") << std::endl;
  // std::cout << "ac: " << nfa->is_word_valid("ac") << std::endl;
  // std::cout << "abc: " << nfa->is_word_valid("abc") << std::endl;
  // std::cout << "aa: " << nfa->is_word_valid("aa") << std::endl;
}


void nfa_func() {
  NFA *nfa = new NFA();

  // std::vector<std::string> states;
  // states  = {0, 1, 2};

  std::vector<int> final_states;
  final_states  = {2};

  std::vector<std::string> alphabet;
  alphabet = {"0", "1"};

  nfa->set_states(3);
  nfa->set_final_states(final_states);
  nfa->set_alphabet(alphabet);

  nfa->add_transition(0, "0", 0);
  nfa->add_transition(0, "1", 1);

  nfa->add_transition(1, "0", 2);
  nfa->add_transition(1, "1", 1);

  nfa->add_transition(2, "0", 2);
  nfa->add_transition(2, "1", 1);

  std::cout << "With nfa:" << std::endl;
  std::cout << *nfa << std::endl << std::endl;

  std::cout << nfa->is_word_valid("0110") << std::endl;
}
*/
