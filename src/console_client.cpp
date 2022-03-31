#include "string_utils.hpp"
#include "file_parser.hpp"
#include "file_context.hpp"
#include "config.hpp"
#include "console_client.hpp"

#include <iostream>

namespace external_memory_find_substr {

namespace detail {

void FindOccurrences() {
  auto parser = filesystem::FileParser(Config::Instance().GetFile());

  std::string pattern;
  std::cout << "pattern >> ";
  std::getline(std::cin, pattern);

  auto occurrences = parser.FindOccurrences(pattern);
  for (const auto& [pos, line, column] : occurrences) {
    std::cout << Config::Instance().GetFilename() << ":"
              << line << ":" << column;

    if (Config::Instance().IsContextEnabled()) {
      auto context = filesystem::GetContext(
          Config::Instance().GetFile(), pos,
          pattern.size(), Config::Instance().GetContextSize()
      );
      std::cout << " ..." << context << "...";
    }

    std::cout << '\n';
  }

  std::cout << "<< Found " << occurrences.size() << " occurrences." << std::endl;
}

void ShowUsage() {
  std::cout <<
    "usage:\n"
    "    current file -- show currently loaded file path\n"
    "    load file -- switch to another file\n"
    "    find -- find pattern in currently loaded file\n"
    "    current context size -- get current context size\n"
    "    set context size -- use another context size\n"
    "    enable context -- show context of occurrences\n"
    "    disable context -- do not" << std::endl;
}

}

bool ProcessUserQuery() {
  std::cout << ">> ";

  std::string query;
  std::getline(std::cin, query);
  if (query == "exit") {
    return true;
  }

  if (query == "current file") {
    auto filename = Config::Instance().GetFilename();
    std::cout << "<< " << filename << std::endl;
  } else if (query == "load file") {
    std::string filename;
    std::cout << "path to file >> ";
    std::getline(std::cin, filename);
    Config::Instance().SetFile(filename);
  } else if (query == "current context size") {
    std::cout << "<< " << Config::Instance().GetContextSize() << std::endl;
  } else if (query == "set context size") {
      std::size_t context_size;
      std::cout << "context size >> ";
      std::cin >> context_size;
      std::getline(std::cin, query);
      Config::Instance().SetContextSize(context_size);
  } else if (query == "enable context") {
    Config::Instance().SetContextMode(true);
  } else if (query == "disable context") {
    Config::Instance().SetContextMode(false);
  } else if (query == "find") {
    detail::FindOccurrences();
  } else {
    std::cout << "<< " << "unknown command `" << query << "`" << std::endl;
    detail::ShowUsage();
  }

  return false;
}

}  // external_memory_find_substr