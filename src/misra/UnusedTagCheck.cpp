//===--- UnusedTagCheck.cpp - clang-tidy ----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "UnusedTagCheck.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang::tidy::misra {

void UnusedTagCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(tagDecl(unless(isExpansionInSystemHeader())).bind("tag"),
                     this);
}

void UnusedTagCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl = Result.Nodes.getNodeAs<TagDecl>("tag");

  if (!MatchedDecl) {
    return;
  }

  if (MatchedDecl->isReferenced() || MatchedDecl->isUsed()) {
    return;
  }

  if (MatchedDecl->getName().empty()) {
    return;
  }

  diag(MatchedDecl->getLocation(), "unused tag '%0'") << MatchedDecl->getName();
}

} // namespace clang::tidy::misra
