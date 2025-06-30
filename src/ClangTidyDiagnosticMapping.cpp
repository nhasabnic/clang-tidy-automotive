//===--- tools/extra/clang-tidy/ClangTidyDiagnosticMapping.cpp -----------=== //
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "ClangTidyDiagnosticMapping.h"
#include "ClangTidy.h"
#include "clang/Basic/DiagnosticIDs.h"

namespace clang::tidy {

void ClangTidyDiagnosticMapping::clear() { DiagConsumer.clear(); }

void ClangTidyDiagnosticMapping::BeginSourceFile(const LangOptions &LangOpts,
                                                 const Preprocessor *PP) {
  DiagConsumer.BeginSourceFile(LangOpts, PP);
}

void ClangTidyDiagnosticMapping::EndSourceFile() {
  DiagConsumer.EndSourceFile();
}

void ClangTidyDiagnosticMapping::finish() { DiagConsumer.finish(); }

bool ClangTidyDiagnosticMapping::IncludeInDiagnosticCounts() const {
  return DiagConsumer.IncludeInDiagnosticCounts();
}

void ClangTidyDiagnosticMapping::HandleDiagnostic(
    DiagnosticsEngine::Level DiagLevel, const Diagnostic &Info) {
 
  if (Context.DiagEngine) {
#if 0 //Broken
     DiagnosticIDs::Level Level = DiagnosticIDs::Warning;
     unsigned ID = Context.DiagEngine->getDiagnosticIDs()->getCustomDiagID(Level, llvm::StringRef("Testing Testing"));
     Context.DiagEngine->Report(Info.getLocation(), ID);

    llvm::outs() << Info.getID() << " " << Context.getCheckName(Info.getID()) << "\n";
   
  } else {
    llvm::outs() << "Fail: " << Info.getID() << " " << "\n";
  }
#endif
  DiagConsumer.HandleDiagnostic(DiagLevel, Info);
  DiagnosticConsumer::HandleDiagnostic(DiagLevel, Info);
}

} // namespace clang::tidy
