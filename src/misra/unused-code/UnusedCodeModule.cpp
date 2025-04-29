//===--- UnusedCodeModule.cpp - clang-tidy --------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "UnusedCodeModule.h"
#include "UnusedLabelCheck.h"
#include "UnusedMacroCheck.h"
#include "UnusedObjectDefinitionCheck.h"
#include "UnusedTagCheck.h"
#include "UnusedTypeCheck.h"

namespace clang::tidy::misra {

void UnusedCodeModule::addCheckFactories(
    ClangTidyCheckFactories &CheckFactories) {

  /* MISRA C 2023
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<UnusedTypeCheck>("misra-c2023-adv-2.3");
  CheckFactories.registerCheck<UnusedMacroCheck>("misra-c2023-adv-2.5");
  CheckFactories.registerCheck<UnusedLabelCheck>("misra-c2023-adv-2.6");
  // CheckFactories.registerCheck<misc::UnusedParametersCheck>(
  //     "misra-c2023-adv-2.7");
  CheckFactories.registerCheck<UnusedObjectDefinitionCheck>(
      "misra-c2023-adv-2.8");

  /* MISRA C 2012
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<UnusedTypeCheck>("misra-c2012-adv-2.3");
  CheckFactories.registerCheck<UnusedMacroCheck>("misra-c2012-adv-2.5");
  CheckFactories.registerCheck<UnusedLabelCheck>("misra-c2012-adv-2.6");
  // CheckFactories.registerCheck<misc::UnusedParametersCheck>(
  //     "misra-c2012-adv-2.7");

  /* Experimental
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<UnusedTagCheck>("misra-x-adv-2.4");
}

} // namespace clang::tidy::misra
