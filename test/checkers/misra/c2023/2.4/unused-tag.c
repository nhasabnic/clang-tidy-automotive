// RUN: %check_clang_tidy %s misra-c2023-adv-2.4 %t -- -- -std=c90
// RUN: %check_clang_tidy %s misra-c2023-adv-2.4 %t -- -- -std=c99
// RUN: %check_clang_tidy %s misra-c2023-adv-2.4 %t -- -- -std=c11

#include <stdint.h>

typedef struct {                   /* Complaint */
  uint8_t address;
  uint8_t data;
} package1_t;

typedef struct tag_package2_t {    /* Not complaint */
// CHECK-MESSAGES: :[[@LINE-1]]:16: warning: unused tag 'tag_package2_t' [misra-c2023-adv-2.4]
  uint16_t address;
  uint16_t data;
} package2_t;

struct tag_package3_t {            /* Complaint - however it seems broken right now... ?? */
// CHECK-MESSAGES: :[[@LINE-1]]:8: warning: unused tag 'tag_package3_t' [misra-c2023-adv-2.4]
  uint16_t address;
  uint16_t data;
};

void f(void) {
  struct tag_package3_t p = {0};

}

void g(void) {
  enum color { RED, GREEN, BLUE }; /* Not compliant */
// CHECK-MESSAGES: :[[@LINE-1]]:8: warning: unused tag 'color' [misra-c2023-adv-2.4]

  enum status { OK, FAIL };        /* Compliant - however it seems broken right now... ?? */
// CHECK-MESSAGES: :[[@LINE-1]]:8: warning: unused tag 'status' [misra-c2023-adv-2.4]

  enum status test = OK;
}
