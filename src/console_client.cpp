#include "string_utils.hpp"
#include "file_parser.hpp"
#include "file_context.hpp"
#include "config.hpp"
#include "console_client.hpp"

#include <iostream>

namespace external_memory_find_substr {

bool ProcessUserQuery() {
  std::cout << ">> ";

  std::string query;
  std::getline(std::cin, query);
  if (query == "exit") {
    return true;
  }

  if (query == "show file") {
    std::cout << "<< " << Config::Instance().GetFilename() << std::endl;
  } else if (query == "load file") {
    std::string filename;
    std::cout << "path to file >> ";
    std::getline(std::cin, filename);
    Config::Instance().SetFile(filename);
  } else if (query == "find") {
    auto parser = filesystem::FileParser(Config::Instance().GetFile());

    std::string pattern;
    std::cout << "pattern >> ";
    std::getline(std::cin, pattern);

    auto occurrences = parser.FindOccurrences(pattern);
    if (Config::Instance().GetShowOccurrences()) {
      for (const auto& [pos, line, column] : occurrences) {
        auto context = filesystem::GetContext(
            Config::Instance().GetFile(), pos,
            pattern.size(), Config::Instance().GetContextSize()
        );

        std::cout << Config::Instance().GetFilename() << ":"
                  << line << ":" << column << " "
                  << "..." << context << "..." << std::endl;
      }
    }
    std::cout << "Found " << occurrences.size() << " occurrences." << std::endl;
  }

  return false;
}

}  // external_memory_find_substr