#include <iostream>
#include <string>
#include <vector>

std::vector<size_t> PrefixFunction(const std::string& subject) {
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

std::vector<size_t> KMP(const std::string& haystack,
                        const std::string& needle) {
  auto cat = needle + "#" + haystack;
  auto prefix_function = PrefixFunction(cat);

  std::vector<size_t> needle_occurences;
  for (size_t i = 0; i < prefix_function.size(); ++i) {
    if (prefix_function[i] == needle.size()) {
      needle_occurences.push_back(i - 2 * needle.size());
    }
  }

  return needle_occurences;
}

int main() {
  std::string haystack;
  std::string needle;
  std::cin >> haystack >> needle;

  auto needle_occurences = KMP(haystack, needle);
  for (const auto& position : needle_occurences) {
    std::cout << position << '\n';
  }
}

