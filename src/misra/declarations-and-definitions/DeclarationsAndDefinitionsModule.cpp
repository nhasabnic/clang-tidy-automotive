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

namespace clang::tidy::misra {

void DeclarationsAndDefinitionsModule::addCheckFactories(ClangTidyCheckFactories &CheckFactories) {

  /* MISRA C 2023
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<UncompleteFunctionPrototypeCheck>(
      "misra-c2023-req-8.2");
  CheckFactories.registerCheck<FunctionDeclarationMismatchCheck>(
      "misra-c2023-req-8.3");
  CheckFactories.registerCheck<StaticInlineCheck>("misra-c2023-req-8.10");
  CheckFactories.registerCheck<MissingExternalArraySizeCheck>(
      "misra-c2023-adv-8.11");
  CheckFactories.registerCheck<UniqueEnumValuesCheck>("misra-c2023-req-8.12");
  CheckFactories.registerCheck<AvoidRestrictTypeCheck>(
      "misra-c2023-req-8.14");

  /* MISRA C 2012
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<StaticInlineCheck>("misra-c2012-req-8.10");
  /* 8.11 m varDecl(allOf(hasType(arrayType(incompleteArrayType())),
   * hasExternalFormalLinkage())) */
  CheckFactories.registerCheck<AvoidRestrictTypeCheck>(
      "misra-c2012-req-8.14");

}

} // namespace clang::tidy::misra
