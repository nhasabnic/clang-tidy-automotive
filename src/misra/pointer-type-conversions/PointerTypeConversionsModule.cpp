//===--- PointerTypeConversionsModule.cpp - clang-tidy --------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "PointerTypeConversionsModule.h"
#include "AvoidAtomicVoidPointerCheck.h"
#include "WrongNullPointerValueCheck.h"

namespace clang::tidy::misra {

void PointerTypeConversionsModule::addCheckFactories(ClangTidyCheckFactories &CheckFactories) {

  /* MISRA C 2023
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<WrongNullPointerValueCheck>(
        "misra-c2023-req-11.9");
  /* 11.10: Diagnostic error */

  /* MISRA C 2012
  ------------------------------------------------------------------ */

}

} // namespace clang::tidy::misra
