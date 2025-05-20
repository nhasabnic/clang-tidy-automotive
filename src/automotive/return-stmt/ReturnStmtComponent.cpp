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

namespace clang::tidy::automotive {

void ReturnStmtComponent::addCheckFactories(
    ClangTidyCheckFactories &CheckFactories) {

  /* C 2023
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<MultipleReturnStmtCheck>("automotive-c23-adv-15.5");
  CheckFactories.registerCheck<MissingReturnValueHandlingCheck>(
      "automotive-c23-req-17.7");
  CheckFactories.registerCheck<NoReturnVoidCheck>("automotive-c23-req-17.10");

  /* C 2012
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<MultipleReturnStmtCheck>("automotive-c12-adv-15.5");
}

} // namespace clang::tidy::automotive
