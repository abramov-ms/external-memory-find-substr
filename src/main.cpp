#include <iostream>
#include <string>
#include <vector>
#include <fstream>

std::vector<size_t> PrefixFunction(const std::string &subject) {
  std::vector<size_t> prefix_function;
  prefix_function.reserve(subject.size());
  prefix_function.push_back(0);

  for (size_t i = 1; i < subject.size(); ++i) {
    size_t prev_suprefix_size = prefix_function[i - 1];
    while (prev_suprefix_size > 0 &&
        subject[prev_suprefix_size] != subject[i]) {
      prev_suprefix_size = prefix_function[prev_suprefix_size - 1];
    }

    auto max_suprefix_size = prev_suprefix_size;
    if (subject[prev_suprefix_size] == subject[i]) {
      ++max_suprefix_size;
    }

    prefix_function.push_back(max_suprefix_size);
  }

  return prefix_function;
}

size_t PrefixFunctionNext(
    const std::string &pattern,
    const std::vector<std::size_t> &pattern_prefix_fn,
    char next_text_char,
    std::size_t prev_suprefix_size) {
  std::size_t suprefix_size = prev_suprefix_size;
  while (suprefix_size > 0 &&
      (suprefix_size >= pattern.size() ||
          pattern[suprefix_size] != next_text_char)) {
    suprefix_size = pattern_prefix_fn[suprefix_size - 1];
  }

  if (suprefix_size < pattern.size() &&
      next_text_char == pattern[suprefix_size]) {
    ++suprefix_size;
  }

  return suprefix_size;
}

std::string GetContext(std::ifstream &file, std::size_t content_size,
                       std::streamoff context_size) {
  auto current_pos = file.tellg();
  auto context_start = current_pos - std::streamoff(content_size) - context_size;

  file.seekg(context_start);

  std::string context;
  for (size_t i = 0; i < content_size + 2 * context_size; ++i) {
    auto text_char = file.get();
    if (text_char == EOF) {
      break;
    }

    if (text_char == '\n') {
      text_char = ' ';
    }

    context.push_back(static_cast<char>(text_char));
  }

  file.seekg(current_pos);

  return context;
}

const int kContextSize = 20;

int main() {
  std::string filename;
  std::cout << "Path to text file: ";
  std::cin >> filename;

  std::ifstream file(filename);

  auto begin = file.tellg();

  while (true) {
    size_t occurrences = 0;
    std::string query;
    std::cout << "> ";
    std::cin >> query;

    if (query == "exit") {
      break;
    }

    auto query_prefix_fn = PrefixFunction(query);
    int next_text_char;
    size_t suprefix_size = 0;
    while ((next_text_char = file.get()) != EOF) {
      suprefix_size =
          PrefixFunctionNext(query, query_prefix_fn,
                             static_cast<char>(next_text_char), suprefix_size);
      if (suprefix_size == query.size()) {
        auto context = GetContext(file, query.size(), kContextSize);
        std::cout << "..." << context << "..." << std::endl;
        ++occurrences;
      }
    }

    file.clear();
    file.seekg(begin);

    std::cout << "Found " << occurrences << " occurrences." << std::endl;
  }

  std::cout << "Search done. Have a good day!" << std::endl;
}
