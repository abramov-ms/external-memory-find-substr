#pragma once

#include <fstream>

namespace external_memory_find_substr {

class Config {
 public:
  static const std::size_t kDefaultContextSize = 20;
  static const bool kDefaultShowOccurrences = true;

  static Config& Instance();

  std::ifstream& GetFile() { return file_; }
  void SetFile(std::ifstream&& file) { file_ = std::move(file); }

  std::size_t GetContextSize() const { return context_size_; }
  void SetContextSize(std::size_t size) { context_size_ = size; }

  bool GetShowOccurrences() const { return show_occurrences_; }
  void SetShowOccurrences(bool show_occurrences) { show_occurrences_ = show_occurrences; }

 private:
  explicit Config() = default;

  std::ifstream file_;
  std::size_t context_size_{kDefaultContextSize};
  bool show_occurrences_{kDefaultShowOccurrences};
};

}  // external_memory_find_substr