//===--- AvoidAtomicVoidPointerCheck.cpp - clang-tidy ---------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "AvoidAtomicVoidPointerCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang::tidy::misra {

void AvoidAtomicVoidPointerCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(varDecl(hasType(pointerType(pointee(atomicType())))).bind("atomicPointer"), this);
}

void AvoidAtomicVoidPointerCheck::check(const MatchFinder::MatchResult &Result) {
    if (const auto *Var = Result.Nodes.getNodeAs<VarDecl>("atomicPointer")) {
        diag(Var->getLocation(), "Variable '%0' is a pointer to a _Atomic type")
             << Var->getName();
    }

}

} // namespace clang::tidy::misra
