//===--- AvoidStdargHeaderCheck.cpp - clang-tidy --------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "AvoidStdargHeaderCheck.h"
// #include "AvoidApiPPCallbacks.h"

namespace clang::tidy::automotive {

static const std::initializer_list<llvm::StringRef> ForbiddenMacroNames = {
    "va_start", "va_copy", "va_arg", "va_end"};

void AvoidStdargHeaderCheck::registerPPCallbacks(
    const SourceManager &SM, Preprocessor *PP, Preprocessor *ModuleExpanderPP) {

  //  PP->addPPCallbacks(std::make_unique<AvoidApiPPCallbacks>(
  //      *this, *PP, "stdarg.h", ForbiddenMacroNames));
}

} // namespace clang::tidy::automotive
