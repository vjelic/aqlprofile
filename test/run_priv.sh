#!/bin/sh
RPATH=`realpath $0`

tbin=./ctrl
export LD_LIBRARY_PATH=$PWD

cd `dirname $RPATH`

echo "Run with SDMA SETUP Mode"
unset AQLPROFILE_PMC
unset AQLPROFILE_SQTT
export AQLPROFILE_SDMA=1
eval $tbin

exit 0
