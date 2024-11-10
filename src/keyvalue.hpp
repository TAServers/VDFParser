#pragma once

#include "case-insensitive-map.hpp"
#include <optional>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

namespace VdfParser {
  struct KeyValue {
    std::variant<std::string, CaseInsensitiveMap<KeyValue>> value;

    [[nodiscard]] std::optional<CaseInsensitiveMap<KeyValue>> getChildren() const;

    [[nodiscard]] std::optional<KeyValue> getChild(const std::string& key) const;

    [[nodiscard]] bool hasChild(const std::string& key) const;

    [[nodiscard]] std::optional<std::string> getValue() const;

    [[nodiscard]] std::optional<std::string> getNestedValue(const std::vector<std::string>& path) const;
  };
}
