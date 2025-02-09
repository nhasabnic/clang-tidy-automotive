//===--- UnusedLabelCheck.cpp - clang-tidy --------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "UnusedLabelCheck.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang::tidy::misra {

void UnusedLabelCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(labelStmt().bind("label"), this);
}

void UnusedLabelCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedLabel = Result.Nodes.getNodeAs<LabelStmt>("label");

  if (!MatchedLabel) {
    return;
  }

  if (MatchedLabel->getDecl()->isReferenced()) {
    return;
  }

  diag(MatchedLabel->getBeginLoc(), "unused label '%0'")
       << MatchedLabel->getName();
}

} // namespace clang::tidy::misra
