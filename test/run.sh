#!/bin/sh
RPATH=`realpath $0`

tbin=./ctrl
export LD_LIBRARY_PATH=$PWD

cd `dirname $RPATH`

echo "Run simple convolution kernel"
unset AQLPROFILE_PMC
unset AQLPROFILE_SQTT
unset AQLPROFILE_SDMA
eval $tbin

echo "Run with PMC"
export AQLPROFILE_PMC=1
unset AQLPROFILE_SQTT
unset AQLPROFILE_SDMA
eval $tbin

echo "Run with SQTT"
unset AQLPROFILE_PMC
export AQLPROFILE_SQTT=1
unset AQLPROFILE_SDMA
eval $tbin

exit 0
