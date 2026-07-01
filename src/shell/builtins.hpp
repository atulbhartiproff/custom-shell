#pragma once

#include <string>
#include <vector>

namespace shell {

const std::vector<std::string> &typeable_builtins();

bool is_typeable_builtin(const std::string &name);

} // namespace shell
