//===--- MissingDefaultInSwitchStatementCheck.cpp - clang-tidy ------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "MissingDefaultInSwitchStatementCheck.h"
#include "utils/ASTMatchers.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang::tidy::misra {

void MissingDefaultInSwitchStatementCheck::registerMatchers(
    MatchFinder *Finder) {
  Finder->addMatcher(
      switchStmt(unless(misra::hasDefaultStmt())).bind("switchStmt"), this);
}

void MissingDefaultInSwitchStatementCheck::check(
    const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl = Result.Nodes.getNodeAs<SwitchStmt>("switchStmt");
  if (MatchedDecl) {
    diag(MatchedDecl->getSwitchLoc(),
         "missing default statement in switch statement");
  }
}

} // namespace clang::tidy::misra
