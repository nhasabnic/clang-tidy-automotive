#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_ABSTRACTCHECKAPIHANDLER_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_ABSTRACTCHECKAPIHANDLER_H

#include "clang/Basic/SourceLocation.h"
#include "clang/Lex/PPCallbacks.h"
#include "llvm/ADT/StringRef.h"

namespace clang::tidy::misra {

class MatchHeaderInfo {
public:
  const clang::SourceLocation Location;
  const Token &Tok;
  const StringRef Name;
  const bool IsAngled;
};

class MatchMacroInfo {
  const MatchHeaderInfo *Header;
  const Token &Tok;
  const StringRef Name;
};

class AbstractCheckApiHandler {
public:
  virtual ~AbstractCheckApiHandler() = default;

  virtual void checkHeader(const MatchHeaderInfo &Result) {}

  virtual void checkMacro(const MatchMacroInfo &Result) {}
};

} // namespace clang::tidy::misra

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_ABSTRACTCHECKAPIHANDLER_H
