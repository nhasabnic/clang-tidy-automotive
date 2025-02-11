//===--- UnterminatedEscapeSequenceCheck.cpp - clang-tidy -----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "UnterminatedEscapeSequenceCheck.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang::tidy::misra {

void UnterminatedEscapeSequenceCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(stringLiteral().bind("string"), this);
  Finder->addMatcher(characterLiteral().bind("char"), this);
}

void UnterminatedEscapeSequenceCheck::check(
    const MatchFinder::MatchResult &Result) {
  const auto *MatchedStringLiteral =
      Result.Nodes.getNodeAs<StringLiteral>("string");
  const auto *MatchedCharLiteral =
      Result.Nodes.getNodeAs<CharacterLiteral>("char");

  if (MatchedStringLiteral) {
    StringRef MatchedStringRef = MatchedStringLiteral->getBytes();
    // TODO
  }

  if (MatchedCharLiteral) {
    char CharValue = MatchedCharLiteral->getValue();
    // TODO
  }
}

} // namespace clang::tidy::misra
