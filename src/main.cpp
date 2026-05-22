#include <iostream>
#include <string>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  while (true) {
    std::cout << "$ ";
    std::string command;
    std::getline(std::cin, command);
    if(command=="exit") break;
    else if(command.substr(0,5)=="echo ")
    {
        std::cout<<command.substr(5,command.size())<<std::endl;
    }
    else if(command.substr(0,5)=="type ")
    {
        std::string inp=command.substr(5,command.size());
        if(inp =="echo" || inp=="exit" || inp=="type") std::cout<<inp<<" is a shell builtin"<<std::endl;
        else std::cout<<inp<<": not found";
    }
    else
    std::cout << command << ": command not found" << std::endl;
  }
}
