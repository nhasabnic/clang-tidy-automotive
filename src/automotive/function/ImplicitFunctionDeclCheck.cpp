//===--- ImplicitFunctionDeclCheck.cpp - clang-tidy -----------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "ImplicitFunctionDeclCheck.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang::tidy::automotive {

void ImplicitFunctionDeclCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(callExpr(callee(functionDecl().bind("func"))).bind("call"),
                     this);
}

void ImplicitFunctionDeclCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedCall = Result.Nodes.getNodeAs<CallExpr>("call");
  const auto *MatchedFunc = Result.Nodes.getNodeAs<FunctionDecl>("func");

  if (!MatchedCall || !MatchedFunc)
    return;

  if (MatchedFunc->hasPrototype())
    return;

  diag(MatchedCall->getBeginLoc(),
       "function '%0' is called without a prior declaration")
      << MatchedFunc->getName();
}

} // namespace clang::tidy::automotive
