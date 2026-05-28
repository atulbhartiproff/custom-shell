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

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::string line;
  std::string command;

  while (true) {
    std::cout << "$ ";
    command.clear();
    std::getline(std::cin, line);
    std::stringstream ss(line);
    ss >> command;
    if(command.size()==0) continue;
    if(command.size()<4)
    {
        std::cout<<"Invalid Command"<<std::endl;
        continue;
    }
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
      std::vector<std::string> knownCom = {"type", "echo", "exit", "pwd"};
      ss >> potentialcommand;

      for (int i = 0; i < knownCom.size(); i++) {
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
      std::cout << get_current_dir_name() << std::endl;
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
    // Invalid parameter
    else {
      if (executeCom(line) == -1) {
        std::cout << command << ": command not found" << std::endl;
      }
    };
  }
}
