#/bin/bash

#QUARTZ_ROOT=/mnt/Store/Kode/github/quartz/
QUARTZ_ROOT=`readlink -f .`
echo "Using root $QUARTZ_ROOT"
export QUARTZ_ROOT
~/Bin/qtcreator.sh &



