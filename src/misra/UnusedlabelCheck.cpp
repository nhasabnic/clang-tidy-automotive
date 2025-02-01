//===--- UnusedlabelCheck.cpp - clang-tidy --------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "UnusedlabelCheck.h"

using namespace clang::ast_matchers;

namespace clang::tidy::misra {

UnusedlabelCheck::~UnusedlabelCheck() {
  for (const auto &Entry : getLabelMap()) {
    const StringRef &LabelName = Entry.first;
    const LabelInfo &Info = Entry.second;

    if (!Info.MatchedGoto && Info.MatchedLabel) {
      diag(Info.MatchedLabel->getBeginLoc(), "unused label '%0'") << LabelName;
    }
/*else if (Info.LabelFunction != Info.GotoFunction) {
      diag(Info.MatchedLabel->getBeginLoc(), "label and goto in different functions");
    } else {
    }*/
  }
}

} // namespace clang::tidy::misra
