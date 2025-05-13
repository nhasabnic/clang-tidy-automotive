//===--- AvoidPreprocessorHashOperatorCheck.cpp - clang-tidy --------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "AvoidPreprocessorHashOperatorCheck.h"
#include "clang/Basic/TokenKinds.h"
#include "clang/Lex/PPCallbacks.h"
#include "clang/Lex/Preprocessor.h"

using namespace clang::ast_matchers;

namespace clang::tidy::misra {

namespace {

class AvoidPreprocessorHashOperatorCallbacks : public PPCallbacks {
public:
  AvoidPreprocessorHashOperatorCallbacks(ClangTidyCheck &Check,
                                         clang::Preprocessor &PP)
      : Check(Check), SourceMgr(PP.getSourceManager()) {}

  void MacroDefined(const Token &MacroNameTok,
                    const MacroDirective *MD) override {
    const MacroInfo *MI = MD->getMacroInfo();
    if (!MI)
      return;

    for (const Token &Tok : MI->tokens()) {
      if (Tok.is(tok::hash) || Tok.is(tok::hashhash)) {
        SourceLocation Loc = Tok.getLocation();
        Check.diag(Loc, "avoid preprocessor operator '%0'")
            << clang::tok::getPunctuatorSpelling(Tok.getKind());
      }
    }
  }

private:
  ClangTidyCheck &Check;
  const SourceManager &SourceMgr;
};

} // namespace

void AvoidPreprocessorHashOperatorCheck::registerPPCallbacks(
    const SourceManager &SM, Preprocessor *PP, Preprocessor *ModuleExpanderPP) {
  PP->addPPCallbacks(
      std::make_unique<AvoidPreprocessorHashOperatorCallbacks>(*this, *PP));
}

} // namespace clang::tidy::misra
