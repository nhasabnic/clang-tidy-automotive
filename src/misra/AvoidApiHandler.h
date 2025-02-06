//===--- AvoidApiHandler.h - clang-tidy -------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_AVOIDAPIHANDLER_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_AVOIDAPIHANDLER_H

#include "clang/Basic/SourceLocation.h"
#include "clang/Lex/PPCallbacks.h"
#include "llvm/ADT/StringRef.h"

namespace clang::tidy::misra {

class MatchHeaderInfo {
public:
  const StringRef Name;
  const clang::SourceLocation Location;
  const Token &Tok;
  const bool IsAngled;
};

class MatchMacroInfo {
public:
  const StringRef Name;
  const MatchHeaderInfo *Header;
  const Token &Tok;
};

class AvoidApiHandler {
public:
  virtual ~AvoidApiHandler() = default;

  virtual void checkHeader(const MatchHeaderInfo &Result) {}

  virtual void checkMacro(const MatchMacroInfo &Result) {}

  virtual void checkFunction(const MatchMacroInfo &Result) {}
};

} // namespace clang::tidy::misra

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_AVOIDAPIHANDLER_H
