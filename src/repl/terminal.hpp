#pragma once

#include <optional>
#include <string>

#ifndef _WIN32
#include <termios.h>
#endif

namespace repl {

bool terminal_is_interactive();

class RawTerminal {
public:
  RawTerminal();
  ~RawTerminal();

  RawTerminal(const RawTerminal &) = delete;
  RawTerminal &operator=(const RawTerminal &) = delete;

  [[nodiscard]] bool enabled() const { return enabled_; }

private:
  bool enabled_ = false;
#ifndef _WIN32
  int fd_ = -1;
  struct termios original_state_;
#endif
};

std::optional<std::string> read_line(bool raw_mode = false);

} // namespace repl
