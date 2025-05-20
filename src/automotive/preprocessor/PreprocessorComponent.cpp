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

namespace clang::tidy::automotive {

void PreprocessorComponent::addCheckFactories(
    ClangTidyCheckFactories &CheckFactories) {

  CheckFactories.registerCheck<AvoidMacroNamedAsCkeywordCheck>(
      "automotive-x-req-20.4");
  CheckFactories.registerCheck<PreprocessorFlowCheck>("automotive-x-req-20.14");

  /* C 2023
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<UnusedMacroCheck>("automotive-c23-adv-2.5");
  CheckFactories.registerCheck<AvoidUndefCheck>("automotive-c23-adv-20.5");
  CheckFactories.registerCheck<AvoidHashOperatorCheck>("automotive-c23-adv-20.10");
  CheckFactories.registerCheck<AvoidMultipleHashOperatorsCheck>(
      "automotive-c23-req-20.11");

  /* C 2012
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<UnusedMacroCheck>("automotive-c12-adv-2.5");
  CheckFactories.registerCheck<AvoidHashOperatorCheck>("automotive-c12-adv-20.10");
}

} // namespace clang::tidy::automotive
