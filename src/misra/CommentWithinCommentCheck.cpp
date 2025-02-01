//===--- CommentWithinCommentCheck.cpp - clang-tidy -----------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "CommentWithinCommentCheck.h"
#include "clang/Lex/Preprocessor.h"
#include <iostream>

using namespace clang::ast_matchers;

namespace clang::tidy::misra {

class CommentWithinCommentHandler : public CommentHandler {
public:
  CommentWithinCommentHandler(ClangTidyCheck &Check) : Check(Check) {}
  virtual bool HandleComment(Preprocessor &PP, SourceRange Comment) override;

private:
  ClangTidyCheck &Check;
};

bool CommentWithinCommentHandler::HandleComment(Preprocessor &PP,
                                                SourceRange Comment) {
  StringRef CommentText =
      Lexer::getSourceText(CharSourceRange::getCharRange(Comment),
                           PP.getSourceManager(), PP.getLangOpts());

  if (CommentText.starts_with("//")) {
    SourceLocation StartLoc = Comment.getBegin();
    size_t Pos = 0;

    while ((Pos = CommentText.find("\\\n", Pos)) != StringRef::npos) {
      SourceLocation LineSpliceLoc = StartLoc.getLocWithOffset(Pos);
      Check.diag(LineSpliceLoc, "Avoid line-spliceing within a // comment");
      Pos += 2;
    }
  }
  return false;
}

void CommentWithinCommentCheck::registerPPCallbacks(
    const SourceManager &SM, Preprocessor *PP, Preprocessor *ModuleExpanderPP) {
  static CommentWithinCommentHandler Handler(*this);
  PP->addCommentHandler(&Handler);
}

} // namespace clang::tidy::misra
