// RUN: %clang_tidy %s misra-c2023-adv-20.5 %t -- -std=c90 -I %S || true
// RUN: %clang_tidy %s misra-c2023-adv-20.5 %t -- -std=c99 -I %S || true
// RUN: %clang_tidy %s misra-c2023-adv-20.5 %t -- -std=c11 -I %S || true

#include header1.h
// CHECK-MESSAGES: :[[@LINE-1]]:10: error: expected "FILENAME" or <FILENAME> [clang-diagnostic-error]

int main(void)
{
  return 0;
}
