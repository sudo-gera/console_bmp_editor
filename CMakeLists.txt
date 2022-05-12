cmake_minimum_required(VERSION 3.22)
project(DraftRepo)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS  ON)

include_directories(..)

add_subdirectory(CLanguage)
add_subdirectory(CppLanguage)
