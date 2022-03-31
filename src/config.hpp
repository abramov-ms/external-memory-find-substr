#pragma once

#include "exception.hpp"

#include <fstream>

namespace external_memory_find_substr {

class Config {
 public:
  static const std::size_t kDefaultContextSize = 20;
  static const bool kDefaultShowOccurrences = true;

  static Config& Instance();

  std::ifstream& GetFile();
  const std::string& GetFilename() const;
  void SetFile(const std::string& filename);

  std::size_t GetContextSize() const { return context_size_; }
  void SetContextSize(std::size_t size) { context_size_ = size; }

  bool IsContextEnabled() const { return enable_context_; }
  void SetContextMode(bool enable_context) { enable_context_ = enable_context; }

 private:
  explicit Config() = default;

  std::ifstream file_;
  std::string filename_;
  std::size_t context_size_{kDefaultContextSize};
  bool enable_context_{kDefaultShowOccurrences};
};

}  // external_memory_find_substr