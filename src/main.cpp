#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unistd.h>

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

    //EXIT COMMAND - Exits the shell
    if (command == "exit")
      break;

    //ECHO COMMAND - Repeats the proceeding input
    else if (command == "echo") {
      std::string word;
      while(ss>>word)
      {
          std::cout<<word<<" ";
      }
      std::cout<<std::endl;
    }

    //TYPE COMMAND - Validates if the proceeding input is a valid command.
    else if (command == "type") {
        bool found=false;
        std::string potentialcommand;
        std::vector<std::string>knownCom={"type","echo","exit"};
        ss>>potentialcommand;


        for(int i=0;i<knownCom.size();i++)
        {
            if (potentialcommand == knownCom[i])
            {
                std::cout << potentialcommand << " is a shell builtin" << std::endl;
                found=true;
                break;
            }
        }

        if(!found)
        {
            std::string path_env = std::getenv("PATH");
            std::stringstream sp(path_env);
            std::string path;
            while(std::getline(sp,path,':'))
            {
                std::string fullPath=path+"/"+potentialcommand;
                if(access(fullPath.c_str(), X_OK)==0)
                {
                    std::cout<<potentialcommand<<" is "<<fullPath<<std::endl;
                    found=true;
                    break;
                }
            }


            if(!found)std::cout << potentialcommand << ": not found" << std::endl;
        }
    }


    //Invalid parameter
    else
    {
        bool found=false;
        std::string path_env = std::getenv("PATH");
        std::stringstream sp(path_env);
        std::string path;
        while(std::getline(sp,path,':'))
        {
            std::string fullPath=path+"/"+command;
            if(access(fullPath.c_str(), X_OK)==0)
            {
                std::vector<std::string> args;
                args.push_back(command);
                int i=0;
                while (true) {
                    if(!(ss>>args[i++])) break;
                }
                std::vector<char*> argspoint;
                for(auto& arg:args)
                {
                    argspoint.push_back(&arg[0]);
                }
                execvp(fullPath.c_str(),argspoint.data());
                found=true;
                break;
            }
        }


        if(!found)std::cout << command << ": command not found" << std::endl;
    };
  }
}
