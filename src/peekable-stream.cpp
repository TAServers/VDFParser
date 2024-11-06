#include "peekable-stream.hpp"
#include <utility>

namespace VdfParser {
  PeekableStream::PeekableStream(std::string data) : data(std::move(data)) {}

  void PeekableStream::discardWhile(const std::function<bool(char)>& predicate) {
    while (predicate(peek())) {
      discard();
    }
  }

  std::string PeekableStream::consumeWhile(const std::function<bool(char)>& predicate) {
    size_t count = 0;
    while (predicate(peek())) {
      count++;
    }

    std::string consumed = peek(count);
    index += count;

    return std::move(consumed);
  }

  char PeekableStream::peek() const {
    if (empty()) {
      return 0;
    }

    return data[index];
  }

  std::string PeekableStream::peek(size_t count) const {
    return data.substr(index, count);
  }

  void PeekableStream::discard() {
    index++;
  }

  bool PeekableStream::empty() const {
    return index >= data.length();
  }
}
