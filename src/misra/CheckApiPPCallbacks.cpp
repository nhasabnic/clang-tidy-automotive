#include "CheckApiPPCallbacks.h"
#include "llvm/ADT/STLExtras.h"

namespace clang::tidy::misra {

void AvoidApiPPCallbacks::InclusionDirective(
    SourceLocation HashLoc, const Token &IncludeTok, StringRef FileName,
    bool IsAngled, CharSourceRange FilenameRange, OptionalFileEntryRef File,
    StringRef SearchPath, StringRef RelativePath, const Module *Imported,
    SrcMgr::CharacteristicKind FileType) {
  // Kolla om den inkluderade headern matchar den förbjudna headern
  if (!HeaderFile.empty() && FileName.equals(HeaderFile)) {
    //    Handler.handleInclusionDirective(HashLoc, FileName, IsAngled);
  }
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
