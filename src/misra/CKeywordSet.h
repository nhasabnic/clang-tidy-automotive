//===--- CKeywordSet.h - clang-tidy -----------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_CKEYWORDSET_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_CKEYWORDSET_H

#include "clang/Basic/LangOptions.h"
#include "clang/Basic/LangStandard.h"
#include "llvm/ADT/DenseSet.h"
#include "llvm/ADT/StringRef.h"

namespace clang::tidy::misra {

class CKeywordSet {
public:
  explicit CKeywordSet(const clang::LangOptions &LangOpts);

  bool isKeyword(llvm::StringRef Str) const;
  bool isDeprecated(llvm::StringRef Str) const;

private:
  const llvm::DenseSet<llvm::StringRef> *ActiveKeywords;
  const llvm::DenseSet<llvm::StringRef> *DeprecatedKeywords;
};

} // namespace clang::tidy::misra

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_CKEYWORDSET_H
