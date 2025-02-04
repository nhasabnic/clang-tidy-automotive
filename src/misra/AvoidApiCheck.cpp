//===--- AvoidApiCheck.cpp - clang-tidy ----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "AvoidApiCheck.h"
#include "AvoidApiPPCallbacks.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

namespace clang::tidy::misra {

using namespace clang::ast_matchers;

void AvoidApiCheck::registerPPCallbacks(
    const SourceManager &SM, Preprocessor *PP, Preprocessor *ModuleExpanderPP) {
  //  PP->addPPCallbacks(std::make_unique<AvoidApiPPCallbacks>(
  //      *this, *PP, Header, FunctionNames));
}

void AvoidApiCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(callExpr(callee(functionDecl(hasAnyName(FunctionNames))))
                         .bind("functionCall"),
                     this);
}

void AvoidApiCheck::check(const MatchFinder::MatchResult &Result) {
  // Hantera matchningar från AST-matchern
  if (const auto *Call = Result.Nodes.getNodeAs<CallExpr>("functionCall")) {
    const FunctionDecl *Func = Call->getDirectCallee();
    if (Func) {
      diag(Call->getBeginLoc(), "Avoid function '%0'") << Func->getName();
    }
  }
}

} // namespace clang::tidy::misra
