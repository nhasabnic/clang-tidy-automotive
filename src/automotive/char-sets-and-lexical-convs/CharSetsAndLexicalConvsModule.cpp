//===--- CharSetsAndLexicalConvsModule.cpp - clang-tidy ------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "CharSetsAndLexicalConvsModule.h"
#include "UnterminatedEscapeSequenceCheck.h"

namespace clang::tidy::misra {

void CharSetsAndLexicalConvsModule::addCheckFactories(
    ClangTidyCheckFactories &CheckFactories) {

  /* MISRA C 2023
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<UnterminatedEscapeSequenceCheck>(
      "misra-c2023-req-4.1");
  /* req-4.2: -Wtrigraphs */

  /* MISRA C 2012
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<UnterminatedEscapeSequenceCheck>(
      "misra-c2012-req-4.1");
  /* req-4.2: -Wtrigraphs */
}

} // namespace clang::tidy::misra
