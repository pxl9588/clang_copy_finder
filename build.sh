#!/bin/bash

set -e
set -u
set -x

REPO=$(realpath $(dirname $0))
DEST=${1:-$REPO/build}

mkdir -p $DEST/install

export CXXFLAGS="-I/usr/include"
export CFLAGS="-I/usr/include"
export LDFLAGS="-L/usr/lib64"

cmake                                                           \
    -G Ninja                                                    \
    -DCMAKE_BUILD_TYPE=Debug                                    \
    -DClang_DIR=/usr/lib/llvm-14.0/lib/cmake/clang/             \
    -DCMAKE_INSTALL_PREFIX=$DEST/install                        \
    -DCMAKE_MODULE_PATH=/usr/lib/llvm-14/lib/cmake/clang        \
    -S $REPO -B $DEST

cd $DEST
ninja -j16
ninja install