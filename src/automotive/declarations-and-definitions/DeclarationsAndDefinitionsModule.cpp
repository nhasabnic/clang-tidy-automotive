//===--- DeclarationsAndDefinitionsModule.cpp - clang-tidy ----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "DeclarationsAndDefinitionsModule.h"
#include "AvoidRestrictTypeCheck.h"
#include "UniqueEnumValuesCheck.h"

namespace clang::tidy::automotive {

void DeclarationsAndDefinitionsModule::addCheckFactories(
    ClangTidyCheckFactories &CheckFactories) {

  CheckFactories.registerCheck<UniqueEnumValuesCheck>(
      "automotive-unique-enum-values");
  CheckFactories.registerCheck<AvoidRestrictTypeCheck>(
      "automotive-avoid-restrict-type");
}

} // namespace clang::tidy::automotive
