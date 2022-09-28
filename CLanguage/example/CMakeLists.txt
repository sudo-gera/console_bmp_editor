add_executable(c_test_example example.c ../ctest_main.c)
add_test(NAME c_test_example COMMAND c_test_example)
