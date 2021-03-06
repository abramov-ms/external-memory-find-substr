#pragma once

#include <istream>
#include <ostream>

namespace external_memory_find_substr {

bool ProcessUserQuery();

class ConsoleClient {
 public:
  ConsoleClient(std::istream& is, std::ostream& os): is_(is), os_(os) {
  }

  bool ProcessUserQuery();

 private:
  void ShowUsage();
  void FindOccurrences();

  std::istream& is_;
  std::ostream& os_;
};

}  // namespace external_memory_find_substr