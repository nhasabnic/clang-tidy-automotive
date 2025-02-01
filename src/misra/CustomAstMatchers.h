//===--- CustomAstMatchers.h - clang-tidy -----------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_CUSTOMASTMATCHERS_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_CUSTOMASTMATCHERS_H

#include "clang/ASTMatchers/ASTMatchers.h"

namespace clang::tidy::misra::custom {

AST_MATCHER(SwitchStmt, hasDefaultStmt) {
  for (const SwitchCase *SC = Node.getSwitchCaseList(); SC;
       SC = SC->getNextSwitchCase()) {
    if (llvm::isa<DefaultStmt>(SC)) {
      return true;
    }
  }
  return false;
}

AST_MATCHER(SwitchStmt, hasCaseStmt) {
  for (const SwitchCase *SC = Node.getSwitchCaseList(); SC;
       SC = SC->getNextSwitchCase()) {
    if (llvm::isa<CaseStmt>(SC)) {
      return true;
    }
  }
  return false;
}

} // namespace clang::tidy::misra::custom

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_CUSTOMASTMATCHERS_H
