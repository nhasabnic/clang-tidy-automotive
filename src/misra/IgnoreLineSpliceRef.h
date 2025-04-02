//===--- IgnoreLineSpliceRef.h - clang-tidy ---------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_IGNORELINESPLICEREF_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_IGNORELINESPLICEREF_H

#include "llvm/ADT/StringRef.h"
#include "llvm/Support/raw_ostream.h"

class IgnoreLineSpliceRefIterator {
public:
  using iterator_category = std::forward_iterator_tag;
  using value_type = char;
  using difference_type = std::ptrdiff_t;
  using pointer = char *;
  using reference = char &;

  IgnoreLineSpliceRefIterator(llvm::StringRef Text, size_t Index)
      : Text(Text), Index(Index) {
    skipLineSplice();
  }

  char operator*() const { return Text[Index]; }

  IgnoreLineSpliceRefIterator &operator++() {
    ++Index;
    skipLineSplice();
    return *this;
  }

  IgnoreLineSpliceRefIterator operator++(int) {
    IgnoreLineSpliceRefIterator temp = *this;
    ++(*this);
    return temp;
  }

  bool operator!=(const IgnoreLineSpliceRefIterator &Other) const {
    return Index != Other.Index;
  }

  size_t position() const { return Index; }

private:
  void skipLineSplice() {
    while (Index + 1 < Text.size() && Text[Index] == '\\' &&
           Text[Index + 1] == '\n') {
      Index += 2;
    }
  }

  llvm::StringRef Text;
  size_t Index;
};

class IgnoreLineSpliceRef {
public:
  IgnoreLineSpliceRef(llvm::StringRef Text) : Text(Text) {}

  IgnoreLineSpliceRefIterator begin() {
    return IgnoreLineSpliceRefIterator(Text, 0);
  }

  IgnoreLineSpliceRefIterator end() {
    return IgnoreLineSpliceRefIterator(Text, Text.size());
  }

private:
  llvm::StringRef Text;
};

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_IGNORELINESPLICEREF_H
