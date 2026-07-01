#include "repl/terminal.hpp"

#include <iostream>
#include <string>

#ifndef _WIN32
#include <termios.h>
#include <unistd.h>
#endif

namespace repl {

bool terminal_is_interactive() {
#ifndef _WIN32
  return isatty(STDIN_FILENO) != 0;
#else
  return false;
#endif
}

RawTerminal::RawTerminal() {
#ifndef _WIN32
  if (!terminal_is_interactive()) {
    return;
  }

  fd_ = STDIN_FILENO;
  if (tcgetattr(fd_, &original_state_) != 0) {
    return;
  }

  termios raw = original_state_;
  raw.c_lflag &= static_cast<tcflag_t>(~(ICANON | ECHO));
  raw.c_cc[VMIN] = 1;
  raw.c_cc[VTIME] = 0;

  if (tcsetattr(fd_, TCSAFLUSH, &raw) == 0) {
    enabled_ = true;
  }
#endif
}

RawTerminal::~RawTerminal() {
#ifndef _WIN32
  if (enabled_) {
    tcsetattr(fd_, TCSAFLUSH, &original_state_);
  }
#endif
}

namespace {

void write_prompt() { std::cout << "$ "; }

#ifndef _WIN32
std::optional<std::string> read_line_raw() {
  std::string line;
  char byte = 0;

  while (read(STDIN_FILENO, &byte, 1) == 1) {
    if (byte == '\r' || byte == '\n') {
      write(STDOUT_FILENO, "\r\n", 2);
      return line;
    }

    if (byte == static_cast<char>(127) || byte == static_cast<char>(8)) {
      if (!line.empty()) {
        line.pop_back();
        write(STDOUT_FILENO, "\b \b", 3);
      }
      continue;
    }

    if (byte == 3) {
      write(STDOUT_FILENO, "^C\r\n", 4);
      return std::string{};
    }

    if (byte == 4 && line.empty()) {
      return std::nullopt;
    }

    line.push_back(byte);
    write(STDOUT_FILENO, &byte, 1);
  }

  return std::nullopt;
}
#endif

std::optional<std::string> read_line_buffered() {
  std::string line;
  if (!std::getline(std::cin, line)) {
    return std::nullopt;
  }
  return line;
}

} // namespace

std::optional<std::string> read_line(bool raw_mode) {
  write_prompt();

#ifndef _WIN32
  if (raw_mode) {
    return read_line_raw();
  }
#endif

  return read_line_buffered();
}

} // namespace repl
