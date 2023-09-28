#!/usr/bin/env bash

mkdir -p out/debug

pushd out/debug

cmake -G "Unix Makefiles" ../.. \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_CXX_FLAGS="-fsanitize=address -fsanitize=leak -g" \
    -DCMAKE_EXE_LINKER_FLAGS="-fsanitize=address -fsanitize=leak" \
    -DCMAKE_MODULE_LINKER_FLAGS="-fsanitize=address -fsanitize=leak"

make

popd
