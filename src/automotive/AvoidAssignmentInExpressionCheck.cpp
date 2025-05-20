//===--- AvoidAssignmentInExpressionCheck.cpp - clang-tidy ----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "AvoidAssignmentInExpressionCheck.h"
#include "utils/ASTMatchers.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang::tidy::automotive {

void AvoidAssignmentInExpressionCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
      binaryOperator(isAssignmentOperator(), automotive::isAssignmentResultUsed())
          .bind("assignment"),
      this);
}

void AvoidAssignmentInExpressionCheck::check(
    const MatchFinder::MatchResult &Result) {
  const auto *Assignment = Result.Nodes.getNodeAs<BinaryOperator>("assignment");

  if (Assignment) {
    diag(Assignment->getOperatorLoc(),
         "Avoid using the result of an assignment operator '%0'")
        << Assignment->getOpcodeStr();
  }
}

} // namespace clang::tidy::automotive
