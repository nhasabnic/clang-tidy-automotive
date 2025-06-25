// RUN: %check_clang_tidy %s avoid-flexible-array-member %t -- -- -std=c11

#include <stdint.h>

struct s {
  uint32_t data[]; // Not compliant
// CHECK-MESSAGES: :[[@LINE-1]]:9: warning: Unused macro definition 'TEST' [avoid-flexible-array-member]
};

struct t {
  uint32_t data[3];
};
