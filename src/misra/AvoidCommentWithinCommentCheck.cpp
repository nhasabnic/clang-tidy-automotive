//===--- AvoidCommentWithinCommentCheck.cpp - clang-tidy ------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "AvoidCommentWithinCommentCheck.h"

using namespace clang::ast_matchers;

namespace clang::tidy::misra {

bool AvoidCommentWithinCommentCheck::InternalCommentHandler::HandleComment(
    Preprocessor &PP, SourceRange Comment) {
  StringRef CommentText =
      Lexer::getSourceText(CharSourceRange::getCharRange(Comment),
                           PP.getSourceManager(), PP.getLangOpts());

  return false;
}

void AvoidCommentWithinCommentCheck::registerPPCallbacks(
    const SourceManager &SM, Preprocessor *PP, Preprocessor *ModuleExpanderPP) {
  PP->addCommentHandler(&Handler);
}

} // namespace clang::tidy::misra
