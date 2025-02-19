//===--- UnusedMacroCheck.cpp - clang-tidy --------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "UnusedMacroCheck.h"
#include "clang/Lex/Preprocessor.h"

namespace clang::tidy::misra {

class UnusedMacroPPCallbacks : public PPCallbacks {
public:
  explicit UnusedMacroPPCallbacks(UnusedMacroCheck &Check,
                                  const SourceManager &SM)
      : Check(Check), SM(SM) {}

  void MacroDefined(const Token &MacroNameTok,
                    const MacroDirective *MD) override {
    StringRef MacroName = MacroNameTok.getIdentifierInfo()->getName();
    SourceLocation Loc = MacroNameTok.getLocation();
    MacroUsage[MacroName] = {false, Loc};
  }

  void MacroExpands(const Token &MacroNameTok, const MacroDefinition &MD,
                    SourceRange Range, const MacroArgs *Args) override {
    StringRef MacroName = MacroNameTok.getIdentifierInfo()->getName();
    MacroUsage[MacroName].first = true;
  }

  void MacroUndefined(const Token &MacroNameTok, const MacroDefinition &MD,
                      const MacroDirective *Undef) override {
    StringRef MacroName = MacroNameTok.getIdentifierInfo()->getName();
    MacroUsage[MacroName].first = true;
  }

  void EndOfMainFile() override {
    for (const auto &Entry : MacroUsage) {
      if (!Entry.getValue().first) {
        SourceLocation Loc = Entry.getValue().second;
        Check.diag(Loc, "unused macro definition '%0'") << Entry.getKey();
      }
    }
  }

private:
  UnusedMacroCheck &Check;
  const SourceManager &SM;
  llvm::StringMap<std::pair<bool, SourceLocation>> MacroUsage;
};

void UnusedMacroCheck::registerPPCallbacks(const SourceManager &SM,
                                           Preprocessor *PP,
                                           Preprocessor *ModuleExpanderPP) {
  PP->addPPCallbacks(std::make_unique<UnusedMacroPPCallbacks>(*this, SM));
}

} // namespace clang::tidy::misra
