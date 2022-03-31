#include "string_utils.hpp"

namespace external_memory_find_substr::string_utils {

std::vector<std::size_t> PrefixFn(const std::string &text) {
  std::vector<std::size_t> prefix_fn;
  prefix_fn.reserve(text.size());
  prefix_fn.push_back(0);

  for (size_t i = 1; i < text.size(); ++i) {
    size_t prev_suprefix_size = prefix_fn[i - 1];
    while (prev_suprefix_size > 0 &&
           text[prev_suprefix_size] != text[i]) {
      prev_suprefix_size = prefix_fn[prev_suprefix_size - 1];
    }

    auto max_suprefix_size = prev_suprefix_size;
    if (text[prev_suprefix_size] == text[i]) {
      ++max_suprefix_size;
    }

    prefix_fn.push_back(max_suprefix_size);
  }

  return prefix_fn;
}

std::size_t PrefixFnNext(
    const std::string &pattern,
    const std::vector<std::size_t> &pattern_prefix_fn,
    char next_char_in_text,
    std::size_t prev_suprefix_size) {
  std::size_t suprefix_size = prev_suprefix_size;

  for (;;) {
    auto suprefix_matches =
        suprefix_size < pattern.size() &&
        pattern[suprefix_size] == next_char_in_text;
    if (suprefix_size == 0 || suprefix_matches) {
      break;
    }

    suprefix_size = pattern_prefix_fn[suprefix_size - 1];
  }

  if (suprefix_size < pattern.size() &&
      next_char_in_text == pattern[suprefix_size]) {
    ++suprefix_size;
  }

  return suprefix_size;
}

} //  namespace string_utils
