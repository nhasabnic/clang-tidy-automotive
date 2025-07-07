#!/usr/bin/bash
mkdir build
cd build
cmake -G Ninja \
      -DCMAKE_EXPORT_COMPILE_COMMANDS=ON . \
      -DCMAKE_BUILD_TYPE=Release \
      -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra" \
      -DLLVM_TARGETS_TO_BUILD="ARM;X86;AArch64" \
      ../llvm-project-llvmorg-20.1.7/llvm
cd ..
