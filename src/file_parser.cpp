#include "file_parser.hpp"
#include "string_utils.hpp"

namespace external_memory_find_substr::filesystem {

std::vector<std::ifstream::pos_type>
FileParser::FindOccurrences(const std::string& pattern) {
  std::vector<std::ifstream::pos_type> occurrences;

  auto pattern_prefix_fn = string_utils::PrefixFn(pattern);

  std::size_t suprefix_size = 0;
  int next_char_in_text;
  while ((next_char_in_text = file_.get()) !=
      std::ifstream::traits_type::eof()) {
    suprefix_size = string_utils::PrefixFnNext(
        pattern, pattern_prefix_fn,
        static_cast<char>(next_char_in_text), suprefix_size);

    if (suprefix_size == pattern.size()) {
      occurrences.push_back(file_.tellg() - std::streamoff(pattern.size()));
    }
  }

  file_.clear();
  file_.seekg(0);

  return occurrences;
}

}  // namespace filesystem
