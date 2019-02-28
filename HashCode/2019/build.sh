#!/usr/bin/env bash
BuildDir="$(cd "$(dirname "${BASH_SOURCE[0]}")" >/dev/null 2>&1 && pwd)/build"
cd "$(dirname "$1")"
FileName=$(basename "$1")
FileName=${FileName%.*}
gcc -lm -Wall -Wextra -Wno-unused-local-typedefs -Wno-unused-function -mavx -maes -g3 -O3 "$1" -o "$BuildDir/$FileName.out"
