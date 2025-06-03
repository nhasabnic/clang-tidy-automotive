//===--- MissingReturnValueHandlingCheck.cpp - clang-tidy -----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "MissingReturnValueHandlingCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang::tidy::automotive {

void MissingReturnValueHandlingCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(callExpr(hasParent(compoundStmt()),
                              callee(functionDecl(unless(returns(voidType())))))
                         .bind("missingReturn"),
                     this);
}

void MissingReturnValueHandlingCheck::check(
    const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl = Result.Nodes.getNodeAs<CallExpr>("missingReturn");

  if (MatchedDecl) {
    diag(MatchedDecl->getBeginLoc(),
         "returned value from function is not used");
  }
}

} // namespace clang::tidy::automotive
