#!/bin/bash

export CC=clang
export CXX=clang++

# clean previous build
[ -d build ] && rm -r build

# prep build dir
mkdir build

# set up build
cmake -S . -B build

# run build
cmake --build build -j8
