//===--- AtoXCheck.cpp - clang-tidy --------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "ExitCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang::tidy::misra {

void ExitCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(callExpr(callee(functionDecl(hasAnyName(
                                  "abort", "exit", "_Exit", "quick_exit"))))
                         .bind("func"),
                     this);
}

void ExitCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedCall = Result.Nodes.getNodeAs<CallExpr>("func");
  if (MatchedCall) {
    diag(MatchedCall->getBeginLoc(), "Avoid termination function '%0'")
        << MatchedCall->getDirectCallee()->getNameAsString();
  }
}

} // namespace clang::tidy::misra
