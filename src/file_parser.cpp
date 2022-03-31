#include "file_parser.hpp"
#include "string_utils.hpp"

namespace external_memory_find_substr::filesystem {

std::vector<FileParser::Occurrence>
FileParser::FindOccurrences(const std::string& pattern) {
  std::vector<Occurrence> occurrences;

  auto pattern_prefix_fn = string_utils::PrefixFn(pattern);

  std::size_t suprefix_size = 0;
  int next_char_in_text;
  std::size_t line = 1;
  std::size_t column = 1;
  while ((next_char_in_text = file_.get()) !=
      std::ifstream::traits_type::eof()) {
    suprefix_size = string_utils::PrefixFnNext(
        pattern, pattern_prefix_fn,
        static_cast<char>(next_char_in_text), suprefix_size);

    if (suprefix_size == pattern.size()) {
      occurrences.push_back(
          {
              file_.tellg() - std::streamoff(pattern.size()),
              line,
              column - pattern.size() + 1
          });
    }

    if (next_char_in_text == '\n') {
      ++line;
      column = 1;
    } else {
      ++column;
    }
  }

  file_.clear();
  file_.seekg(0);

  return occurrences;
}

}  // namespace filesystem
