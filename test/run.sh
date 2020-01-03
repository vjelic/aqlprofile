#!/bin/sh
RPATH=`realpath $0`

tbin=./ctrl
export LD_LIBRARY_PATH=$PWD

cd `dirname $RPATH`

echo "Run simple convolution kernel"
unset AQLPROFILE_PMC
unset AQLPROFILE_PMC_PRIV
unset AQLPROFILE_SQTT
unset AQLPROFILE_SDMA
unset AQLPROFILE_SCAN
eval $tbin

echo "Run with PMC"
export AQLPROFILE_PMC=1
unset AQLPROFILE_PMC_PRIV
unset AQLPROFILE_SQTT
unset AQLPROFILE_SDMA
unset AQLPROFILE_SCAN
eval $tbin

echo "Run with SQTT"
unset AQLPROFILE_PMC
unset AQLPROFILE_PMC_PRIV
export AQLPROFILE_SQTT=1
unset AQLPROFILE_SDMA
unset AQLPROFILE_SCAN
eval $tbin

echo "Run with PCSMP"
unset AQLPROFILE_PMC
unset AQLPROFILE_PMC_PRIV
unset AQLPROFILE_SQTT
export AQLPROFILE_PCSMP=1
unset AQLPROFILE_SDMA
unset AQLPROFILE_SCAN
eval $tbin

#valgrind --leak-check=full $tbin
#valgrind --tool=massif $tbin
#ms_print massif.out.<N>

exit 0
