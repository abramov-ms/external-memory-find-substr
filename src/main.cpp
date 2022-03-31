#include "string_utils.hpp"
#include "file_parser.hpp"
#include "file_context.hpp"
#include "config.hpp"

#include <iostream>

int main() {
  using namespace external_memory_find_substr;

  auto parser = filesystem::FileParser();

  while (true) {
    std::cout << ">> ";

    std::string query;
    std::cin >> query;
    if (query == "exit") {
      break;
    }

    if (query == "load") {
      std::string filename;
      std::cin >> filename;
      Config::Instance().SetFile(std::ifstream(filename));
    } else if (query == "find") {
      std::string pattern;
      std::cin >> pattern;

      auto occurrences = parser.FindOccurrences(pattern);
      for (const auto& occurrence: occurrences) {
        auto context = filesystem::GetContext(
            Config::Instance().GetFile(), occurrence,
            pattern.size(), Config::Instance().GetContextSize()
        );

        std::cout << "..." << context << "..." << std::endl;
      }
      std::cout << "Found " << occurrences.size() << " occurrences." << std::endl;
    }
  }

  std::cout << "Search done. Have a good day!" << std::endl;
}
