//===--- WrongorderdefaultinswitchstatementCheck.cpp - clang-tidy ---------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "WrongorderdefaultinswitchstatementCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang::tidy::misra {

void WrongorderdefaultinswitchstatementCheck::registerMatchers(
    MatchFinder *Finder) {
  Finder->addMatcher(
      switchStmt(forEachSwitchCase(switchCase().bind("case"))).bind("switch"),
      this);
}

void WrongorderdefaultinswitchstatementCheck::check(
    const MatchFinder::MatchResult &Result) {
  const auto *MatchSwitch = Result.Nodes.getNodeAs<SwitchStmt>("switch");
  const auto *MatchCase = Result.Nodes.getNodeAs<SwitchCase>("case");
  const auto *MatchDefault = llvm::dyn_cast<DefaultStmt>(MatchCase);

  if ((MatchSwitch) && (MatchSwitch != PrevSwitch)) {
    PrevDefault = nullptr;
  } else if ((MatchCase) && (PrevDefault)) {
    diag(PrevDefault->getBeginLoc(), "default statement neither first or last");
    PrevDefault = nullptr;
  } else {
    PrevDefault = MatchDefault;
  }
  PrevSwitch = MatchSwitch;
}

} // namespace clang::tidy::misra
