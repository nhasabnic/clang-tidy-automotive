//===--- AvoidLinesplicingWithinCommentCheck.cpp - clang-tidy ------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "AvoidLinesplicingWithinCommentCheck.h"

namespace clang::tidy::misra {

bool AvoidLinesplicingWithinCommentHandler::HandleComment(Preprocessor &PP,
                                                          SourceRange Comment) {
  StringRef CommentText =
      Lexer::getSourceText(CharSourceRange::getCharRange(Comment),
                           PP.getSourceManager(), PP.getLangOpts());

  if (CommentText.starts_with("//")) {
    SourceLocation StartLoc = Comment.getBegin();
    size_t Pos = 0;

    while ((Pos = CommentText.find("\\\n", Pos)) != StringRef::npos) {
      SourceLocation LineSpliceLoc = StartLoc.getLocWithOffset(Pos);
      Check.diag(LineSpliceLoc, "avoid line-spliceing within a // comment");
      Pos += 2;
    }
  }
  return false;
}

void AvoidLinesplicingWithinCommentCheck::registerPPCallbacks(
    const SourceManager &SM, Preprocessor *PP, Preprocessor *ModuleExpanderPP) {

  PP->addCommentHandler(&Handler);
}

} // namespace clang::tidy::misra
