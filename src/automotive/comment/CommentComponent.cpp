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

  CheckFactories.registerCheck<AvoidCommentWithinCommentCheck>(
      "automotive-avoid-comment-within-comment");
  CheckFactories.registerCheck<AvoidLinesplicingWithinCommentCheck>(
      "automotive-avoid-line-splicing-within-comment");
}

} // namespace clang::tidy::automotive
