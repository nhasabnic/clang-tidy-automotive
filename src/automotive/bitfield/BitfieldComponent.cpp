//===--- BitfieldComponent.cpp - clang-tidy ----------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "BitfieldComponent.h"
#include "AvoidBitfieldInUnionCheck.h"
#include "AvoidSignedSingleBitFieldCheck.h"
#include "WrongBitfieldTypeCheck.h"

namespace clang::tidy::automotive {

void BitfieldComponent::addCheckFactories(
    ClangTidyCheckFactories &CheckFactories) {

  /* C 2023
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<WrongBitfieldTypeCheck>(
      "automotive-c23-req-6.1");
  CheckFactories.registerCheck<AvoidSignedSingleBitFieldCheck>(
      "automotive-c23-req-6.2");
  CheckFactories.registerCheck<AvoidBitfieldInUnionCheck>(
      "automotive-c23-req-6.3");

  /* C 2012
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<WrongBitfieldTypeCheck>(
      "automotive-c12-req-6.1");
  CheckFactories.registerCheck<AvoidSignedSingleBitFieldCheck>(
      "automotive-c12-req-6.2");
}

} // namespace clang::tidy::automotive
