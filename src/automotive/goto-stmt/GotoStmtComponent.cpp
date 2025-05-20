//===--- GotoStmtComponent.cpp - clang-tidy -------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "GotoStmtComponent.h"
#include "AvoidGotoCheck.h"
#include "ForwardGotoLabelCheck.h"
#include "UnusedLabelCheck.h"

namespace clang::tidy::automotive {

void GotoStmtComponent::addCheckFactories(
    ClangTidyCheckFactories &CheckFactories) {

  /* C 2023
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<UnusedLabelCheck>("automotive-c23-adv-2.6");
  CheckFactories.registerCheck<AvoidGotoCheck>("automotive-c23-adv-15.1");
  CheckFactories.registerCheck<ForwardGotoLabelCheck>("automotive-c23-req-15.2");

  /* C 2012
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<UnusedLabelCheck>("automotive-c12-adv-2.6");
  CheckFactories.registerCheck<AvoidGotoCheck>("automotive-c12-adv-15.1");
  CheckFactories.registerCheck<ForwardGotoLabelCheck>("automotive-c12-req-15.2");
}

} // namespace clang::tidy::automotive
