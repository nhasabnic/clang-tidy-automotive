//===--- LiteralComponent.cpp - clang-tidy --------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "LiteralComponent.h"
#include "AvoidLowercaseLiteralSuffixCheck.h"
#include "AvoidOctalNumberCheck.h"

namespace clang::tidy::automotive {

void LiteralComponent::addCheckFactories(
    ClangTidyCheckFactories &CheckFactories) {

  /* C 2023
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<AvoidOctalNumberCheck>("automotive-c23-req-7.1");
  CheckFactories.registerCheck<AvoidLowercaseLiteralSuffixCheck>(
      "automotive-c23-req-7.3");

  /* C 2012
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<AvoidOctalNumberCheck>("automotive-c12-req-7.1");
}

} // namespace clang::tidy::automotive
