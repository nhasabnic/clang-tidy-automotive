//===--- AvoidLowercaseLiteralSuffixCheck.cpp - clang-tidy ----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "AvoidLowercaseLiteralSuffixCheck.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Lex/Lexer.h"

using namespace clang::ast_matchers;

namespace clang::tidy::automotive {

void AvoidLowercaseLiteralSuffixCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(expr(anyOf(integerLiteral().bind("literal"),
                                floatLiteral().bind("literal"))),
                     this);
}

void AvoidLowercaseLiteralSuffixCheck::check(
    const MatchFinder::MatchResult &Result) {
  const auto *MatchedLiteral = Result.Nodes.getNodeAs<Expr>("literal");

  if (!MatchedLiteral)
    return;

  SourceRange Range = MatchedLiteral->getSourceRange();
  SourceManager &SM = *Result.SourceManager;
  LangOptions LangOpts = Result.Context->getLangOpts();
  StringRef LiteralText =
      Lexer::getSourceText(CharSourceRange::getTokenRange(Range), SM, LangOpts);

  if (!LiteralText.empty()) {
    static constexpr char Digits[] = "0123456789";
    size_t SuffixStart = LiteralText.find_last_of(Digits) + 1;

    for (size_t Index = SuffixStart; Index < LiteralText.size(); ++Index) {
      char Ch = LiteralText[Index];

      if (Ch == 'l') {
        auto SuffixLoc =
            MatchedLiteral->getBeginLoc().getLocWithOffset(SuffixStart);
        diag(SuffixLoc, "avoid lowercase 'l' in a literal suffix");
        return;
      }
    }
  }
}

} // namespace clang::tidy::automotive
