//===--- AtoXCheck.cpp - clang-tidy --------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "AtoXCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang::tidy::misra {

void AtoXCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(callExpr(callee(functionDecl(
                                  hasAnyName("atof", "atoi", "atol", "atoll"))))
                         .bind("func"),
                     this);
}

void AtoXCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedCall = Result.Nodes.getNodeAs<CallExpr>("func");
  if (MatchedCall) {
    diag(MatchedCall->getBeginLoc(),
         "Avoid function '%0' that has undefined behavior")
        << MatchedCall->getDirectCallee()->getNameAsString();
  }
}

} // namespace clang::tidy::misra
