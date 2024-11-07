#include "vdf.hpp"
#include "errors.hpp"
#include "peekable-stream.hpp"
#include <set>

namespace VdfParser {
  namespace {
    const std::set WHITESPACE = {' ', '\t', '\r', '\n'};

    std::string parseLiteral(PeekableStream& stream) {
      std::set<char> terminators;
      bool isQuoted = false;

      if (stream.peek() == '"') {
        stream.discard();
        terminators = {'"'};
        isQuoted = true;
      } else {
        terminators = {'"', '{', '}'};
        terminators.insert(WHITESPACE.begin(), WHITESPACE.end());
        isQuoted = false;
      }

      std::string literal = stream.consumeWhile([&terminators](const char c) { return !terminators.contains(c); });

      if (isQuoted) {
        stream.discard();
      }

      return std::move(literal);
    }

    void discardWhitespaceAndComments(PeekableStream& stream) {
      while (!stream.empty() && (WHITESPACE.contains(stream.peek()) || stream.peek(2) == "//")) {
        if (WHITESPACE.contains(stream.peek())) {
          stream.discardWhile([](const char c) { return WHITESPACE.contains(c); });
        }

        if (stream.peek(2) == "//") {
          stream.discardWhile([](const char c) { return c != '\r' && c != '\n'; });
        }
      }
    }

    std::vector<KeyValue> parseKeyValues(PeekableStream& stream) {
      std::vector<KeyValue> values;

      while (!stream.empty() && stream.peek() != '}') {
        KeyValue keyValue;

        discardWhitespaceAndComments(stream);

        keyValue.key = parseLiteral(stream);

        discardWhitespaceAndComments(stream);

        if (stream.peek() == '{') {
          stream.discard();
          keyValue.value = parseKeyValues(stream);

          if (stream.peek() != '}') {
            throw Errors::UnexpectedCharacter("Expected '}' to close key-value block");
          }

          stream.discard();
        } else {
          keyValue.value = parseLiteral(stream);
        }

        values.push_back(std::move(keyValue));

        discardWhitespaceAndComments(stream);
      }

      return std::move(values);
    }
  }

  KeyValue fromString(const std::string& raw) {
    PeekableStream stream(raw);
    return KeyValue{.key = "root", .value = parseKeyValues(stream)};
  }
}
