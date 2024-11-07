#include "keyvalue.hpp"

namespace VdfParser {

  std::optional<std::vector<KeyValue>> KeyValue::getChildren() const {
    if (!std::holds_alternative<std::vector<KeyValue>>(value)) {
      return std::nullopt;
    }

    return std::get<std::vector<KeyValue>>(value);
  }

  std::optional<KeyValue> KeyValue::getChild(const std::string& key) const {
    const auto& children = getChildren();
    if (!children.has_value()) {
      return std::nullopt;
    }

    for (const auto& child : children.value()) {
      if (child.key == key) {
        return child;
      }
    }

    return std::nullopt;
  }

  bool KeyValue::hasChild(const std::string& key) const {
    const auto& children = getChildren();
    if (!children.has_value()) {
      return false;
    }

    for (const auto& child : children.value()) {
      if (child.key == key) {
        return true;
      }
    }

    return false;
  }

  std::optional<std::string> KeyValue::getValue() const {
    return std::holds_alternative<std::string>(value) ? std::make_optional(std::get<std::string>(value)) : std::nullopt;
  }

  std::optional<std::string> KeyValue::getNestedValue(const std::vector<std::string>& path) const {
    std::optional node = *this;

    for (const auto& key : path) {
      node = node->getChild(key);
      if (!node.has_value()) {
        return std::nullopt;
      }
    }

    return node->getValue();
  }
}
