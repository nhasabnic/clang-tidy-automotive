//===--- OperatorComponent.cpp - clang-tidy -------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "OperatorComponent.h"
#include "AvoidCommaOperatorCheck.h"

namespace clang::tidy::automotive {

void OperatorComponent::addCheckFactories(
    ClangTidyCheckFactories &CheckFactories) {

  /* C 2023
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<AvoidCommaOperatorCheck>(
      "automotive-c23-adv-12.3");

  /* C 2012
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<AvoidCommaOperatorCheck>(
      "automotive-c12-adv-12.3");
}

} // namespace clang::tidy::automotive
