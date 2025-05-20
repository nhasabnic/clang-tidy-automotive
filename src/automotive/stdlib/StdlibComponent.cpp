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

namespace clang::tidy::automotive {

void StdlibComponent::addCheckFactories(
    ClangTidyCheckFactories &CheckFactories) {

  /* C 2023
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<AvoidStdargHeaderCheck>(
      "automotive-c23-req-17.1");
  // CheckFactories.registerCheck<AvoidStdlibMemoryCheck>(
  //     "automotive-c23-req-21.3");
  CheckFactories.registerCheck<AvoidSetjmpHeaderCheck>(
      "automotive-c23-req-21.4");
  CheckFactories.registerCheck<AvoidSignalHeaderCheck>(
      "automotive-c23-req-21.5");
  CheckFactories.registerCheck<AtoXCheck>("automotive-c23-req-21.7");
  CheckFactories.registerCheck<ExitCheck>("automotive-c23-req-21.8");

  CheckFactories.registerCheck<AvoidstdlibsystemcallCheck>(
      "automotive-c23-req-21.21");
  CheckFactories.registerCheck<AvoidStdlibRandCheck>(
      "automotive-c23-req-21.24");

  /* C 2012
  ------------------------------------------------------------------ */
}

} // namespace clang::tidy::automotive
