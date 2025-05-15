//===--- PreprocessorComponent.cpp - clang-tidy ---------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "PreprocessorComponent.h"
#include "AvoidHashOperatorCheck.h"
#include "AvoidMacroNamedAsCkeywordCheck.h"
#include "AvoidMultipleHashOperatorsCheck.h"
#include "AvoidUndefCheck.h"
#include "PreprocessorFlowCheck.h"
#include "UnusedMacroCheck.h"

namespace clang::tidy::misra {

void PreprocessorComponent::addCheckFactories(
    ClangTidyCheckFactories &CheckFactories) {

  CheckFactories.registerCheck<AvoidMacroNamedAsCkeywordCheck>(
      "misra-x-req-20.4");
  CheckFactories.registerCheck<PreprocessorFlowCheck>("misra-x-req-20.14");

  /* MISRA C 2023
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<UnusedMacroCheck>("misra-c2023-adv-2.5");
  CheckFactories.registerCheck<AvoidUndefCheck>("misra-c2023-adv-20.5");
  CheckFactories.registerCheck<AvoidHashOperatorCheck>(
      "misra-c2023-adv-20.10");
  CheckFactories.registerCheck<AvoidMultipleHashOperatorsCheck>(
      "misra-c2023-req-20.11");

  /* MISRA C 2012
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<UnusedMacroCheck>("misra-c2012-adv-2.5");
  CheckFactories.registerCheck<AvoidHashOperatorCheck>(
      "misra-c2012-adv-20.10");
}

} // namespace clang::tidy::misra
