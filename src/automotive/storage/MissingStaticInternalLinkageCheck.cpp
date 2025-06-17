//===--- MissingStaticInternalLinkageCheck.cpp - clang-tidy ---------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "MissingStaticInternalLinkageCheck.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang::tidy::automotive {

AST_MATCHER(NamedDecl, hasInternalLinkage) {
  return Node.getFormalLinkage() == Linkage::None;
}

void MissingStaticInternalLinkageCheck::registerMatchers(MatchFinder *Finder) {
#if NOT_WORKING_AT_THE_MOMENT
  Finder->addMatcher(varDecl(unless(isStaticStorageClass())).bind("var"), this);
  Finder->addMatcher(functionDecl(unless(isStaticStorageClass())).bind("func"),
                     this);
#endif
}

void MissingStaticInternalLinkageCheck::check(
    const MatchFinder::MatchResult &Result) {
#if NOT_WORKING_AT_THE_MOMENT
  if (const auto *Var = Result.Nodes.getNodeAs<VarDecl>("var")) {
    diag(Var->getLocation(),
        << Var->getName();
    diag(Var->getLocation(), "Link %0") << (int)Var->getVisibility();
  }

  if (const auto *Func = Result.Nodes.getNodeAs<FunctionDecl>("func")) {
    diag(Func->getLocation(),
         "Function with internal linkage should use 'static': '%0'")
        << Func->getName();
    diag(Func->getLocation(), "Link %0") << (int)Func->getVisibility();
  }
#endif
}

} // namespace clang::tidy::automotive
