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
      "automotive-avoid-macro-named-as-ckeyword");
  CheckFactories.registerCheck<PreprocessorFlowCheck>("preprocessor-flow");

  CheckFactories.registerCheck<UnusedMacroCheck>("automotive-unused-macro");
  CheckFactories.registerCheck<AvoidUndefCheck>("automotive-avoid-undef");
  CheckFactories.registerCheck<AvoidHashOperatorCheck>(
      "automotive-avoid-hash-operator");
  CheckFactories.registerCheck<AvoidMultipleHashOperatorsCheck>(
      "automotive-avoid-multiple-hash-operators");
}

} // namespace clang::tidy::automotive
