#pragma once

#include <stdexcept>

namespace external_memory_find_substr {

class ExternalMemoryFindSubstrException : public std::runtime_error {
 public:
  explicit ExternalMemoryFindSubstrException(const std::string& message):
    std::runtime_error(message) {}
};

}  // external_memory_find_substr
