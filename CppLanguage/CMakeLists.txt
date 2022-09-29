set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined -Wall -Wextra -pedantic -Werror -Wno-self-assign-overloaded -Wno-missing-braces")
set(CMAKE_EXPORT_COMPILE_COMMANDS  ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include_directories(.)
add_subdirectory(playground)
add_subdirectory(simple_test)
add_subdirectory(array)
add_subdirectory(complex)
add_subdirectory(str)
add_subdirectory(unique_pointer)
add_subdirectory(shared_pointer)
