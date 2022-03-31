#include "console_client.hpp"
#include "exception.hpp"

#include <iostream>

int main() {
  using namespace external_memory_find_substr;

  while (true) {
    try {
      auto exit_query = ProcessUserQuery();
      if (exit_query) {
        break;
      }
    } catch (ExternalMemoryFindSubstrException& exc) {
      std::cout << exc.what() << std::endl;
    } catch (std::exception& exc) {
      std::cout << "Something really unexpected happened." << std::endl;
      std::cout << exc.what() << std::endl;
      return 0;
    }
  }

  std::cout << "Search done. Have a good day!" << std::endl;
}
