#include "string_utils.hpp"
#include "file_parser.hpp"
#include "file_context.hpp"
#include "config.hpp"
#include "console_client.hpp"

#include <iostream>

namespace external_memory_find_substr {

bool ConsoleClient::ProcessUserQuery() {
  os_ << ">> ";

  std::string query;
  std::getline(is_, query);
  if (query == "exit") {
    return true;
  }

  if (query == "current file") {
    auto filename = Config::Instance().GetFilename();
    os_ << "<< " << filename << std::endl;
  } else if (query == "load file") {
    std::string filename;
    os_ << "path to file >> ";
    std::getline(is_, filename);
    Config::Instance().SetFile(filename);
  } else if (query == "current context size") {
    os_ << "<< " << Config::Instance().GetContextSize() << std::endl;
  } else if (query == "set context size") {
    std::size_t context_size;
    os_ << "context size >> ";
    is_ >> context_size;
    std::getline(is_, query);
    Config::Instance().SetContextSize(context_size);
  } else if (query == "enable context") {
    Config::Instance().SetContextMode(true);
  } else if (query == "disable context") {
    Config::Instance().SetContextMode(false);
  } else if (query == "find") {
    FindOccurrences();
  } else if (query == "help") {
    ShowUsage();
  } else {
    os_ << "<< " << "unknown command `" << query << "`" << std::endl;
    ShowUsage();
  }

  return false;
}

void ConsoleClient::FindOccurrences() {
  auto parser = filesystem::FileParser(Config::Instance().GetFile());

  std::string pattern;
  os_ << "pattern >> ";
  std::getline(is_, pattern);

  auto occurrences = parser.FindOccurrences(pattern);
  for (const auto& [pos, line, column] : occurrences) {
    os_ << Config::Instance().GetFilename() << ":"
              << line << ":" << column;

    if (Config::Instance().IsContextEnabled()) {
      auto context = filesystem::GetContext(
          Config::Instance().GetFile(), pos,
          pattern.size(), Config::Instance().GetContextSize()
      );
      os_ << " ..." << context << "...";
    }

    os_ << '\n';
  }

  os_ << "<< Found " << occurrences.size() << " occurrences." << std::endl;
}

void ConsoleClient::ShowUsage() {
  os_ <<
    "usage:\n"
    "    current file -- show currently loaded file path\n"
    "    load file -- switch to another file\n"
    "    find -- find pattern in currently loaded file\n"
    "    current context size -- get current context size\n"
    "    set context size -- use another context size\n"
    "    enable context -- show context of occurrences\n"
    "    disable context -- do not" << std::endl;
}

}  // external_memory_find_substr