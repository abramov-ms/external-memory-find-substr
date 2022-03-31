#include "config.hpp"

namespace external_memory_find_substr {

Config& Config::Instance() {
  static Config config;
  return config;
}

void Config::SetFile(const std::string &filename) {
  file_ = std::ifstream(filename);
  if (!file_.is_open()) {
    throw ExternalMemoryFindSubstrException(
        "could not open file " + filename);
  }

  filename_ = filename;
}

std::ifstream& Config::GetFile() {
  if (!file_.is_open()) {
    throw ExternalMemoryFindSubstrException("no file is loaded");
  }

  return file_;
}

const std::string& Config::GetFilename() const {
  if (!file_.is_open()) {
    throw ExternalMemoryFindSubstrException("no file is loaded");
  }

  return filename_;
}

}  // namespace external_memory_find_substr
