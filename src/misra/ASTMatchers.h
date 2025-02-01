//===--- ASTMatchers.h - clang-tidy -----------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_ASTMATCHERS_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_ASTMATCHERS_H

#include "clang/ASTMatchers/ASTMatchers.h"

namespace clang::tidy::misra {

namespace ast_matchers {

using namespace clang::ast_matchers;

AST_MATCHER(QualType, isRestrictType) {
  return Node.getLocalQualifiers().hasRestrict();
}

AST_MATCHER(SwitchStmt, hasDefaultStmt) {
  for (const SwitchCase *SC = Node.getSwitchCaseList(); SC; SC = SC->getNextSwitchCase()) {
    if (llvm::isa<DefaultStmt>(SC)) {
      return true;
    }
  }
  return false;
}

AST_MATCHER(Expr, isEssentiallyBoolean) {
  if (Node.getType()->isBooleanType()) {
    return true;
  } else if (const auto *BinaryOp = dyn_cast<BinaryOperator>(&Node)) {
    return BinaryOp->isComparisonOp() || BinaryOp->isLogicalOp();
  } else {
    return false;
  }
}

AST_MATCHER(BinaryOperator, isAssignmentResultUsed) {
  const auto *Parent = Finder->getASTContext().getParents(Node)[0].get<Stmt>();
  if (!Parent) {
    return false;
  }
  return isa<Expr>(Parent);
}

/*
ast_matchers::internal::Matcher<clang::NamedDecl>
hasAnyFunctionNames(const llvm::StringSet<> &FunctionNames);



ast_matchers::internal::Matcher<clang::NamedDecl>
hasAnyFunctionNames(const llvm::StringSet<> &FunctionNames) {
  llvm::SmallVector<llvm::StringRef, 8> Names;
  for (const auto &Name : FunctionNames) {
    Names.push_back(Name.getKey());
  }
  return functionDecl(hasAnyName(Names));
}
*/

} //namespace ast_matchers

namespace misra = ast_matchers;

} // namespace clang::tidy::misra

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_ASTMATCHERS_H
