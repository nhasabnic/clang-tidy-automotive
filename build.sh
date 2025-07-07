#!/usr/bin/bash
cd build
ninja -j 8 clang-tidy clang-format
cd ..
