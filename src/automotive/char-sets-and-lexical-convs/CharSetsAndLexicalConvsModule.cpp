//===--- CharSetsAndLexicalConvsModule.cpp - clang-tidy ------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "CharSetsAndLexicalConvsModule.h"
#include "UnterminatedEscapeSequenceCheck.h"

namespace clang::tidy::automotive {

void CharSetsAndLexicalConvsModule::addCheckFactories(
    ClangTidyCheckFactories &CheckFactories) {

  CheckFactories.registerCheck<UnterminatedEscapeSequenceCheck>(
      "automotive-unterminated-escape-sequence");
}

} // namespace clang::tidy::automotive
