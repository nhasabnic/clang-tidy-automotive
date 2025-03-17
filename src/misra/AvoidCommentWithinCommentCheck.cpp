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

enum State {
  Normal = 0,
  ExpectCommentStart,
  ExpectCommentEnd,
  CommentSingleLine,
  CommentStart,
  CommentEnd
};

typedef State (*StateFunc_t)(char Ch);

static State StateNormal(char Ch);
static State StateExpectCommentStart(char Ch);
static State StateExpectCommentEnd(char Ch);

static constexpr StateFunc_t StateTable[] = {
  &StateNormal,
  &StateExpectCommentStart,
  &StateExpectCommentEnd,
  &StateNormal,
  &StateNormal
};

bool AvoidCommentWithinCommentCheck::InternalCommentHandler::HandleComment(
    Preprocessor &PP, SourceRange Comment) {

  StringRef CommentText =
      Lexer::getSourceText(CharSourceRange::getCharRange(Comment),
                           PP.getSourceManager(), PP.getLangOpts());
  
  unsigned int Size = CommentText[1] == '*' ? CommentText.size() - 2 : CommentText.size();
  unsigned int Index = 2;
  State CurrentState = State::Normal;
  SourceLocation Location;

  while (Index < Size) {
    char Ch = CommentText[Index];
    CurrentState = StateTable[CurrentState](Ch);

    switch (CurrentState) {
    case State::CommentSingleLine:
      Location = Comment.getBegin().getLocWithOffset(Index-1);
      Check.diag(Location, "avoid '//' within comment");
      break;

    case State::CommentStart:
      Location = Comment.getBegin().getLocWithOffset(Index-1);
      Check.diag(Location, "avoid '/*' within comment");
      break;

    case State::CommentEnd:
      Location = Comment.getBegin().getLocWithOffset(Index-1);
      Check.diag(Location, "avoid '*/' within comment");
      
    default:
      break;
    }
    Index++;
  }
  return false;
}

void AvoidCommentWithinCommentCheck::registerPPCallbacks(
    const SourceManager &SM, Preprocessor *PP, Preprocessor *ModuleExpanderPP) {
  PP->addCommentHandler(&Handler);
}

static State StateNormal(char Ch) {
  switch(Ch) {
  case '/': 
    return State::ExpectCommentStart;

  case '*':
    return State::ExpectCommentEnd;

  default: 
    return State::Normal;
  }
}

static State StateExpectCommentStart(char Ch) {
  switch(Ch) {
  case '/':
    return State::CommentSingleLine;

  case '*':
    return State::CommentStart;

  default:
    return State::Normal;
  }
}

static State StateExpectCommentEnd(char Ch) {
  switch(Ch) {
  case '/':
    return State::CommentEnd;

  default:
    return State::Normal;
  }
}

} // namespace clang::tidy::misra
