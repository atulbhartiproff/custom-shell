#pragma once

#include <string>

enum class DispatchResult { Continue, Exit };

DispatchResult dispatch(const std::string &line);
