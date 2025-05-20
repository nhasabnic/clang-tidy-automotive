//===--- AvoidFunctionParameterModificationCheck.cpp - clang-tidy ---------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "AvoidFunctionParameterModificationCheck.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang::tidy::misra {

void AvoidFunctionParameterModificationCheck::registerMatchers(
    MatchFinder *Finder) {
  Finder->addMatcher(binaryOperator(isAssignmentOperator(),
                                    hasLHS(ignoringParenImpCasts(declRefExpr(
                                        to(parmVarDecl().bind("param"))))))
                         .bind("operator"),
                     this);

  Finder->addMatcher(
      unaryOperator(anyOf(hasOperatorName("++"), hasOperatorName("--")),
                    hasUnaryOperand(ignoringParenImpCasts(
                        declRefExpr(to(parmVarDecl().bind("param"))))))
          .bind("operator"),
      this);
}

void AvoidFunctionParameterModificationCheck::check(
    const MatchFinder::MatchResult &Result) {
  const auto *MatchedParam = Result.Nodes.getNodeAs<ParmVarDecl>("param");
  const auto *MatchedOperator = Result.Nodes.getNodeAs<Expr>("operator");

  if (MatchedParam && MatchedOperator) {
    // Check if the operator is an assignment or increment/decrement and give a
    // specific message
    if (isa<BinaryOperator>(MatchedOperator)) {
      diag(MatchedOperator->getExprLoc(),
           "avoid modifying function parameter '%0' with assignment operator")
          << MatchedParam->getName();
    } else if (isa<UnaryOperator>(MatchedOperator)) {
      diag(MatchedOperator->getExprLoc(),
           "avoid modifying function parameter '%0' with increment/decrement "
           "operator")
          << MatchedParam->getName();
    }

    // Provide the location where the parameter is declared
    diag(MatchedParam->getLocation(), "function parameter '%0' declared here",
         DiagnosticIDs::Note)
        << MatchedParam->getName();
  }
}

} // namespace clang::tidy::misra
