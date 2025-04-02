//===--- AvoidCommentWithinCommentCheck.cpp - clang-tidy ------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "AvoidCommentWithinCommentCheck.h"
#include "IgnoreLineSpliceRef.h"

using namespace clang::ast_matchers;

namespace clang::tidy::misra {

static constexpr std::initializer_list<const char *> DefaultProtocols = {
    "http", "https", "ftp", "ftps", "ssh", "file", "sftp", "svn", "git"};

namespace {

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

struct CommentPosition {
  size_t Index;
  size_t Size;
};

typedef State (*StateFunc_t)(char Ch);

}; // Anonymous namespace

static CommentPosition findCommentPosition(StringRef CommentText);

static constexpr State getNextState(State CurrentState, char Ch);

static constexpr State stateDefault(char Ch);
static constexpr State stateNormal(char Ch);
static constexpr State stateExpectCommentStart(char Ch);
static constexpr State stateExpectCommentEnd(char Ch);

void AvoidCommentWithinCommentCheck::registerPPCallbacks(
    const SourceManager &SM, Preprocessor *PP, Preprocessor *ModuleExpanderPP) {
  PP->addCommentHandler(&Handler);
}

AvoidCommentWithinCommentCheck::InternalCommentHandler::InternalCommentHandler(
    AvoidCommentWithinCommentCheck &Check)
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

  CommentPosition Position = findCommentPosition(CommentText);
  CheckComment(Comment.getBegin().getLocWithOffset(Position.Index),
               CommentText.substr(Position.Index, Position.Size));

  return false;
}

void AvoidCommentWithinCommentCheck::InternalCommentHandler::CheckComment(
    SourceLocation CommentLoc, StringRef CommentText) {

  IgnoreLineSpliceRef FilteredText(CommentText);
  State CurrentState = State::Normal;
  size_t IndexWord = 0;

  for (auto It = FilteredText.begin(); It != FilteredText.end(); ++It) {
    CurrentState = getNextState(CurrentState, *It);
    size_t Index = It.position();

    switch (CurrentState) {
    case State::CommentSingleLine:
      Check.diag(CommentLoc.getLocWithOffset(Index - 1),
                 "avoid '//' within comment");
      break;

    case State::CommentStart:
      Check.diag(CommentLoc.getLocWithOffset(Index - 1),
                 "avoid '/*' within comment");
      break;

    case State::CommentEnd:
      Check.diag(CommentLoc.getLocWithOffset(Index),
                 "avoid '*/' within comment");
      break;

    case ExpectURLPattern:
      if (CommentText.substr(Index, 3) == "://") {
        /* TODO: Fix the reverse IndexWord */
        /*
        StringRef Protocol = CommentText.substr(IndexWord, Index - IndexWord);

        if (!Protocols.contains(Protocol)) {
          Check.diag(CommentLoc.getLocWithOffset(Index),
                     "unknown protocol '%0'", DiagnosticIDs::Note)
              << Protocol;
        }*/
        std::advance(It, 2);
      }
      break;

    default:
      break;
    }
  }
}

static CommentPosition findCommentPosition(StringRef CommentText) {
  CommentPosition Position = {0};
  char PrevCh = '\0';

  for (size_t Index = 0; Index < CommentText.size(); ++Index) {
    char Ch = CommentText[Index];

    switch (Ch) {
    case '/':
      if (PrevCh == '/') {
        Position.Index = Index;
        Position.Size = CommentText.size() - Index;
        return Position;
      }
      PrevCh = Ch;
      break;

    case '*':
      if (PrevCh == '/') {
        Position.Index = Index;
        Position.Size = CommentText.size() - Index - 2;
        return Position;
      }
      PrevCh = Ch;
      break;

    default:
      break;
    }
  }
  return Position;
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
