#!/bin/sh

tbin=./test/ctrl
export LD_LIBRARY_PATH=$PWD

echo
echo "Run simple convolution kernel"
unset ROCR_ENABLE_PMC
unset ROCR_ENABLE_SQTT
eval $tbin

echo
echo "Run with PMC"
export ROCR_ENABLE_PMC=1
unset ROCR_ENABLE_SQTT
eval $tbin

echo
echo "Run with SQTT"
unset ROCR_ENABLE_PMC
export ROCR_ENABLE_SQTT=1
eval $tbin

exit 0
