//===--- AvoidMultipleHashOperatorsCheck.cpp - clang-tidy -----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "AvoidMultipleHashOperatorsCheck.h"
#include "clang/Basic/TokenKinds.h"
#include "clang/Lex/PPCallbacks.h"
#include "clang/Lex/Preprocessor.h"

using namespace clang::ast_matchers;

namespace clang::tidy::misra {

namespace {

class AvoidMultipleHashOperatorsPPCallbacks : public PPCallbacks {
public:
  AvoidMultipleHashOperatorsPPCallbacks(ClangTidyCheck &Check,
                                        clang::Preprocessor &PP)
      : Check(Check), SourceMgr(PP.getSourceManager()) {}

  void MacroDefined(const Token &MacroNameTok,
                    const MacroDirective *MD) override {
    const MacroInfo *MI = MD->getMacroInfo();
    if (!MI) {
      return;
    }

    const Token *PrevTok = nullptr;

    for (const Token &Tok : MI->tokens()) {
      if ((Tok.is(tok::hash)) || (Tok.is(tok::hashhash))) {
        if (PrevTok) {
          SourceLocation TokLoc = Tok.getLocation();
          SourceLocation PrevTokLoc = PrevTok->getLocation();
          auto TokSpelling = clang::tok::getPunctuatorSpelling(Tok.getKind());
          auto PrevTokSpelling =
              clang::tok::getPunctuatorSpelling(PrevTok->getKind());

          Check.diag(TokLoc, "avoid '%0' operator after '%1' operator")
              << TokSpelling << PrevTokSpelling;
          Check.diag(PrevTokLoc, "location of '%0' operator",
                     DiagnosticIDs::Note)
              << PrevTokSpelling;
        }
        PrevTok = &Tok;
      }
    }
  }

private:
  ClangTidyCheck &Check;
  const SourceManager &SourceMgr;
};

} // namespace

void AvoidMultipleHashOperatorsCheck::registerPPCallbacks(
    const SourceManager &SM, Preprocessor *PP, Preprocessor *ModuleExpanderPP) {
  PP->addPPCallbacks(
      std::make_unique<AvoidMultipleHashOperatorsPPCallbacks>(*this, *PP));
}

} // namespace clang::tidy::misra
