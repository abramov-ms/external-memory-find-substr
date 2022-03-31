#pragma once

#include "config.hpp"

#include <string>
#include <vector>
#include <fstream>
#include <ios>

namespace external_memory_find_substr::filesystem {

class FileParser {
 public:
  struct Occurrence {
    std::ifstream::pos_type pos;
    std::size_t line;
    std::size_t column;
  };

  explicit FileParser(std::ifstream& file): file_(file) {
  }

  std::vector<Occurrence> FindOccurrences(const std::string& pattern);

 private:
  std::ifstream& file_;
};

}  // namespace filesystem
