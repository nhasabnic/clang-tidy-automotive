//===--- ReturnStmtComponent.cpp - clang-tidy -----------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "ReturnStmtComponent.h"
#include "MissingReturnValueHandlingCheck.h"
#include "MultipleReturnStmtCheck.h"
#include "NoReturnVoidCheck.h"

namespace clang::tidy::misra {

void ReturnStmtComponent::addCheckFactories(
    ClangTidyCheckFactories &CheckFactories) {

  /* MISRA C 2023
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<MultipleReturnStmtCheck>("misra-c2023-adv-15.5");
  CheckFactories.registerCheck<MissingReturnValueHandlingCheck>(
      "misra-c2023-req-17.7");
  CheckFactories.registerCheck<NoReturnVoidCheck>("misra-c2023-req-17.10");

  /* MISRA C 2012
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<MultipleReturnStmtCheck>("misra-c2012-adv-15.5");
}

} // namespace clang::tidy::misra
