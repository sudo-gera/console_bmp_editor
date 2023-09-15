set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fsanitize=address,undefined -Wfatal-errors -Ofast")
set(CMAKE_CXX_STANDARD 20)
add_executable(bmp "${CMAKE_SOURCE_DIR}/alg.cpp"  "${CMAKE_SOURCE_DIR}/bmp.cpp"  "${CMAKE_SOURCE_DIR}/esh.cpp"  "${CMAKE_SOURCE_DIR}/pix.cpp")
cmake_minimum_required(VERSION 3.8)
project(Image)
enable_testing()
add_subdirectory(tests)

