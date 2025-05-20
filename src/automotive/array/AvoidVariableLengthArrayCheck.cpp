//===--- AvoidVariableLengthArrayCheck.cpp - clang-tidy -------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "AvoidVariableLengthArrayCheck.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang::tidy::automotive {

static SourceLocation getLBrace(const TypeLoc *MatchedTypeLoc);

void AvoidVariableLengthArrayCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(typeLoc(loc(variableArrayType())).bind("vlaTypeLoc"),
                     this);
}

void AvoidVariableLengthArrayCheck::check(
    const MatchFinder::MatchResult &Result) {
  const auto *MatchedTypeLoc = Result.Nodes.getNodeAs<TypeLoc>("vlaTypeLoc");

  if (!MatchedTypeLoc) {
    return;
  }

  diag(getLBrace(MatchedTypeLoc), "avoid variable-length array");
}

static SourceLocation getLBrace(const TypeLoc *MatchedTypeLoc) {
  SourceLocation LBracketLoc =
      MatchedTypeLoc->getAs<VariableArrayTypeLoc>().getLBracketLoc();

  if (LBracketLoc.isValid()) {
    return LBracketLoc;
  } else {
    return MatchedTypeLoc->getBeginLoc();
  }
}

} // namespace clang::tidy::automotive
