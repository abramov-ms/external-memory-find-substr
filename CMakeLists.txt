cmake_minimum_required(VERSION 3.21)
project(external_memory_find_substr)

set(CMAKE_CXX_STANDARD 17)

add_executable(external_memory_find_substr src/main.cpp src/string_utils.hpp src/string_utils.cpp src/file_parser.hpp src/file_parser.cpp src/file_context.hpp src/file_context.cpp src/config.hpp src/config.cpp src/exception.hpp src/console_client.hpp src/console_client.cpp)
