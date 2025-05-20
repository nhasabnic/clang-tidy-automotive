//===--- AvoidApiCheck.h - clang-tidy --------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_AVOIDAPICHECK_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_AVOIDAPICHECK_H

#include "../../ClangTidyCheck.h"
#include "AvoidApiHandler.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/StringRef.h"

namespace clang::tidy::misra {

/// FIXME: Write a short description.
///
/// For the user-facing documentation see:
/// http://clang.llvm.org/extra/clang-tidy/checks/misra/Avoid-Stdarg-Header.html
class AvoidApiCheck : public ClangTidyCheck {
public:
  void registerPPCallbacks(const SourceManager &SM, Preprocessor *PP,
                           Preprocessor *ModuleExpanderPP) override;
  void registerMatchers(ast_matchers::MatchFinder *Finder) override;
  void check(const ast_matchers::MatchFinder::MatchResult &Result) override;

protected:
  AvoidApiCheck(StringRef Name, ClangTidyContext *Context, StringRef Header,
                const std::initializer_list<llvm::StringRef> &FunctionNames)
      : ClangTidyCheck(Name, Context) {}
  AvoidApiCheck(StringRef Name, ClangTidyContext *Context,
                const std::initializer_list<llvm::StringRef> &FunctionNames)
      : ClangTidyCheck(Name, Context) {}

  AvoidApiCheck(StringRef Name, ClangTidyContext *Context, StringRef HeaderName,
                ArrayRef<StringRef> FunctionNames)
      : ClangTidyCheck(Name, Context), FunctionNames(FunctionNames),
        HeaderName(HeaderName) {}

private:
  ArrayRef<StringRef> FunctionNames;
  StringRef HeaderName;
};

} // namespace clang::tidy::misra

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_AVOIDAPICHECK_H
