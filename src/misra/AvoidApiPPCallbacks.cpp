//===--- AvidApiPPCallbacks.cpp - clang-tidy ------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "AvoidApiPPCallbacks.h"
#include "llvm/ADT/STLExtras.h"

namespace clang::tidy::misra {

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
  // Kolla om det expanderade makrot finns i listan över förbjudna makron
  //  StringRef MacroName = MacroNameTok.getIdentifierInfo()->getName();
  //  if (llvm::is_contained(ForbiddenMacros, MacroName)) {
  //    Handler.handleMacroExpansion(MacroNameTok.getLocation(), MacroName,
  //    HeaderFile);
  //  }
}

} // namespace clang::tidy::misra
