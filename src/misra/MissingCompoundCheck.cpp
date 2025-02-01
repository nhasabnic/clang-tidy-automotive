//===--- MissingCompoundCheck.cpp - clang-tidy ----------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "MissingCompoundCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/ASTMatchers/ASTMatchers.h"

using namespace clang::ast_matchers;

namespace clang::tidy::misra {

namespace custom {

AST_MATCHER_P(SwitchStmt, hasBody, clang::ast_matchers::internal::Matcher<Stmt>,
              InnerMatcher) {
  const Stmt *const Body = Node.getBody();
  return (Body != nullptr && InnerMatcher.matches(*Body, Finder, Builder));
}

} // namespace custom

void MissingCompoundCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
      ifStmt(hasThen(stmt(unless(compoundStmt())).bind("body"))).bind("parent"),
      this);
  Finder->addMatcher(
      ifStmt(
          hasElse(stmt(unless(anyOf(compoundStmt(), ifStmt()))).bind("body")))
          .bind("parent"),
      this);
  Finder->addMatcher(forStmt(hasBody(stmt(unless(compoundStmt())).bind("body")))
                         .bind("parent"),
                     this);
  Finder->addMatcher(
      whileStmt(hasBody(stmt(unless(compoundStmt())).bind("body")))
          .bind("parent"),
      this);
  Finder->addMatcher(
      doStmt(hasBody(stmt(unless(compoundStmt())).bind("body"))).bind("parent"),
      this);
  Finder->addMatcher(
      switchStmt(custom::hasBody(stmt(unless(compoundStmt())).bind("body")))
          .bind("parent"),
      this);
}

void MissingCompoundCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedParent = Result.Nodes.getNodeAs<Stmt>("parent");
  const auto *MatchedBody = Result.Nodes.getNodeAs<Stmt>("body");

  if (MatchedParent && MatchedBody) {
    diag(MatchedBody->getBeginLoc(), "missing compound statement",
         DiagnosticIDs::Warning);
    // diag(MatchedParent->getEndLoc(), "parent node", DiagnosticIDs::Note);
  }
}

void MissingCompoundCheck::diagBody(const Stmt *Body) {}

} // namespace clang::tidy::misra
