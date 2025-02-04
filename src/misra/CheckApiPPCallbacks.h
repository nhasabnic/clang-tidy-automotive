#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_AVOIDAPIPPCALLBACKS_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_AVOIDAPIPPCALLBACKS_H

#include "AbstractCheckApiHandler.h"
#include "clang/Lex/PPCallbacks.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/StringRef.h"

namespace clang::tidy::misra {

class AvoidApiPPCallbacks : public PPCallbacks {
public:
  // Konstruktor som tar emot en AbstractAvoidApiHandler, en ArrayRef och en
  // valfri header-fil
  AvoidApiPPCallbacks(AbstractCheckApiHandler &Handler,
                      llvm::ArrayRef<llvm::StringRef> ForbiddenMacros,
                      llvm::StringRef HeaderFile = "")
      : Handler(Handler), ForbiddenMacros(ForbiddenMacros),
        HeaderFile(HeaderFile) {}

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
  AbstractCheckApiHandler &Handler; // Referens till hanteraren
  llvm::ArrayRef<llvm::StringRef>
      ForbiddenMacros;        // Referens till förbjudna makron
  llvm::StringRef HeaderFile; // Header-fil (kan vara tom)
  std::unique_ptr<MatchHeaderInfo> Header = nullptr;
};

} // namespace clang::tidy::misra

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_AVOIDAPIPPCALLBACKS_H
