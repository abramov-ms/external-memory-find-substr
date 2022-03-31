#include "file_context.hpp"

namespace external_memory_find_substr::filesystem {

std::string GetContext(
    std::ifstream& file, std::istream::pos_type content_pos,
    std::size_t content_size, std::size_t context_size) {
  auto initial_pos = file.tellg();
  auto context_start =
      std::max(std::istream::pos_type(0),
               content_pos - std::streamoff(context_size));

  std::string context;
  context.reserve(content_size + 2 * context_size);
  file.seekg(context_start);
  for (std::size_t i = 0; i < content_size + 2 * context_size; ++i) {
    auto char_in_text = file.get();
    if (char_in_text == std::ifstream::traits_type::eof()) {
      break;
    }

    if (std::isspace(char_in_text)) {
      char_in_text = '\x20';
    }

    context.push_back(static_cast<char>(char_in_text));
  }

  file.clear();
  file.seekg(initial_pos);

  return context;
}

}  // namespace filesystem
