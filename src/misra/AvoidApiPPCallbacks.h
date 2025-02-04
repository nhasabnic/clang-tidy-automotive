//===--- AvoidApiPPCallbacks.h - clang-tidy ---------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_AVOIDAPIPPCALLBACKS_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_AVOIDAPIPPCALLBACKS_H

// #include "AvoidApiHandler.h"
#include "clang/Lex/PPCallbacks.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/StringRef.h"

namespace clang::tidy::misra {

class AvoidApiPPCallbacks : public PPCallbacks {
public:
  AvoidApiPPCallbacks() {}

  void InclusionDirective(SourceLocation DirectiveLoc,
                          const Token &IncludeToken, StringRef IncludedFilename,
                          bool IsAngled, CharSourceRange FilenameRange,
                          OptionalFileEntryRef IncludedFile,
                          StringRef SearchPath, StringRef RelativePath,
                          const Module *SuggestedModule, bool ModuleImported,
                          SrcMgr::CharacteristicKind FileType) override;

  void MacroExpands(const Token &MacroNameTok, const MacroDefinition &MD,
                    SourceRange Range, const MacroArgs *Args) override;
};

} // namespace clang::tidy::misra

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_AVOIDAPIPPCALLBACKS_H
