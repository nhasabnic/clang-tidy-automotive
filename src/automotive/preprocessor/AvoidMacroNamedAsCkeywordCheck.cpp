//===--- AvoidMacroNamedAsCkeywordCheck.cpp - clang-tidy ------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "AvoidMacroNamedAsCkeywordCheck.h"
#include "../utils/CKeywordSet.h"
#include "clang/Lex/PPCallbacks.h"
#include "clang/Lex/Preprocessor.h"
using namespace clang::ast_matchers;

namespace clang::tidy::misra {

namespace {

class AvoidMacroNamedAsCkeywordPPCallbacks : public PPCallbacks {
public:
  AvoidMacroNamedAsCkeywordPPCallbacks(Preprocessor &PP, ClangTidyCheck &Check)
      : PP(PP), CKeywords(PP.getLangOpts()), Check(Check) {}

  void MacroDefined(const Token &MacroNameTok,
                    const MacroDirective *MD) override {
    StringRef MacroName = MacroNameTok.getIdentifierInfo()->getName();

    if (CKeywords.isKeyword(MacroName)) {
      Check.diag(MacroNameTok.getLocation(),
                 "macro name '%0' conflicts with C keyword")
          << MacroName;
    }
  }

private:
  Preprocessor &PP;
  CKeywordSet CKeywords;
  ClangTidyCheck &Check;
};

} // anonymous namespace

void AvoidMacroNamedAsCkeywordCheck::registerPPCallbacks(
    const SourceManager &SM, Preprocessor *PP, Preprocessor *ModuleExpanderPP) {
  PP->addPPCallbacks(
      std::make_unique<AvoidMacroNamedAsCkeywordPPCallbacks>(*PP, *this));
}

} // namespace clang::tidy::misra
