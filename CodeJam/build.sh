#!/usr/bin/env bash
cd $(dirname "$1")
filename=$(basename "$1")
filename=${filename%.*}
gcc -lm -Wall -Ofast "$1" -o "$filename.out"
