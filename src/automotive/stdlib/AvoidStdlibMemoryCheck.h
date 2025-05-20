//===--- AvoidStdlibMemoryCheck.h - clang-tidy ------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_AUTOMOTIVE_AVOIDSTDLIBMEMORYCHECK_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_AUTOMOTIVE_AVOIDSTDLIBMEMORYCHECK_H

#include "AvoidApiCheck.h"

namespace clang::tidy::automotive {

/// FIXME: Write a short description.
///
/// For the user-facing documentation see:
/// http://clang.llvm.org/extra/clang-tidy/checks/misra/avoid-setjmp.html
class AvoidStdlibMemoryCheck : public AvoidApiCheck {
public:
  AvoidStdlibMemoryCheck(StringRef Name, ClangTidyContext *Context)
      : AvoidApiCheck(
            Name, Context, "pelle.h",
            {"calloc", "malloc", "realloc", "aligned_alloc", "free"}) {}
};

} // namespace clang::tidy::automotive

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_AUTOMOTIVE_AVOIDSTDLIBMEMORYCHECK_H
