//===--- CommentComponent.h - clang-tidy ------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TIDY_AUTOMOTIVE_COMMENTCOMPONENT_H
#define LLVM_CLANG_TIDY_AUTOMOTIVE_COMMENTCOMPONENT_H

#include "../../ClangTidy.h"
#include "../../ClangTidyModule.h"
#include "../../ClangTidyModuleRegistry.h"

namespace clang::tidy::automotive {

class CommentComponent {
public:
  static void addCheckFactories(ClangTidyCheckFactories &CheckFactories);
};

} // namespace clang::tidy::automotive

#endif // LLVM_CLANG_TIDY_AUTOMOTIVE_COMMENTCOMPONENT_H
