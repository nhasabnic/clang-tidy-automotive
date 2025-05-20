//===--- CommentComponent.cpp - clang-tidy --------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "CommentComponent.h"
#include "AvoidCommentWithinCommentCheck.h"
#include "AvoidLinesplicingWithinCommentCheck.h"

namespace clang::tidy::automotive {

void CommentComponent::addCheckFactories(
    ClangTidyCheckFactories &CheckFactories) {

  /* C 2023
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<AvoidCommentWithinCommentCheck>(
      "automotive-c23-req-3.1");
  CheckFactories.registerCheck<AvoidLinesplicingWithinCommentCheck>(
      "automotive-c23-req-3.2");

  /* C 2012
  ------------------------------------------------------------------ */
  CheckFactories.registerCheck<AvoidCommentWithinCommentCheck>(
      "automotive-c12-req-3.1");
  CheckFactories.registerCheck<AvoidLinesplicingWithinCommentCheck>(
      "automotive-c12-req-3.2");
}

} // namespace clang::tidy::automotive
