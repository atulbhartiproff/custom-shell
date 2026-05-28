
#include "append_stdout.hpp"
#include "arrow_handler.hpp"
#include "stderr_redirect.hpp"
#include <iostream>
#include <string>
#include <vector>

inline int echoHandle(std::string &line) {
  std::string inp = line.substr(5, line.size());
  bool squo = false, dquo = false;
  // Boolean flags for single quote is open
  //  or
  // double quotes is opened
  std::string arg = "";
  std::vector<std::string> finalarg;
  for (int i = 0; i < inp.size(); i++) {

    // > Operator handling

    if (inp[i] == '>') {
      finalarg.push_back(arg);
      arg = "";
      if (finalarg.size() != 0)
        arg += finalarg[0];
      for (int i = 1; i < finalarg.size(); i++)
        arg += " " + finalarg[i];
      std::string destination = inp.substr(i + 1, inp.size());

      if (arg[arg.size() - 1] == '1')
        arg = arg.substr(0, arg.size() - 2);
      else if (arg[arg.size() - 1] == '2') {
        arg = arg.substr(0, arg.size() - 2);
        if (stderrRedirect(arg, destination) == 1)
          return 1;
        return -1;
      }

      if (inp[i + 1] == '>') {
          destination=destination.substr(1,destination.size());
        if(appendStdout(arg, destination)==1) return 1;
        return -1;
      }

      if (arrowHandle(arg, destination) == 1)
        return 1;
      return 1;
    }

    // Space seperating two arguments which arent enclose in quotes
    // We will use every space outside quotes as the breaking point of words
    // Since consecutive quotes is append and space is the only place where we
    // can completely change words
    if (inp[i] == ' ' && !(squo || dquo)) {
      if (arg.size() != 0)
        finalarg.push_back(arg);
      arg = "";
    }
    // Backslash used outside any quotes
    // This would just add the next character into the argument
    else if (i != inp.size() - 1 && inp[i] == '\\' && !(squo || dquo)) {
      arg += inp[i + 1];
      i++;
    } else {
      // Logic for inside Double Quotes
      if (dquo) {
        if (inp[i] == '\\')
          arg += inp[++i];
        else if (inp[i] == '\"')
          dquo = !dquo;
        else
          arg += inp[i];
      }
      // Logic for inside Single Quotes
      else if (squo) {
        if (inp[i] == '\'')
          squo = !squo;
        else
          arg += inp[i];
      }
      // For everything outside Quotes
      else {
        if (inp[i] == '\"')
          dquo = !dquo;
        else if (inp[i] == '\'')
          squo = !squo;
        else
          arg += inp[i];
      }
    }
  }
  // Add final word into vector
  if (arg.size() != 0)
    finalarg.push_back(arg);

  // No argument, direct return
  if (finalarg.size() == 0)
    return 0;

  // Print rest
  else
    std::cout << finalarg[0];
  for (int i = 1; i < finalarg.size(); i++)
    std::cout << " " << finalarg[i];
  std::cout << std::endl;
  return 1;
}
