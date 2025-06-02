//===--- PointerComponent.cpp - clang-tidy --------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "PointerComponent.h"
#include "AvoidAtomicVoidPointerCheck.h"
#include "WrongNullPointerValueCheck.h"

namespace clang::tidy::automotive {

void PointerComponent::addCheckFactories(
    ClangTidyCheckFactories &CheckFactories) {

  CheckFactories.registerCheck<WrongNullPointerValueCheck>(
      "automotive-wrong-null-pointer-value");
}

} // namespace clang::tidy::automotive
