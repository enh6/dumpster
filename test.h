#include <stdio.h>
#include <stdbool.h>

int test_count = 0;
int fail_count = 0;

#define ASSERT(condition)\
  if ((condition) == false) {\
    printf("%s:%d %s\n", __FILE__, __LINE__, __FUNCTION__);\
    printf("  Assertion failed: \"" #condition "\"\n");\
    fail_count++;\
    return;\
  }

#define TEST_CASE(name) void test_##name()

#define TEST(name)\
  do {\
    test_count++;\
    printf("Testing case #%d " #name "\n", test_count);\
    test_##name();\
  } while (0)

#define TEST_END()\
  do {\
    printf("Test finished.\n");\
    printf("%d/%d test passed.\n", (test_count-fail_count), test_count);\
  } while (0)


