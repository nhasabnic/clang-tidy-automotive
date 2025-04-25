//===--- TypesModule.cpp - clang-tidy ------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "TypesModule.h"
#include "AvoidBitfieldsInUnionsCheck.h"
#include "AvoidSignedSingleBitFieldsCheck.h"
#include "WrongBitfieldTypeCheck.h"

namespace clang::tidy::misra {

void TypesModule::addCheckFactories(ClangTidyCheckFactories &CheckFactories) {

  /* MISRA C 2023
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<WrongBitfieldTypeCheck>("misra-c2023-req-6.1");
  CheckFactories.registerCheck<AvoidSignedSingleBitFieldsCheck>(
      "misra-c2023-req-6.2");
  CheckFactories.registerCheck<AvoidBitfieldsInUnionsCheck>(
      "misra-c2023-req-6.3");

  /* MISRA C 2012
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<WrongBitfieldTypeCheck>("misra-c2012-req-6.1");
  CheckFactories.registerCheck<AvoidSignedSingleBitFieldsCheck>(
      "misra-c2012-req-6.2");
}

} // namespace clang::tidy::misra
