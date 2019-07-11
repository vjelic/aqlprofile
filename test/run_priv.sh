#!/bin/sh
RPATH=`realpath $0`

tbin=./ctrl
export LD_LIBRARY_PATH=$PWD

cd `dirname $RPATH`

echo "Run with SDMA SETUP Mode"
unset AQLPROFILE_PMC
unset AQLPROFILE_PMC_PRIV
unset AQLPROFILE_SQTT
export AQLPROFILE_SDMA=1
eval $tbin

echo "Run with PMC Privilge"
unset AQLPROFILE_PMC
export AQLPROFILE_PMC_PRIV=1
unset AQLPROFILE_SQTT
unset AQLPROFILE_SDMA
eval $tbin

exit 0
