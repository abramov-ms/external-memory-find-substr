#pragma once

#include <string>
#include <istream>
#include <ostream>

namespace external_memory_find_substr {

class ConsoleClient {
 public:
  ConsoleClient(std::istream& is, std::ostream& os): is_(is), os_(os) {}

  void ProcessCommand(const std::string& command);

 private:
  void SetOption(const std::string& key, const std::string& value);

  std::istream& is_;
  std::ostream& os_;
};

}  // namespace external_memory_find_substr