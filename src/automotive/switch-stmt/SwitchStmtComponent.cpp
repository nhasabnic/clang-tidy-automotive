//===--- SwitchStmtComponent.cpp - clang-tidy -----------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "SwitchStmtComponent.h"
#include "AvoidBooleanInSwitchCheck.h"
#include "MissingBreakInSwitchCheck.h"
#include "MissingDefaultInSwitchStatementCheck.h"
#include "UnstructuredSwitchCaseCheck.h"
#include "WrongOrderDefaultInSwitchStatementCheck.h"

namespace clang::tidy::automotive {

void SwitchStmtComponent::addCheckFactories(
    ClangTidyCheckFactories &CheckFactories) {

  /* C 2023
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<MissingBreakInSwitchCheck>(
      "automotive-c23-req-16.3");
  CheckFactories.registerCheck<MissingDefaultInSwitchStatementCheck>(
      "automotive-c23-req-16.4");
  CheckFactories.registerCheck<WrongOrderDefaultInSwitchStatementCheck>(
      "automotive-c23-req-16.5");
  CheckFactories.registerCheck<AvoidBooleanInSwitchCheck>(
      "automotive-c23-req-16.7");
  CheckFactories.registerCheck<UnstructuredSwitchCaseCheck>(
      "automotive-x-req-16.2");
  /* 16.2 Inspiration: m
   * caseStmt(unless(hasParent(compoundStmt(hasParent(switchStmt()))))) */

  /* C 2012
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<MissingDefaultInSwitchStatementCheck>(
      "automotive-c12-req-16.4");
  CheckFactories.registerCheck<WrongOrderDefaultInSwitchStatementCheck>(
      "automotive-c12-req-16.5");
}

} // namespace clang::tidy::automotive
