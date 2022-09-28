set(CMAKE_C_STANDARD 11)
set (CMAKE_C_FLAGS "-fsanitize=undefined -Wall -Wextra -pedantic -Werror -Wno-missing-braces")
set(CMAKE_EXPORT_COMPILE_COMMANDS  ON)


include_directories(.)
add_subdirectory(example)
