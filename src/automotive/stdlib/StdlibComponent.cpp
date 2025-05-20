//===--- StdlibComponent.cpp - clang-tidy ---------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "StdlibComponent.h"
#include "AtoXCheck.h"
#include "AvoidSetjmpHeaderCheck.h"
#include "AvoidSignalHeaderCheck.h"
#include "AvoidStdargHeaderCheck.h"
#include "AvoidStdlibMemoryCheck.h"
#include "AvoidStdlibRandCheck.h"
#include "AvoidstdlibsystemcallCheck.h"
#include "ExitCheck.h"

namespace clang::tidy::misra {

void StdlibComponent::addCheckFactories(
    ClangTidyCheckFactories &CheckFactories) {

  /* MISRA C 2023
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<AvoidStdargHeaderCheck>("misra-c2023-req-17.1");
  // CheckFactories.registerCheck<AvoidStdlibMemoryCheck>(
  //     "misra-c2023-req-21.3");
  CheckFactories.registerCheck<AvoidSetjmpHeaderCheck>("misra-c2023-req-21.4");
  CheckFactories.registerCheck<AvoidSignalHeaderCheck>("misra-c2023-req-21.5");
  CheckFactories.registerCheck<AtoXCheck>("misra-c2023-req-21.7");
  CheckFactories.registerCheck<ExitCheck>("misra-c2023-req-21.8");

  CheckFactories.registerCheck<AvoidstdlibsystemcallCheck>(
      "misra-c2023-req-21.21");
  CheckFactories.registerCheck<AvoidStdlibRandCheck>("misra-c2023-req-21.24");

  /* MISRA C 2012
  ------------------------------------------------------------------ */
}

} // namespace clang::tidy::misra
