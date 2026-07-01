#include "shell/builtins.hpp"

namespace shell {

const std::vector<std::string> &typeable_builtins() {
  static const std::vector<std::string> builtins = {"type", "echo", "exit",
                                                    "pwd"};
  return builtins;
}

bool is_typeable_builtin(const std::string &name) {
  for (const auto &builtin : typeable_builtins()) {
    if (name == builtin) {
      return true;
    }
  }
  return false;
}

} // namespace shell
