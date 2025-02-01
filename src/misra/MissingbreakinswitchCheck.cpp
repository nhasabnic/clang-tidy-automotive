//===--- MissingbreakinswitchCheck.cpp - clang-tidy -----------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "MissingbreakinswitchCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang::tidy::misra {

void MissingbreakinswitchCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(switchStmt().bind("switchStmt"), this);
}

void MissingbreakinswitchCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *Switch = Result.Nodes.getNodeAs<SwitchStmt>("switchStmt");
  if (!Switch) return;

  // Hämta CompoundStmt som innehåller alla satser i switch-satsen
  const auto *Body = dyn_cast<CompoundStmt>(Switch->getBody());
  if (!Body) return;

  // Iterera genom alla satser i switch-satsen
  for (auto It = Body->body_begin(); It != Body->body_end(); ++It) {
    const Stmt *S = *It;

    // Om det är en case/default-sats
    if (const auto *Case = dyn_cast<CaseStmt>(S)) {
      checkCase(Case, It, Body, Result.Context);
    } else if (const auto *Default = dyn_cast<DefaultStmt>(S)) {
      checkCase(Default, It, Body, Result.Context);
    }
  }
}

void MissingbreakinswitchCheck::checkCase(const Stmt *Case, CompoundStmt::const_body_iterator It,
               const CompoundStmt *Body, ASTContext *Context) {
  // Hoppa över tomma fall-throughs
  if (isa<CaseStmt>(Case) && Case->children().empty()) {
    return;
  }

  // Leta efter ett break i efterföljande satser
  bool FoundBreak = false;
  for (++It; It != Body->body_end(); ++It) {
    const Stmt *S = *It;

    // Om vi hittar ett break, är satsen compliant
    if (isa<BreakStmt>(S)) {
      FoundBreak = true;
      break;
    }

    // Om vi hittar nästa case/default, avbryt sökningen
    if (isa<CaseStmt>(S) || isa<DefaultStmt>(S)) {
      break;
    }
  }

  // Om inget break hittades, rapportera fel
  if (!FoundBreak) {
    diag(Case->getBeginLoc(),
         "Every non-empty switch case must end with a break statement");
  }
}



} // namespace clang::tidy::misra
