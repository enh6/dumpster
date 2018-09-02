#ifndef _TEST_H_
#define _TEST_H_
#include <stdio.h>

int test_count = 0;
int success_count = 0;

int test_success;

#define ASSERT(condition)                                                      \
  if (!(condition)) {                                                          \
    printf("%s:%d %s\n", __FILE__, __LINE__, __FUNCTION__);                    \
    printf("  Assertion failed: \"" #condition "\"\n");                        \
    test_success = 0;                                                          \
  }

#define TEST_CASE(name)                                                        \
  test_count++;                                                                \
  test_success = 1;                                                            \
  printf("Testing case #%d " #name "\n", test_count);                          \
  for (int _i = 0; _i == 0; _i++, success_count += test_success,               \
           printf("%s", test_success ? "Success\n" : "Fail\n"))

#define TEST_END()                                                             \
  do {                                                                         \
    printf("Test finished.\n");                                                \
    printf("%d/%d test passed.\n", success_count, test_count);                 \
  } while (0)

#endif
