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

  CheckFactories.registerCheck<WrongBitfieldTypeCheck>(
      "automotive-wrong-bitfield-type");
  CheckFactories.registerCheck<AvoidSignedSingleBitFieldCheck>(
      "automotive-avoid-signed-single-bitfield");
  CheckFactories.registerCheck<AvoidBitfieldInUnionCheck>(
      "automotive-avoid-bitfield-in-union");
}

} // namespace clang::tidy::automotive
