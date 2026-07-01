#include "repl/repl.hpp"

#include "executor/dispatch.hpp"
#include "repl/terminal.hpp"

#include <iostream>

namespace repl {

void run_repl() {
  RawTerminal raw_terminal;

  while (true) {
    const auto line = read_line(raw_terminal.enabled());
    if (!line.has_value()) {
      break;
    }

    if (dispatch(*line) == DispatchResult::Exit) {
      break;
    }
  }
}

} // namespace repl
