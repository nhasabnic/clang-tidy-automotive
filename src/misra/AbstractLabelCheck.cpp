//===--- AbstractLabelCheck.cpp - clang-tidy ------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "AbstractLabelCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang::tidy::misra {

void AbstractLabelCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(labelStmt(hasAncestor(functionDecl().bind("func"))).bind("label"), this);
  Finder->addMatcher(gotoStmt(hasAncestor(functionDecl().bind("func"))).bind("goto"), this);
}

void AbstractLabelCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedFunc = Result.Nodes.getNodeAs<FunctionDecl>("func");
  const auto *MatchedLabel = Result.Nodes.getNodeAs<LabelStmt>("label");
  const auto *MatchedGoto = Result.Nodes.getNodeAs<GotoStmt>("goto");

  if (MatchedLabel) {
    auto LabelName = MatchedLabel->getName();
    auto Info = LabelMap.lookup(LabelName);

    Info.MatchedLabel = MatchedLabel;
    Info.LabelFunction = MatchedFunc;
    Info.LabelIndex = Index;
    LabelMap[LabelName] = Info;
  }

  if (MatchedGoto) {
    const auto TargetLabel = MatchedGoto->getLabel();

    if (TargetLabel) {
      auto LabelName = TargetLabel->getName();
      auto Info = LabelMap.lookup(LabelName);

      Info.MatchedGoto = MatchedGoto;
      Info.GotoFunction = MatchedFunc;
      Info.GotoIndex = Index;
      LabelMap[LabelName] = Info;
    }
  }
  Index++;
}

} // namespace clang::tidy::misra
