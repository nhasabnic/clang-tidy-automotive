//===--- AvoidRestrictTypeCheck.cpp - clang-tidy --------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "AvoidRestrictTypeCheck.h"
#include "ASTMatchers.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang::tidy::misra {

void AvoidRestrictTypeCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
      typeLoc(loc(qualType(misra::isRestrictType()))).bind("restrictTypeLoc"),
      this);
}

void AvoidRestrictTypeCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedTypeLoc =
          Result.Nodes.getNodeAs<TypeLoc>("restrictTypeLoc"))

  if (MatchedTypeLoc) {
    SourceLocation Loc = MatchedTypeLoc->getBeginLoc();
    if (Loc.isValid()) {
      diag(Loc, "avoid restrict type");
    }
  }
}

} // namespace clang::tidy::misra
