//===--- AvoidLinesplicingWithinCommentCheck.cpp - clang-tidy ------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "AvoidLinesplicingWithinCommentCheck.h"
#include "CommentMatch.h"

namespace clang::tidy::misra {

bool AvoidLinesplicingWithinCommentCheck::InternalCommentHandler::HandleComment(
    Preprocessor &PP, SourceRange Comment) {
  StringRef CommentText =
      Lexer::getSourceText(CharSourceRange::getCharRange(Comment),
                           PP.getSourceManager(), PP.getLangOpts());

  CommentMatch Match = matchComment(CommentText);

  if (Match.isSingleLine()) {
    SourceLocation StartLoc = Comment.getBegin();

    for (size_t Pos = 0;
         (Pos = CommentText.find("\\\n", Pos)) != StringRef::npos; Pos += 2) {
      SourceLocation LineSpliceLoc = StartLoc.getLocWithOffset(Pos);

      Check.diag(LineSpliceLoc, "avoid line-spliceing within a // comment");
    }
  }
  return false;
}

void AvoidLinesplicingWithinCommentCheck::registerPPCallbacks(
    const SourceManager &SM, Preprocessor *PP, Preprocessor *ModuleExpanderPP) {

  PP->addCommentHandler(&Handler);
}

} // namespace clang::tidy::misra
