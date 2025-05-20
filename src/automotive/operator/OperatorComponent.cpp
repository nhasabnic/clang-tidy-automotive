//===--- OperatorComponent.cpp - clang-tidy -------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "OperatorComponent.h"
#include "AvoidCommaOperatorCheck.h"

namespace clang::tidy::misra {

void OperatorComponent::addCheckFactories(
    ClangTidyCheckFactories &CheckFactories) {

  /* MISRA C 2023
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<AvoidCommaOperatorCheck>("misra-c2023-adv-12.3");

  /* MISRA C 2012
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<AvoidCommaOperatorCheck>("misra-c2012-adv-12.3");
}

} // namespace clang::tidy::misra
