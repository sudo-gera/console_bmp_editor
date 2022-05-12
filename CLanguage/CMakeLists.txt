cmake_minimum_required(VERSION 3.22)
project(DraftRepo)

set(CMAKE_C_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

#add_executable(c_language)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address,undefined -Wall -Wextra -pedantic -Werror -Wno-missing-braces")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


include_directories(.)

add_subdirectory(simple_test)