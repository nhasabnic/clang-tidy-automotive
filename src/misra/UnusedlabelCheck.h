//===--- UnusedlabelCheck.h - clang-tidy ------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_UNUSEDLABELCHECK_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_UNUSEDLABELCHECK_H

#include "AbstractLabelCheck.h"

namespace clang::tidy::misra {

/// FIXME: Write a short description.
///
/// For the user-facing documentation see:
/// http://clang.llvm.org/extra/clang-tidy/checks/misra/UnusedLabel.html
class UnusedlabelCheck : public AbstractLabelCheck {
public:
  UnusedlabelCheck(StringRef Name, ClangTidyContext *Context)
      : AbstractLabelCheck(Name, Context) {}
  ~UnusedlabelCheck();
};

} // namespace clang::tidy::misra

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_UNUSEDLABELCHECK_H
