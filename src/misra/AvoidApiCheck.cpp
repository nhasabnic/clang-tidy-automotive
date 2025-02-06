//===--- AvoidApiCheck.cpp - clang-tidy ----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "AvoidApiCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Lex/PPCallbacks.h"
#include "clang/Lex/Preprocessor.h"

namespace clang::tidy::misra {

using namespace clang::ast_matchers;

class AvoidApiPPCallbacks : public PPCallbacks {
public:
  AvoidApiPPCallbacks(AvoidApiCheck &Check, StringRef HeaderName,
                      ArrayRef<StringRef> MacroNames)
      : Check(Check), MacroNames(MacroNames), HeaderName(HeaderName) {}

  void InclusionDirective(SourceLocation DirectiveLoc,
                          const Token &IncludeToken, StringRef IncludedFilename,
                          bool IsAngled, CharSourceRange FilenameRange,
                          OptionalFileEntryRef IncludedFile,
                          StringRef SearchPath, StringRef RelativePath,
                          const Module *SuggestedModule, bool ModuleImported,
                          SrcMgr::CharacteristicKind FileType) override;

  void MacroExpands(const Token &MacroNameTok, const MacroDefinition &MD,
                    SourceRange Range, const MacroArgs *Args) override;

private:
  AvoidApiCheck &Check;
  ArrayRef<StringRef> MacroNames;
  StringRef HeaderName;
};

void AvoidApiCheck::registerPPCallbacks(const SourceManager &SM,
                                        Preprocessor *PP,
                                        Preprocessor *ModuleExpanderPP) {

  PP->addPPCallbacks(
      std::make_unique<AvoidApiPPCallbacks>(*this, HeaderName, FunctionNames));
}

void AvoidApiCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(callExpr(callee(functionDecl(hasAnyName(FunctionNames))))
                         .bind("functionCall"),
                     this);
}

void AvoidApiCheck::check(const MatchFinder::MatchResult &Result) {
  // Hantera matchningar från AST-matchern
  /*  if (const auto *Call = Result.Nodes.getNodeAs<CallExpr>("functionCall")) {
      const FunctionDecl *Func = Call->getDirectCallee();
      if (Func) {
        diag(Call->getBeginLoc(), "Avoid function '%0'") << Func->getName();
      }
    }*/
}

void AvoidApiPPCallbacks::InclusionDirective(
    SourceLocation DirectiveLoc, const Token &IncludeToken,
    StringRef IncludedFilename, bool IsAngled, CharSourceRange FilenameRange,
    OptionalFileEntryRef IncludedFile, StringRef SearchPath,
    StringRef RelativePath, const Module *SuggestedModule, bool ModuleImported,
    SrcMgr::CharacteristicKind FileType) {

  /*  if (!HeaderFile.empty() && FileName.equals(HeaderFile)) {
      //    Handler.handleInclusionDirective(HashLoc, FileName, IsAngled);
    }*/
}

void AvoidApiPPCallbacks::MacroExpands(const Token &MacroNameTok,
                                       const MacroDefinition &MD,
                                       SourceRange Range,
                                       const MacroArgs *Args) {
  // Kolla om det expanderade makrot finns i listan   ver f  rbjudna makron
  //  StringRef MacroName = MacroNameTok.getIdentifierInfo()->getName();
  //  if (llvm::is_contained(ForbiddenMacros, MacroName)) {
  //    Handler.handleMacroExpansion(MacroNameTok.getLocation(), MacroName,
  //    HeaderFile);
  //  }
}

} // namespace clang::tidy::misra
