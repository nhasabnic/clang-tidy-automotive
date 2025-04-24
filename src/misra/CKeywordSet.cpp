//===--- CKeywordSet.cpp - clang-tidy -------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "CKeywordSet.h"
#include "clang/Basic/LangOptions.h"
#include "clang/Basic/LangStandard.h"

namespace clang::tidy::misra {

using namespace clang;

static constexpr size_t
sizeofKeywordSet(std::initializer_list<llvm::ArrayRef<llvm::StringRef>> Lists);

static llvm::DenseSet<llvm::StringRef>
makeKeywordSet(std::initializer_list<llvm::ArrayRef<llvm::StringRef>> Lists,
               llvm::ArrayRef<llvm::StringRef> RemoveList = {});

static constexpr llvm::StringRef C89Keywords[] = {
    "auto",     "break",  "case",    "char",   "const",    "continue",
    "default",  "do",     "double",  "else",   "enum",     "extern",
    "float",    "for",    "goto",    "if",     "int",      "long",
    "register", "return", "short",   "signed", "sizeof",   "static",
    "struct",   "switch", "typedef", "union",  "unsigned", "void",
    "volatile", "while"};

static constexpr llvm::StringRef C99Keywords[] = {
    "_Bool", "_Complex", "_Imaginary", "inline", "restrict"};

static constexpr llvm::StringRef C11Keywords[] = {
    "_Alignas",  "_Alignof",       "_Atomic",      "_Generic",
    "_Noreturn", "_Static_assert", "_Thread_local"};

static constexpr llvm::StringRef C23Keywords[] = {
    "alignas",     "alignof",    "bool",          "constexpr",
    "false",       "nullptr",    "static_assert", "thread_local",
    "true",        "typeof",     "typeof_unqual", "_BitInt",
    "_Decimal128", "_Decimal32", "_Decimal64"};

static constexpr llvm::StringRef C23DeprecatedKeywords[] = {
    "_Alignas",  "_Alignof",       "_Bool",
    "_Noreturn", "_Static_assert", "_Thread_local"};

static const llvm::DenseSet<llvm::StringRef> EmptyKeywordSet = {};

static const llvm::DenseSet<llvm::StringRef> C89KeywordSet =
    makeKeywordSet({C89Keywords});

static const llvm::DenseSet<llvm::StringRef> C99KeywordSet =
    makeKeywordSet({C89Keywords, C99Keywords});

static const llvm::DenseSet<llvm::StringRef> C11KeywordSet =
    makeKeywordSet({C89Keywords, C99Keywords, C11Keywords});

static const llvm::DenseSet<llvm::StringRef> C23KeywordSet =
    makeKeywordSet({C89Keywords, C99Keywords, C11Keywords, C23Keywords},
                   C23DeprecatedKeywords);

static const llvm::DenseSet<llvm::StringRef> C23DeprecatedKeywordSet =
    makeKeywordSet({C23DeprecatedKeywords});

CKeywordSet::CKeywordSet(const clang::LangOptions &LangOpts) {
  if (LangOpts.C23) {
    ActiveKeywords = &C23KeywordSet;
    DeprecatedKeywords = &C23DeprecatedKeywordSet;

  } else if (LangOpts.C11) {
    ActiveKeywords = &C11KeywordSet;
    DeprecatedKeywords = &EmptyKeywordSet;

  } else if (LangOpts.C99) {
    ActiveKeywords = &C99KeywordSet;
    DeprecatedKeywords = &EmptyKeywordSet;

  }  else {
    ActiveKeywords = &C23KeywordSet;
    DeprecatedKeywords = &EmptyKeywordSet;

  }
}

bool CKeywordSet::isKeyword(StringRef Str) const {
  return ActiveKeywords->contains(Str);
}

bool CKeywordSet::isDeprecated(StringRef Str) const {
  return DeprecatedKeywords->contains(Str);
}

static constexpr size_t
sizeofKeywordSet(std::initializer_list<llvm::ArrayRef<llvm::StringRef>> Lists) {
  size_t Size = 0;
  for (const auto &List : Lists) {
    Size += List.size();
  }
  return Size;
}

static llvm::DenseSet<llvm::StringRef>
makeKeywordSet(std::initializer_list<llvm::ArrayRef<llvm::StringRef>> Lists,
               ArrayRef<llvm::StringRef> RemoveList) {

  llvm::DenseSet<llvm::StringRef> Result(sizeofKeywordSet(Lists));

  for (const auto &List : Lists) {
    Result.insert(List.begin(), List.end());
  }

  for (const auto &Remove : RemoveList) {
    Result.erase(Remove);
  }

  return Result;
}

} // namespace clang::tidy::misra
