#!/bin/sh
RPATH=`realpath $0`
cd `dirname $RPATH`

tbin=./ctrl
export LD_LIBRARY_PATH=$PWD:/opt/rocm/hsa-amd-aqlprofile/lib

echo "Run simple convolution kernel"
unset AQLPROFILE_PMC
unset AQLPROFILE_SQTT
eval $tbin

echo "Run with PMC"
export AQLPROFILE_PMC=1
unset AQLPROFILE_SQTT
eval $tbin

echo "Run with SQTT"
unset AQLPROFILE_PMC
export AQLPROFILE_SQTT=1
eval $tbin

exit 0
