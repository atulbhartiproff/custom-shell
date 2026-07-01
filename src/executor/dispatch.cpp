#include "executor/dispatch.hpp"

#include "echo_handler.hpp"
#include "exec_handler.hpp"
#include "shell/builtins.hpp"
#include "type_handler.hpp"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>

namespace {

std::string first_token(const std::string &line) {
  std::stringstream ss(line);
  std::string command;
  ss >> command;
  return command;
}

} // namespace

DispatchResult dispatch(const std::string &line) {
  const std::string command = first_token(line);
  if (command.empty()) {
    return DispatchResult::Continue;
  }

  if (command.size() < 4) {
    std::cout << "Invalid Command" << std::endl;
    return DispatchResult::Continue;
  }

  if (command == "exit") {
    return DispatchResult::Exit;
  }

  if (command == "echo") {
    std::string mutable_line = line;
    if (echoHandle(mutable_line) == 1) {
      return DispatchResult::Continue;
    }
  } else if (command == "type") {
    std::stringstream ss(line);
    std::string ignored;
    std::string potential_command;
    ss >> ignored >> potential_command;

    if (shell::is_typeable_builtin(potential_command)) {
      std::cout << potential_command << " is a shell builtin" << std::endl;
    } else {
      std::string mutable_line = line;
      if (typeCom(mutable_line) == -1) {
        std::cout << potential_command << ": not found" << std::endl;
      }
    }
  } else if (command == "pwd") {
    std::cout << get_current_dir_name() << std::endl;
  } else if (command == "cd") {
    std::stringstream ss(line);
    std::string ignored;
    std::string target_dir;
    ss >> ignored >> target_dir;

    if (target_dir == "~") {
      const char *home_dir = std::getenv("HOME");
      if (home_dir != nullptr) {
        target_dir = home_dir;
      }
    }

    if (chdir(target_dir.c_str()) != 0) {
      std::cout << "cd: " << target_dir << ": No such file or directory"
                << std::endl;
    }
  } else {
    std::string mutable_line = line;
    if (executeCom(mutable_line) == -1) {
      std::cout << command << ": command not found" << std::endl;
    }
  }

  return DispatchResult::Continue;
}
