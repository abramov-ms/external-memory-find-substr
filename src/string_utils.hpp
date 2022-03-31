#pragma once

#include <vector>
#include <string>

namespace external_memory_find_substr::string_utils {

std::vector<std::size_t> PrefixFn(const std::string& text);

std::size_t PrefixFnNext(
    const std::string& pattern,
    const std::vector<std::size_t>& pattern_prefix_fn,
    char next_char_in_text,
    std::size_t prev_suprefix_size);

}  // namespace string_utils