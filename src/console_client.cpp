#include "console_client.hpp"

#include <sstream>

namespace external_memory_find_substr {

void ConsoleClient::ProcessCommand(const std::string& command) {
  std::istringstream iss(command);

  std::string query;
  iss >> query;
  if (query == "load") {

  } else if (query == "find") {

  } else if (query == "set") {
    std::string key;
    std::string value;
    iss >> key >> value;

    SetOption(key, value);
  } else {
    os_ << "Unknown command `" << query << "`" << std::endl;
  }
}

void ConsoleClient::SetOption(const std::string &key,
                              const std::string &value) {
  // Backoff
}

}  // namespace external_memory_find_substr
