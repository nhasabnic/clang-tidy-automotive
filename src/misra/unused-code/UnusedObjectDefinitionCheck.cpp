//===--- UnusedObjectDefinitionCheck.cpp - clang-tidy ---------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "UnusedObjectDefinitionCheck.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang::tidy::misra {

void UnusedObjectDefinitionCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(varDecl(isDefinition(), hasLocalStorage(),
                             unless(parmVarDecl()), unless(isImplicit()))
                         .bind("unusedVar"),
                     this);

  Finder->addMatcher(varDecl(hasGlobalStorage(), isStaticStorageClass())
                         .bind("unusedStaticVar"),
                     this);
}

void UnusedObjectDefinitionCheck::check(
    const MatchFinder::MatchResult &Result) {
  const auto *Var = Result.Nodes.getNodeAs<VarDecl>("unusedVar");
  const auto *StaticVar = Result.Nodes.getNodeAs<VarDecl>("unusedStaticVar");

  if (Var && !Var->isUsed()) {
    diag(Var->getLocation(), "unused object definition '%0'") << Var->getName();
  }

  if (StaticVar && !StaticVar->isUsed()) {
    diag(StaticVar->getLocation(), "unused static object definition '%0'")
        << StaticVar->getName();
  }
}

} // namespace clang::tidy::misra
