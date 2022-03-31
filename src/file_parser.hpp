#pragma once

#include "config.hpp"

#include <string>
#include <vector>
#include <fstream>
#include <ios>

namespace external_memory_find_substr::filesystem {

class FileParser {
 public:
  explicit FileParser(): file_(Config::Instance().GetFile()) {
  }

  std::vector<std::ifstream::pos_type>
  FindOccurrences(const std::string& pattern);

 private:
  std::ifstream& file_;
};

}  // namespace filesystem
