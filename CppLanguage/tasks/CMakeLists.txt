set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fsanitize=address,undefined -Wall -Wextra -pedantic -Werror -Wno-self-assign-overloaded -Wno-missing-braces")
set(CMAKE_EXPORT_COMPILE_COMMANDS  ON)

add_subdirectory(any)
add_subdirectory(array)
add_subdirectory(complex)
add_subdirectory(function)
add_subdirectory(graph)
add_subdirectory(shared_pointer)
add_subdirectory(simple_test)
add_subdirectory(str)
add_subdirectory(tuple)
add_subdirectory(unique_pointer)

