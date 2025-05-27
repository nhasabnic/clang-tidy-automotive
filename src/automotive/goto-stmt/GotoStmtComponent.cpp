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

  CheckFactories.registerCheck<UnusedLabelCheck>("automotive-unused-label");
  CheckFactories.registerCheck<AvoidGotoCheck>("automotive-avoid-goto");
  CheckFactories.registerCheck<ForwardGotoLabelCheck>(
      "automotive-forward-goto-label");
}

} // namespace clang::tidy::automotive
