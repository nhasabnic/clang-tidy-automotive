//===--- AvoidLinesplicingWithinCommentCheck.h - clang-tidy -----*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_AUTOMOTIVE_AVOIDLINESPLICINGWITHINCOMMENTCHECK_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_AUTOMOTIVE_AVOIDLINESPLICINGWITHINCOMMENTCHECK_H

#include "../../ClangTidyCheck.h"
#include "clang/Lex/Preprocessor.h"

namespace clang::tidy::automotive {

/// FIXME: Write a short description.
///
/// For the user-facing documentation see:
/// http://clang.llvm.org/extra/clang-tidy/checks/misra/comment-within-comment.html
class AvoidLinesplicingWithinCommentCheck : public ClangTidyCheck {
public:
  AvoidLinesplicingWithinCommentCheck(StringRef Name, ClangTidyContext *Context)
      : ClangTidyCheck(Name, Context),
        Handler(*this, Options.get("FixitEnabled", false)) {}

  void registerPPCallbacks(const SourceManager &SM, Preprocessor *PP,
                           Preprocessor *ModuleExpanderPP) override;

private:
  class InternalCommentHandler : public CommentHandler {
  public:
    InternalCommentHandler(ClangTidyCheck &Check, bool FixitEnabled)
        : Check(Check), FixitEnabled(FixitEnabled) {}
    virtual bool HandleComment(Preprocessor &PP, SourceRange Comment) override;

  private:
    ClangTidyCheck &Check;
    bool FixitEnabled;
  };

  InternalCommentHandler Handler;
};

} // namespace clang::tidy::automotive

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_AUTOMOTIVE_AVOIDLINESPLICINGWITHINCOMMENTCHECK_H
