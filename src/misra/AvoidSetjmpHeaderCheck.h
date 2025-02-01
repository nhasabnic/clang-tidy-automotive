//===--- SetjmpCheck.h - clang-tidy ----------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_SETJMPCHECK_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_SETJMPCHECK_H

#include "AbstractAvoidApiCheck.h"

namespace clang::tidy::misra {

/// FIXME: Write a short description.
///
/// For the user-facing documentation see:
/// http://clang.llvm.org/extra/clang-tidy/checks/misra/avoid-setjmp.html
class AvoidSetjmpHeaderCheck : public AbstractAvoidApiCheck {
public:
  AvoidSetjmpHeaderCheck(StringRef Name, ClangTidyContext *Context)
      : AbstractAvoidApiCheck(Name, Context, "setjmp.h", {"setjmp", "longjmp"}) {
  }
};

} // namespace clang::tidy::misra

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_SETJMPCHECK_H
