//===--- AvoidSignedSingleBitFieldsCheck.cpp - clang-tidy -----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "AvoidSignedSingleBitFieldsCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang::tidy::misra {

void AvoidSignedSingleBitFieldsCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(fieldDecl(allOf(isBitField(), hasType(isSignedInteger()),
                                     hasDescendant(integerLiteral(equals(1)))))
                         .bind("signedBitField"),
                     this);
}

void AvoidSignedSingleBitFieldsCheck::check(
    const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl = Result.Nodes.getNodeAs<FieldDecl>("signedBitField");

  if (MatchedDecl) {
    diag(MatchedDecl->getLocation(),
         "avoid signed type for bitfields of single bit");
  }
}

} // namespace clang::tidy::misra
