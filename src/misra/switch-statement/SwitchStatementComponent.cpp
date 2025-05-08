//===--- SwitchStatementComponent.cpp - clang-tidy ------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "SwitchStatementComponent.h"
#include "AvoidBooleanInSwitchCheck.h"
#include "MissingBreakInSwitchCheck.h"
#include "MissingDefaultInSwitchStatementCheck.h"
#include "UnstructuredSwitchCaseCheck.h"
#include "WrongOrderDefaultInSwitchStatementCheck.h"

namespace clang::tidy::misra {

void SwitchStatementComponent::addCheckFactories(
    ClangTidyCheckFactories &CheckFactories) {

  /* MISRA C 2023
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<MissingBreakInSwitchCheck>(
      "misra-c2023-req-16.3");
  CheckFactories.registerCheck<MissingDefaultInSwitchStatementCheck>(
      "misra-c2023-req-16.4");
  CheckFactories.registerCheck<WrongOrderDefaultInSwitchStatementCheck>(
      "misra-c2023-req-16.5");
  CheckFactories.registerCheck<AvoidBooleanInSwitchCheck>(
      "misra-c2023-req-16.7");
  CheckFactories.registerCheck<UnstructuredSwitchCaseCheck>("misra-x-req-16.2");
  /* 16.2 Inspiration: m
   * caseStmt(unless(hasParent(compoundStmt(hasParent(switchStmt()))))) */

  /* MISRA C 2012
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<MissingDefaultInSwitchStatementCheck>(
      "misra-c2012-req-16.4");
  CheckFactories.registerCheck<WrongOrderDefaultInSwitchStatementCheck>(
      "misra-c2012-req-16.5");
}

} // namespace clang::tidy::misra
