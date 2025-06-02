//===--- StatementComponent.cpp - clang-tidy ------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "StatementComponent.h"
#include "AvoidBooleanInSwitchCheck.h"
#include "MissingBreakInSwitchCheck.h"
#include "MissingDefaultInSwitchStatementCheck.h"
#include "UnstructuredSwitchCaseCheck.h"
#include "WrongOrderDefaultInSwitchStatementCheck.h"
#include "AvoidGotoCheck.h"
#include "ForwardGotoLabelCheck.h"
#include "UnusedLabelCheck.h"
#include "MissingCompoundCheck.h"
#include "MissingElseCheck.h"

namespace clang::tidy::automotive {

void StatementComponent::addCheckFactories(
    ClangTidyCheckFactories &CheckFactories) {

  CheckFactories.registerCheck<UnusedLabelCheck>("automotive-unused-label");
  CheckFactories.registerCheck<AvoidGotoCheck>("automotive-avoid-goto");
  CheckFactories.registerCheck<ForwardGotoLabelCheck>(
      "automotive-forward-goto-label");

  CheckFactories.registerCheck<MissingBreakInSwitchCheck>(
      "automotive-missing-break-in-switch-stmt");
  CheckFactories.registerCheck<MissingDefaultInSwitchStatementCheck>(
      "automotive-missing-default-in-switch-stmt");
  CheckFactories.registerCheck<WrongOrderDefaultInSwitchStatementCheck>(
      "automotive-c23-req-16.5");
  CheckFactories.registerCheck<AvoidBooleanInSwitchCheck>(
      "automotive-avoid-boolean-in-switch-stmt");
  CheckFactories.registerCheck<UnstructuredSwitchCaseCheck>(
      "automotive-x-req-16.2");
  /* 16.2 Inspiration: m
   * caseStmt(unless(hasParent(compoundStmt(hasParent(switchStmt()))))) */

    /* 15.
    ---------------------------------------------------------------- */
    CheckFactories.registerCheck<MissingCompoundCheck>(
        "automotive-c23-req-15.6");
    CheckFactories.registerCheck<MissingElseCheck>("automotive-c23-req-15.7");
}

} // namespace clang::tidy::automotive
