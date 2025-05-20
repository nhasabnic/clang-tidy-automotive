//===--- DeclarationsAndDefinitionsModule.cpp - clang-tidy ----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "DeclarationsAndDefinitionsModule.h"
#include "AvoidRestrictTypeCheck.h"
#include "FunctionDeclarationMismatchCheck.h"
#include "MissingExternalArraySizeCheck.h"
#include "StaticInlineCheck.h"
#include "UncompleteFunctionPrototypeCheck.h"
#include "UniqueEnumValuesCheck.h"

namespace clang::tidy::automotive {

void DeclarationsAndDefinitionsModule::addCheckFactories(
    ClangTidyCheckFactories &CheckFactories) {

  /* C 2023
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<UncompleteFunctionPrototypeCheck>(
      "automotive-c23-req-8.2");
  CheckFactories.registerCheck<FunctionDeclarationMismatchCheck>(
      "automotive-c23-req-8.3");
  CheckFactories.registerCheck<StaticInlineCheck>("automotive-c23-req-8.10");
  CheckFactories.registerCheck<MissingExternalArraySizeCheck>(
      "automotive-c23-adv-8.11");
  CheckFactories.registerCheck<UniqueEnumValuesCheck>(
      "automotive-c23-req-8.12");
  CheckFactories.registerCheck<AvoidRestrictTypeCheck>(
      "automotive-c23-req-8.14");

  /* C 2012
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<StaticInlineCheck>("automotive-c12-req-8.10");
  /* 8.11 m varDecl(allOf(hasType(arrayType(incompleteArrayType())),
   * hasExternalFormalLinkage())) */
  CheckFactories.registerCheck<AvoidRestrictTypeCheck>(
      "automotive-c12-req-8.14");
}

} // namespace clang::tidy::automotive
