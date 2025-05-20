//===--- CommentMatch.h - clang-tidy ---------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_AUTOMOTIVE_COMMENTMATCH_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_AUTOMOTIVE_COMMENTMATCH_H

#include "../utils/IgnoreLineSpliceRef.h"
#include "llvm/ADT/StringRef.h"

namespace clang::tidy::automotive {

enum class CommentKind { None, SingleLine, MultiLine };

struct CommentMatch {
  size_t Index = 0;
  size_t Size = 0;
  CommentKind Kind = CommentKind::None;

  bool isValid() const { return Kind != CommentKind::None; }
  bool isMultiLine() const { return Kind == CommentKind::MultiLine; }
  bool isSingleLine() const { return Kind == CommentKind::SingleLine; }
};

inline CommentMatch matchComment(StringRef CommentText) {
  if (CommentText.size() >= 2) {
    IgnoreLineSpliceRef FilteredText(CommentText);

    auto It = FilteredText.begin();
    char PrevCh = *It;
    char Ch = *(++It);

    if (PrevCh == '/' && Ch == '*') {
      auto ReverseIt = FilteredText.rbegin();
      char RPrevCh = *ReverseIt;
      char RCh = *(--ReverseIt);

      if (RPrevCh == '/' && RCh == '*') {
        size_t StartIndex = It.position();
        size_t EndIndex = ReverseIt.position();
        size_t Size = EndIndex - StartIndex;

        return {StartIndex, Size, CommentKind::MultiLine};
      }
    }

    else if (PrevCh == '/' && Ch == '/') {
      size_t StartIndex = It.position();
      size_t Size = CommentText.size() - StartIndex;
      return {StartIndex, Size, CommentKind::SingleLine};
    }
  }
  return {};
}

} // namespace clang::tidy::automotive

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_AUTOMOTIVE_COMMENTMATCH_H
