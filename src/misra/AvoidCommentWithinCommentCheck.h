//===--- AvoidCommentWithinCommentCheck.h - clang-tidy ----------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_AVOIDCOMMENTWITHINCOMMENTCHECK_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_AVOIDCOMMENTWITHINCOMMENTCHECK_H

#include "../ClangTidyCheck.h"
#include "clang/Lex/Preprocessor.h"

namespace clang::tidy::misra {

/// FIXME: Write a short description.
///
/// For the user-facing documentation see:
/// http://clang.llvm.org/extra/clang-tidy/checks/misra/comment-within-comment.html
class AvoidCommentWithinCommentCheck : public ClangTidyCheck {
public:
  AvoidCommentWithinCommentCheck(StringRef Name, ClangTidyContext *Context)
      : ClangTidyCheck(Name, Context), Handler(*this) {}

  void registerPPCallbacks(const SourceManager &SM, Preprocessor *PP,
                           Preprocessor *ModuleExpanderPP) override;

private:
  class InternalCommentHandler : public CommentHandler {
  public:
    InternalCommentHandler(ClangTidyCheck &Check) : Check(Check) {}
    virtual bool HandleComment(Preprocessor &PP, SourceRange Comment) override;

  private:
    ClangTidyCheck &Check;
  };

  InternalCommentHandler Handler;
};

} // namespace clang::tidy::misra

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_AVOIDCOMMENTWITHINCOMMENTCHECK_H
