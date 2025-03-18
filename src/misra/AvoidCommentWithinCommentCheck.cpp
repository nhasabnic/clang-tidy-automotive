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

static constexpr std::initializer_list<const char *> DefaultProtocols = {
    "http", "https", "ftp", "ftps", "ssh", "file", "sftp", "svn", "git"};

enum State {
  Normal = 0,
  NormalSpace,
  ExpectCommentStart,
  ExpectCommentEnd,
  ExpectURLPattern,
  CommentSingleLine,
  CommentStart,
  CommentEnd
};

typedef State (*StateFunc_t)(char Ch);

static constexpr State getNextState(State CurrentState, char Ch);

static constexpr State stateDefault(char Ch);
static constexpr State stateNormal(char Ch);
static constexpr State stateExpectCommentStart(char Ch);
static constexpr State stateExpectCommentEnd(char Ch);

AvoidCommentWithinCommentCheck::InternalCommentHandler::InternalCommentHandler(
    ClangTidyCheck &Check)
    : Check(Check) {
  for (const char *Protocol : DefaultProtocols) {
    Protocols.insert(Protocol);
  }
}

bool AvoidCommentWithinCommentCheck::InternalCommentHandler::HandleComment(
    Preprocessor &PP, SourceRange Comment) {

  StringRef CommentText =
      Lexer::getSourceText(CharSourceRange::getCharRange(Comment),
                           PP.getSourceManager(), PP.getLangOpts());

  unsigned int Size =
      CommentText[1] == '*' ? CommentText.size() - 1 : CommentText.size();
  unsigned int Index = 2;
  unsigned int IndexSpace = 2;
  unsigned int Offset = 1;

  State CurrentState = State::Normal;
  SourceLocation Location;

  while (Index < Size) {
    char Ch = CommentText[Index];
    char ChNext = CommentText[Index + 1];

    if (Ch != '\\' && ChNext != '\n') {
      CurrentState = getNextState(CurrentState, Ch);

      switch (CurrentState) {
      case State::NormalSpace:
        IndexSpace = Index;
        break;

      case State::CommentSingleLine:
        Location = Comment.getBegin().getLocWithOffset(Index - Offset);
        Check.diag(Location, "avoid '//' within comment");
        break;

      case State::CommentStart:
        Location = Comment.getBegin().getLocWithOffset(Index - Offset);
        Check.diag(Location, "avoid '/*' within comment");
        break;

      case State::CommentEnd:
        Location = Comment.getBegin().getLocWithOffset(Index - Offset);
        Check.diag(Location, "avoid '*/' within comment");
        break;

      case ExpectURLPattern:
        if (CommentText.substr(Index, 3) == "://") {
          unsigned int IndexWord = IndexSpace + 1;
          StringRef Protocol = CommentText.substr(IndexWord, Index - IndexWord);

          if (!Protocols.contains(Protocol)) {
            Location = Comment.getBegin().getLocWithOffset(Index + 1);
            Check.diag(Location, "avoid '//' within comment");
            Location = Comment.getBegin().getLocWithOffset(IndexWord);
            Check.diag(Location, "unknown protocol '%0'", DiagnosticIDs::Note)
                << Protocol;
          }
          Index += 2;
        }
        break;

      default:
        Offset = 1;
        break;
      }
      Index++;

    } else {
      Index += 2;
      Offset += 2;
    }
  }
  return false;
}

void AvoidCommentWithinCommentCheck::registerPPCallbacks(
    const SourceManager &SM, Preprocessor *PP, Preprocessor *ModuleExpanderPP) {
  PP->addCommentHandler(&Handler);
}

static constexpr State getNextState(State CurrentState, char Ch) {
  switch (CurrentState) {
  case State::ExpectCommentStart:
    return stateExpectCommentStart(Ch);

  case State::ExpectCommentEnd:
    return stateExpectCommentEnd(Ch);

  default:
    return stateNormal(Ch);
  }
}

static constexpr State stateDefault(char Ch) {
  switch (Ch) {
  case ' ':
  case '\t':
    return State::NormalSpace;

  default:
    return State::Normal;
  }
}

static constexpr State stateNormal(char Ch) {
  switch (Ch) {
  case '/':
    return State::ExpectCommentStart;

  case '*':
    return State::ExpectCommentEnd;

  case ':':
    return State::ExpectURLPattern;

  default:
    return stateDefault(Ch);
  }
}

static constexpr State stateExpectCommentStart(char Ch) {
  switch (Ch) {
  case '/':
    return State::CommentSingleLine;

  case '*':
    return State::CommentStart;

  default:
    return stateDefault(Ch);
  }
}

static constexpr State stateExpectCommentEnd(char Ch) {
  switch (Ch) {
  case '/':
    return State::CommentEnd;

  default:
    return stateDefault(Ch);
  }
}

} // namespace clang::tidy::misra
