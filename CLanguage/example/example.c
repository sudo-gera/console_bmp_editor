#include <ctest.h>
#include <stdlib.h>
CTEST(TEST, test) {
  malloc(10);
  ASSERT_NOT_NULL("Hello, world!");
}
