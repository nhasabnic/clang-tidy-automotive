//===--- AbstractLabelCheck.h - clang-tidy ----------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_ABSTRACTLABELCHECK_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_ABSTRACTLABELCHECK_H

#include "../ClangTidyCheck.h"
#include "llvm/ADT/DenseMap.h"
#include "clang/Basic/SourceLocation.h"

namespace clang::tidy::misra {

struct LabelInfo {
  const LabelStmt *MatchedLabel = nullptr;
  const GotoStmt *MatchedGoto = nullptr;
  const FunctionDecl *LabelFunction = nullptr;
  const FunctionDecl *GotoFunction = nullptr;
  unsigned int GotoIndex = 0u;
  unsigned int LabelIndex = 0u;
};

/// FIXME: Write a short description.
///
/// For the user-facing documentation see:
/// http://clang.llvm.org/extra/clang-tidy/checks/misra/UnusedLabel.html
class AbstractLabelCheck : public ClangTidyCheck {
public:
  void registerMatchers(ast_matchers::MatchFinder *Finder) override;
  void check(const ast_matchers::MatchFinder::MatchResult &Result) override;

protected:
  AbstractLabelCheck(StringRef Name, ClangTidyContext *Context)
      : ClangTidyCheck(Name, Context) {}
  const llvm::DenseMap<llvm::StringRef, LabelInfo> &getLabelMap() const {
    return LabelMap;
  }

private:
  llvm::DenseMap<StringRef, LabelInfo> LabelMap;
  unsigned int Index;
};

} // namespace clang::tidy::misra

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_ABSTRACTLABELCHECK_H
