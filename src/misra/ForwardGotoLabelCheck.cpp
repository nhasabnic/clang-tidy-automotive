//===--- ForwardGotoLabelCheck.cpp - clang-tidy ---------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "ForwardGotoLabelCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang::tidy::misra {

static const LabelStmt* getLabelStmt(const GotoStmt* Goto);

void ForwardGotoLabelCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(gotoStmt().bind("goto"), this);
}

void ForwardGotoLabelCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedGoto = Result.Nodes.getNodeAs<GotoStmt>("goto");
  const auto *MatchedLabel = getLabelStmt(MatchedGoto);

  if (MatchedGoto && MatchedLabel) {
    SourceManager &SM = Result.Context->getSourceManager();
    const auto GotoLoc = MatchedGoto->getBeginLoc();
    const auto LabelLoc = MatchedLabel->getBeginLoc();

    if (SM.isBeforeInTranslationUnit(LabelLoc, GotoLoc)) {
       diag(GotoLoc, "goto statement jumps backward to label '%0'")
            << MatchedLabel->getName();
       diag(LabelLoc, "location of label '%0'", DiagnosticIDs::Note)
            << MatchedLabel->getName();
    }
  }
}

static const LabelStmt* getLabelStmt(const GotoStmt* Goto) {
  if (Goto) {
    const auto* Label = Goto->getLabel();

    if (Label) {
      return Label->getStmt();
    }
  }
  return nullptr;
}

} // namespace clang::tidy::misra
