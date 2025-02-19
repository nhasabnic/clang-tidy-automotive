//===--- UnterminatedEscapeSequenceCheck.cpp - clang-tidy -----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "UnterminatedEscapeSequenceCheck.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "llvm/Support/Regex.h"

using namespace clang::ast_matchers;

namespace clang::tidy::misra {

void UnterminatedEscapeSequenceCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(stringLiteral().bind("stringLiteral"), this);
  Finder->addMatcher(characterLiteral().bind("charLiteral"), this);
}

void UnterminatedEscapeSequenceCheck::check(
    const ast_matchers::MatchFinder::MatchResult &Result) {
  if (const auto *MatchString =
          Result.Nodes.getNodeAs<StringLiteral>("stringLiteral")) {
    checkEscapeSequences(MatchString->getString(), MatchString->getBeginLoc());

  } else if (const auto *MatchChar =
                 Result.Nodes.getNodeAs<CharacterLiteral>("charLiteral")) {
    char Value = MatchChar->getValue();
    checkEscapeSequences(StringRef(&Value, 1), MatchChar->getBeginLoc());

  } else {
    /* Intentionally left empty. */
  }
}

void UnterminatedEscapeSequenceCheck::checkEscapeSequences(StringRef Str,
                                                           SourceLocation Loc) {
  // TODO
}

} // namespace clang::tidy::misra
