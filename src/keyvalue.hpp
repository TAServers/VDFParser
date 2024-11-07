#pragma once

#include <optional>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

namespace VdfParser {
  struct KeyValue {
    std::string key;
    std::variant<std::string, std::vector<KeyValue>> value;

    [[nodiscard]] std::optional<const std::vector<KeyValue>&> getChildren() const;

    [[nodiscard]] std::optional<KeyValue> getChild(const std::string& key) const;

    [[nodiscard]] bool hasChild(const std::string& key) const;

    [[nodiscard]] std::optional<std::string> getValue() const;

    [[nodiscard]] std::optional<std::string> getNestedValue(const std::vector<std::string>& path) const;
  };
}
