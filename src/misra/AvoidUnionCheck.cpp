//===--- AvoidUnionCheck.cpp - clang-tidy ---------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "AvoidUnionCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang::tidy::misra {

void AvoidUnionCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
      recordDecl(isUnion(), hasDeclContext(translationUnitDecl()))
          .bind("union"),
      this);
}

void AvoidUnionCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl = Result.Nodes.getNodeAs<RecordDecl>("union");

  if (MatchedDecl) {
    diag(MatchedDecl->getBeginLoc(), "avoid union keyword");
  }
}

} // namespace clang::tidy::misra
