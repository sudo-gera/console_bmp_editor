add_executable(example example.c ../ctest_main.c)
add_test(TEST, example)

set (CMAKE_C_FLAGS "-fsanitize=address,undefined -Wall -Wextra -pedantic -Werror -Wno-self-assign-overloaded -Wno-missing-braces") 

set(CMAKE_EXPORT_COMPILE_COMMANDS  ON)