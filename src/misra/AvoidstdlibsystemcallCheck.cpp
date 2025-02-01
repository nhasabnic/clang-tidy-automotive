//===--- AvoidstdlibsystemcallCheck.cpp - clang-tidy ----------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "AvoidstdlibsystemcallCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang::tidy::misra {


void AvoidstdlibsystemcallCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(callExpr(callee(functionDecl(hasName("system")))).bind("func"), this);
}

void AvoidstdlibsystemcallCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedCall = Result.Nodes.getNodeAs<CallExpr>("func");
  if (MatchedCall) {
    diag(MatchedCall->getBeginLoc(),
         "Avoid '%0' call from stdlib")
        << MatchedCall->getDirectCallee()->getNameAsString();
  }
}

} // namespace clang::tidy::misra
