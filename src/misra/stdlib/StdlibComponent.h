//===--- StdlibComponent.h - clang-tidy -------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TIDY_MISRA_STDLIBCOMPONENT_H
#define LLVM_CLANG_TIDY_MISRA_STDLIBCOMPONENT_H

#include "../../ClangTidy.h"
#include "../../ClangTidyModule.h"
#include "../../ClangTidyModuleRegistry.h"

namespace clang::tidy::misra {

class StdlibComponent {
public:
  static void addCheckFactories(ClangTidyCheckFactories &CheckFactories);
};

} // namespace clang::tidy::misra

#endif // LLVM_CLANG_TIDY_MISRA_STDLIBCOMPONENT_H
