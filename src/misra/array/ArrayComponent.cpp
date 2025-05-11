//===--- ArrayComponent.cpp - clang-tidy ----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "ArrayComponent.h"
#include "AvoidFlexibleArrayMemberCheck.h"
#include "AvoidVariableLengthArrayCheck.h"

namespace clang::tidy::misra {

void ArrayComponent::addCheckFactories(
    ClangTidyCheckFactories &CheckFactories) {

  /* MISRA C 2023
  ------------------------------------------------------------------ */
    CheckFactories.registerCheck<AvoidFlexibleArrayMemberCheck>(
        "misra-c2023-req-18.7");
    CheckFactories.registerCheck<AvoidVariableLengthArrayCheck>(
        "misra-c2023-req-18.8");

  /* MISRA C 2012
  ------------------------------------------------------------------ */
}

} // namespace clang::tidy::misra
