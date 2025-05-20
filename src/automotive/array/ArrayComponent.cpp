//===--- ArrayComponent.cpp - clang-tidy ----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "ArrayComponent.h"
#include "AvoidFlexibleArrayMemberCheck.h"
#include "AvoidPartialArrayInitCheck.h"
#include "AvoidVariableLengthArrayCheck.h"

namespace clang::tidy::automotive {

void ArrayComponent::addCheckFactories(
    ClangTidyCheckFactories &CheckFactories) {

  /* C 2023
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<AvoidPartialArrayInitCheck>(
      "automotive-c23-req-9.3");

  CheckFactories.registerCheck<AvoidFlexibleArrayMemberCheck>(
      "automotive-c23-req-18.7");
  CheckFactories.registerCheck<AvoidVariableLengthArrayCheck>(
      "automotive-c23-req-18.8");

  /* C 2012
  ------------------------------------------------------------------ */
}

} // namespace clang::tidy::automotive
