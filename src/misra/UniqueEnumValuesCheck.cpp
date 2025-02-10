//===--- UniqueEnumValuesCheck.cpp - clang-tidy ---------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "UniqueEnumValuesCheck.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang::tidy::misra {

void UniqueEnumValuesCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(enumDecl().bind("enum"), this);
}

void UniqueEnumValuesCheck::check(const MatchFinder::MatchResult &Result) {
  if (const auto *Enum = Result.Nodes.getNodeAs<EnumDecl>("enum")) {
    llvm::DenseMap<int64_t, const EnumConstantDecl *> usedValues;
    int64_t lastValue = -1;

    for (const auto *EnumConst : Enum->enumerators()) {
      int64_t currentValue;

      // Kontrollera om explicit initialisering finns
      if (EnumConst->getInitExpr()) {
        currentValue = EnumConst->getInitVal().getSExtValue();
      } else {
        currentValue = lastValue + 1;
      }

      auto it = usedValues.find(currentValue);
      if (it != usedValues.end()) {
        const EnumConstantDecl *previousEnum = it->second;
        diag(EnumConst->getLocation(), "duplicate enum value '%0' from '%1'")
            << currentValue << previousEnum->getName();
        diag(previousEnum->getLocation(), "declaration of '%0'",
             DiagnosticIDs::Note)
            << previousEnum->getName();
      } else {
        usedValues[currentValue] = EnumConst;
      }

      lastValue = currentValue;
    }
  }
}

} // namespace clang::tidy::misra
