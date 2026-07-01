#include "repl/repl.hpp"

#include <iostream>

int main() {
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  repl::run_repl();
  return 0;
}
