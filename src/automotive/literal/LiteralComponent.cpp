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

namespace clang::tidy::misra {

void LiteralComponent::addCheckFactories(
    ClangTidyCheckFactories &CheckFactories) {

  /* MISRA C 2023
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<AvoidOctalNumberCheck>("misra-c2023-req-7.1");
  CheckFactories.registerCheck<AvoidLowercaseLiteralSuffixCheck>(
      "misra-c2023-req-7.3");

  /* MISRA C 2012
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<AvoidOctalNumberCheck>("misra-c2012-req-7.1");
}

} // namespace clang::tidy::misra
