//===--- AvoidFlexibleArrayMemberCheck.cpp - clang-tidy -------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "AvoidFlexibleArrayMemberCheck.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang::tidy::misra {

void AvoidFlexibleArrayMemberCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
      fieldDecl(hasType(incompleteArrayType())).bind("flexArray"), this);
}

void AvoidFlexibleArrayMemberCheck::check(
    const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl = Result.Nodes.getNodeAs<FieldDecl>("flexArray");

  if (MatchedDecl) {
    diag(MatchedDecl->getLocation(), "avoid flexible array members");
  }
}

} // namespace clang::tidy::misra
