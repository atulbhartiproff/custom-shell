#include "exec_handler.hpp"
#include "type_handler.hpp"
#include "echo_handler.hpp"
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>

// Helper function to append current directory to PATH if not present
void ensure_current_dir_in_path() {
    char* current_path = std::getenv("PATH");
    std::string new_path = current_path ? std::string(current_path) : "";

    // In POSIX PATH strings, adding a colon followed by nothing, or a dot '.'
    // tells the environment to look in the current working directory.
    if (new_path.empty()) {
        new_path = ".";
    } else if (new_path.find_first_of('.') == std::string::npos) {
        new_path += ":.";
    }

    // Overwrite the PATH environment variable for this process and its children
    setenv("PATH", new_path.c_str(), 1);
}

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // Ensure fallback path includes current directory before running commands
  ensure_current_dir_in_path();

  std::string line;
  std::string command;

  while (true) {
    std::cout << "$ ";
    command.clear();
    std::getline(std::cin, line);
    std::stringstream ss(line);
    ss >> command;
    if(command.size()==0) continue;

    // Quick guard fix: 'pwd' or 'cd' are less than 4 chars but valid!
    // Let's remove the rigid < 4 size block to allow commands like 'pwd', 'cd', 'ls'

    // EXIT COMMAND - Exits the shell
    if (command == "exit")
      break;

    // ECHO COMMAND - Repeats the proceeding input [calls echo_Handler]
    else if (command == "echo") {
      if(echoHandle(line)==1) continue;
    }

    // TYPE COMMAND - Validates if the proceeding input is a valid command.
    else if (command == "type") {
      bool found = false;
      std::string potentialcommand;
      std::vector<std::string> knownCom = {"type", "echo", "exit", "pwd", "cd"};
      ss >> potentialcommand;

      for (size_t i = 0; i < knownCom.size(); i++) {
        if (potentialcommand == knownCom[i]) {
          std::cout << potentialcommand << " is a shell builtin" << std::endl;
          found = true;
          break;
        }
      }

      if (!found) {
        if (typeCom(line) == -1) {
          std::cout << potentialcommand << ": not found" << std::endl;
        }
      }
    } else if (command == "pwd") {
      // Clean cross-platform replacement for get_current_dir_name() if needed
      char cwd[1024];
      if (getcwd(cwd, sizeof(cwd)) != nullptr) {
          std::cout << cwd << std::endl;
        }
    }

    else if (command == "cd") {
      std::string targetDir;
      ss >> targetDir;
      if (targetDir == "~") {
        std::string homeDir = std::getenv("HOME");
        targetDir = homeDir;
      }
      if (chdir(targetDir.c_str()) != 0) {
        std::cout << "cd: " << targetDir << ": No such file or directory"
                  << std::endl;
      }
    }
    // External executables evaluation
    else {
      if (executeCom(line) == -1) {
        std::cout << command << ": command not found" << std::endl;
      }
    };
  }
}
