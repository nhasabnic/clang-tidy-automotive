//===--- CommentsModule.cpp - clang-tidy ----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "CommentsModule.h"
#include "AvoidCommentWithinCommentCheck.h"
#include "AvoidLinesplicingWithinCommentCheck.h"

namespace clang::tidy::misra {

void CommentsModule::addCheckFactories(ClangTidyCheckFactories &CheckFactories) {

  /* MISRA C 2023
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<AvoidCommentWithinCommentCheck>(
      "misra-c2023-req-3.1");
  CheckFactories.registerCheck<AvoidLinesplicingWithinCommentCheck>(
      "misra-c2023-req-3.2");

  /* MISRA C 2012
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<AvoidCommentWithinCommentCheck>(
      "misra-c2012-req-3.1");
  CheckFactories.registerCheck<AvoidLinesplicingWithinCommentCheck>(
      "misra-c2012-req-3.2");

}

} // namespace clang::tidy::misra
