//===--- WrongOrderInSwitchStmtCheck.cpp - clang-tidy ---------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "WrongOrderInSwitchStmtCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang::tidy::automotive {

void WrongOrderInSwitchStmtCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
      switchStmt(forEachSwitchCase(switchCase().bind("case"))).bind("switch"),
      this);
}

void WrongOrderInSwitchStmtCheck::check(
    const MatchFinder::MatchResult &Result) {
  const auto *MatchSwitch = Result.Nodes.getNodeAs<SwitchStmt>("switch");
  const auto *MatchCase = Result.Nodes.getNodeAs<SwitchCase>("case");

  if ((MatchSwitch) && (MatchSwitch != PrevSwitch)) {
    PrevDefault = nullptr;
  } else if ((MatchCase) && (PrevDefault)) {
    diag(PrevDefault->getBeginLoc(), "default statement neither first or last");
    PrevDefault = nullptr;
  } else {
    const auto *MatchDefault = llvm::dyn_cast<DefaultStmt>(MatchCase);
    PrevDefault = MatchDefault;
  }
  PrevSwitch = MatchSwitch;
}

} // namespace clang::tidy::automotive
