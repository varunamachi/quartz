#!/bin/bash

SCRIPT_DIR=$(dirname $0) 
# ABS_SCRIPT_DIR=$(readlink -f $SCRIPT_DIR)
QUARTZ_ROOT=$(readlink -f $SCRIPT_DIR/../..)
echo "Using Quartz root: $QUARTZ_ROOT"

export QUARTZ_ROOT=$QUARTZ_ROOT
QT_CMAKE_PATH=$QT_ROOT/lib/cmake/

RELEASE_BUILD_DIR=$QUARTZ_ROOT/build/__quartz_release
if [ -d "$RELEASE_BUILD_DIR" ] ; then
    echo "Removing previoud build directory $RELEASE_BUILD_DIR"
    rm -R "$RELEASE_BUILD_DIR" || exit -1
fi
mkdir -p "$RELEASE_BUILD_DIR"
cd "$RELEASE_BUILD_DIR" || exit -1

NUM_PROCS=$(grep -c ^processor /proc/cpuinfo)
cmake -G "Unix Makefiles" -DCMAKE_PREFIX_PATH="$QT_CMAKE_PATH" \
    -DCMAKE_BUILD_TYPE=Release ../.. || exit -1

make -j"${NUM_PROCS}" install

