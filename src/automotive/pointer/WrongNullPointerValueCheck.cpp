//===--- WrongNullPointerValueCheck.cpp - clang-tidy ----------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "WrongNullPointerValueCheck.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang::tidy::automotive {

void WrongNullPointerValueCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
      expr(anyOf(
          implicitCastExpr(hasSourceExpression(integerLiteral(equals(0))),
                           hasType(pointerType()))
              .bind("assign"),
          binaryOperator(hasOperatorName("=="),
                         hasLHS(expr(hasType(pointerType()))),
                         hasRHS(integerLiteral(equals(0))))
              .bind("compare"),
          conditionalOperator(hasTrueExpression(integerLiteral(equals(0))),
                              hasFalseExpression(hasType(pointerType())))
              .bind("ternary"),
          conditionalOperator(hasFalseExpression(integerLiteral(equals(0))),
                              hasTrueExpression(hasType(pointerType())))
              .bind("ternary"))),
      this);
}

void WrongNullPointerValueCheck::check(const MatchFinder::MatchResult &Result) {
  if (const auto *E = Result.Nodes.getNodeAs<Expr>("assign")) {
    diag(E->getBeginLoc(),
         "Use NULL instead of 0 for null pointer assignment.");
  } else if (const auto *E = Result.Nodes.getNodeAs<Expr>("compare")) {
    diag(E->getBeginLoc(), "Use NULL instead of 0 in pointer comparisons.");
  } else if (const auto *E = Result.Nodes.getNodeAs<Expr>("ternary")) {
    diag(
        E->getBeginLoc(),
        "Use NULL instead of 0 in conditional expressions involving pointers.");
  }
}

} // namespace clang::tidy::automotive
