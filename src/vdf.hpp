#pragma once

#include "keyvalue.hpp"
#include <unordered_map>

namespace VdfParser {
  std::unordered_map<std::string, KeyValue> fromString(const std::string& raw);
}
