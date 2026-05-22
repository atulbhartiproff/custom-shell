#include <iostream>
#include <sstream>
#include <string>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::string line;
  std::string command;

  while (true) {
    std::cout << "$ ";

    std::getline(std::cin, line);
    std::stringstream ss(line);
    ss>>command;

    if (command == "exit")
      break;

    else if (command == "echo") {
      std::string word;
      while(ss>>word)
      {
          std::cout<<word<<" ";
      }
      std::cout<<std::endl;
    }

    else if (command == "type") {
        std::string potentialcommand;
        ss>>potentialcommand;
      if (potentialcommand == "echo" || potentialcommand == "exit" || potentialcommand == "type")
          std::cout << potentialcommand << " is a shell builtin" << std::endl;
      else
        std::cout << potentialcommand << ": not found" << std::endl;
    } else
      std::cout << command << ": command not found" << std::endl;
  }
}
