//===--- Utils.h - clang-tidy ----------------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_UTILS_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_UTILS_H

#include "clang/ASTMatchers/ASTMatchers.h"

namespace clang::tidy::misra {

namespace utils {

static bool isLanguageC90(const LangOptions &LangOpts) {
  return !LangOpts.C99 && !LangOpts.C11 && !LangOpts.C17 && !LangOpts.C23 &&
         !LangOpts.CPlusPlus;
}

} // namespace utils

} // namespace clang::tidy::misra

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_UTILS_H
