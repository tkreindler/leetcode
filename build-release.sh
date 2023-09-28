#!/usr/bin/env bash

mkdir -p out/release

pushd out/release

cmake -G "Unix Makefiles" ../.. -DCMAKE_BUILD_TYPE=Release

make

popd
