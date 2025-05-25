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
      "automotive-Avoid-Partial-Array-Init");

  CheckFactories.registerCheck<AvoidFlexibleArrayMemberCheck>(
      "automotive-Avoid-Flexible-Array-Member");
  CheckFactories.registerCheck<AvoidVariableLengthArrayCheck>(
      "automotive-Avoid-Variable-Length-Array");

  /* C 2012
  ------------------------------------------------------------------ */
}

} // namespace clang::tidy::automotive
