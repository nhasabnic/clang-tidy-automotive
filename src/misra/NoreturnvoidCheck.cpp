//===--- NoreturnvoidCheck.cpp - clang-tidy -------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "NoreturnvoidCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang::tidy::misra {

void NoreturnvoidCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(functionDecl(isNoReturn(), unless(hasReturnTypeLoc(loc(asString("void"))))).bind("x"), this);
}

void NoreturnvoidCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl = Result.Nodes.getNodeAs<FunctionDecl>("x");
  if (MatchedDecl->getIdentifier()) {
  diag(MatchedDecl->getLocation(), "Use 'void' as return type")
      << MatchedDecl;
  }
}

} // namespace clang::tidy::misra
