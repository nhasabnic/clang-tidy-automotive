//===--- TokenRange.h - clang-tidy -----------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_TOKENRANGE_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_TOKENRANGE_H

#include "clang/Basic/AttrKinds.h"
#include "clang/Basic/CharInfo.h"
#include "clang/Basic/IdentifierTable.h"
#include "clang/Basic/LangOptions.h"
#include "clang/Basic/SourceManager.h"
#include "clang/Basic/TargetInfo.h"
#include "clang/Lex/Lexer.h"
#include <optional>

namespace clang::tidy::misra {

class TokenRange {
public:
  class TokenIterator;

  TokenRange(SourceLocation StartLoc, SourceLocation EndLoc,
             const SourceManager &SM, const LangOptions &LangOpts)
      : StartIterator(
            TokenIterator(StartLoc.getLocWithOffset(-1), SM, LangOpts)),
        EndIterator(TokenIterator(EndLoc, SM, LangOpts)) {}

  class TokenIterator {
  public:
    using iterator_category = std::input_iterator_tag;

    TokenIterator(SourceLocation CurrentLoc, const SourceManager &SM,
                  const LangOptions &LangOpts)
        : SM(SM), LangOpts(LangOpts), CurrentLoc(CurrentLoc) {}

    std::optional<Token> operator*() const {
      auto Tok = Lexer::findNextToken(CurrentLoc, SM, LangOpts);
      if (Tok) {
        NextLoc = Tok->getLocation();
      } else {
        NextLoc = SourceLocation();
      }
      return Tok;
    }

    TokenIterator &operator++() {
      CurrentLoc = NextLoc;
      return *this;
    }

    bool operator!=(const TokenIterator &Other) const {
      return SM.isBeforeInTranslationUnit(NextLoc, Other.CurrentLoc);
    }

  protected:
    const SourceManager &SM;
    const LangOptions &LangOpts;
    SourceLocation CurrentLoc;
    mutable SourceLocation NextLoc;
  };

  TokenIterator begin() const { return StartIterator; }
  TokenIterator end() const { return EndIterator; }

private:
  TokenIterator StartIterator;
  TokenIterator EndIterator;
};

} // namespace clang::tidy::misra

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_TOKENRANGE_H
