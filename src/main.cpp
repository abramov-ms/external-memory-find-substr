#include "console_client.hpp"
#include "exception.hpp"

#include <iostream>

int main() {
  auto client = external_memory_find_substr::ConsoleClient(std::cin, std::cout);

  for (;;) {
    try {
      auto exit_query = client.ProcessUserQuery();
      if (exit_query) {
        break;
      }
    } catch (external_memory_find_substr::ExternalMemoryFindSubstrException& exc) {
      std::cout << "<< " << exc.what() << std::endl;
    } catch (std::exception& exc) {
      std::cout << "<< " << "Something really unexpected happened." << std::endl;
      std::cout << "<< " << exc.what() << std::endl;
      return 0;
    }
  }
}
