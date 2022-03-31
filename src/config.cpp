#include "config.hpp"

namespace external_memory_find_substr {

Config& Config::Instance() {
  static Config config;
  return config;
}

}  // namespace external_memory_find_substr
