#!/usr/bin/bash

# Download and extract LLVM
wget https://github.com/llvm/llvm-project/archive/refs/tags/llvmorg-20.1.7.tar.gz
tar xzvf llvmorg-20.1.7.tar.gz

# Create symbolic links from the clang-tidy-automotive source tree into LLVM.
ln -f -s ../../../src/automotive/ llvm-project-llvmorg-20.1.7/clang-tools-extra/clang-tidy/
ln -f -s ../../../../../test/checkers/automotive llvm-project-llvmorg-20.1.7/clang-tools-extra/test/clang-tidy/checkers/automotive

# Create symlinks in the src directory.
directories=(
    "cert"
    "misc"
)

src_files=(
    "ClangTidy.h"
    "ClangTidyCheck.h"
    "ClangTidyDiagnosticConsumer.h"
    "ClangTidyModule.h"
    "ClangTidyModuleRegistry.h"
    "ClangTidyOptions.h"
    "ClangTidyProfiling.h"
    "ExpandModularHeadersPPCallbacks.h"
    "FileExtensionsSet.h"
    "GlobList.h"
    "NoLintDirectiveHandler.h"
)

for directory in "${directories[@]}"; do
    ln -f -s "../llvm-project-llvmorg-20.1.7/clang-tools-extra/clang-tidy/${directory}" "src/${directory}"
done

for file in "${src_files[@]}"; do
    ln -f -s "../llvm-project-llvmorg-20.1.7/clang-tools-extra/clang-tidy/${file}" "src/${file}"
done

# Copy the prepatched files to activate Automotive support
cp prepatch/ClangTidyForceLinker.h llvm-project-llvmorg-20.1.7/clang-tools-extra/clang-tidy/ClangTidyForceLinker.h
cp prepatch/CMakeLists.txt llvm-project-llvmorg-20.1.7/clang-tools-extra/clang-tidy/CMakeLists.txt
