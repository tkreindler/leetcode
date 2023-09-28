#!/usr/bin/env bash

# build dependencies silently
make debug > /dev/null
make release > /dev/null

set -x

time out/debug/main inputs/dictionaryFile2.txt inputs/inputFile2.txt
time out/release/main inputs/dictionaryFile2.txt inputs/inputFile2.txt

