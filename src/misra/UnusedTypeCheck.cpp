//===--- UnusedTypeCheck.cpp - clang-tidy ---------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "UnusedTypeCheck.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang::tidy::misra {

void UnusedTypeCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(typedefDecl().bind("typedef"), this);
}

void UnusedTypeCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl = Result.Nodes.getNodeAs<TypedefDecl>("typedef");

  if (!MatchedDecl) {
    return;
  }

  if (MatchedDecl->isImplicit()) {
     return;
  }

  if (MatchedDecl->getMostRecentDecl()->isReferenced()) {
    return;
  }

  diag(MatchedDecl->getLocation(), "unused type declaration '%0'")
      << MatchedDecl->getName();
}

} // namespace clang::tidy::misra
