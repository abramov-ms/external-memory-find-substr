#pragma once

#include <string>
#include <fstream>

namespace external_memory_find_substr::filesystem {

std::string GetContext(
    std::ifstream& file, std::ifstream::pos_type content_pos,
    std::size_t content_size, std::size_t context_size);

}  // namespace filesystem
