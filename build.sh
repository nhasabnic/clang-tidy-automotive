#!/usr/bin/bash
cd build
ninja -j 2 clang-tidy clang-format
cd ..
