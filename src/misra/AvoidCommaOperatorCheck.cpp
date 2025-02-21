//===--- AvoidCommaOperatorCheck.cpp - clang-tidy -------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "AvoidCommaOperatorCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang::tidy::misra {

void AvoidCommaOperatorCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(binaryOperator(hasOperatorName(",")).bind("commaOp"), this);
}

void AvoidCommaOperatorCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedCommaOp = Result.Nodes.getNodeAs<BinaryOperator>("commaOp");

  if (MatchedCommaOp) {
    diag(MatchedCommaOp->getOperatorLoc(), "avoid comma operator");
  }
}

} // namespace clang::tidy::misra
