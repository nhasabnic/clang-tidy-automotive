//===--- MissingBreakInSwitchCheck.cpp - clang-tidy -----------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "MissingBreakInSwitchCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang::tidy::misra {

void MissingBreakInSwitchCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(switchStmt().bind("switchStmt"), this);
}

void MissingBreakInSwitchCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *Switch = Result.Nodes.getNodeAs<SwitchStmt>("switchStmt");
  if (!Switch)
    return;

  const auto *Body = dyn_cast<CompoundStmt>(Switch->getBody());
  if (!Body)
    return;

  for (auto It = Body->body_begin(); It != Body->body_end(); ++It) {
    const Stmt *S = *It;

    if (const auto *Case = dyn_cast<CaseStmt>(S)) {
      checkCase(Case, It, Body, Result.Context);
    } else if (const auto *Default = dyn_cast<DefaultStmt>(S)) {
      checkCase(Default, It, Body, Result.Context);
    }
  }
}

void MissingBreakInSwitchCheck::checkCase(const Stmt *Case,
                                          CompoundStmt::const_body_iterator It,
                                          const CompoundStmt *Body,
                                          ASTContext *Context) {
  if (isa<CaseStmt>(Case) && Case->children().empty()) {
    return;
  }

  bool FoundBreak = false;
  for (++It; It != Body->body_end(); ++It) {
    const Stmt *S = *It;

    if (isa<BreakStmt>(S)) {
      FoundBreak = true;
      break;
    }

    if (isa<CaseStmt>(S) || isa<DefaultStmt>(S)) {
      break;
    }
  }

  if (!FoundBreak) {
    diag(Case->getBeginLoc(),
         "every non-empty switch case must end with a break statement");
  }
}

} // namespace clang::tidy::misra
