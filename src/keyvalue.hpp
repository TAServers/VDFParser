#pragma once

#include <string>
#include <unordered_map>
#include <variant>

namespace VdfParser {
  struct KeyValue {
    std::variant<std::string, float, std::unordered_map<std::string, KeyValue>> value;
  };
}
