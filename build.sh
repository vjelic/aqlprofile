#!/bin/sh -x
BIN_DIR=`dirname $0`
BLD_DIR=$BIN_DIR/build

export CMAKE_PREFIX_PATH=/opt/rocm/lib:/opt/rocm/include/hsa
rm -rf $BLD_DIR && mkdir $BLD_DIR && cd $BLD_DIR && cmake ..
make -j
if [ "$?" = 0 ] ; then
  make mytest
fi
if [ "$?" = 0 ] ; then
  ./run.sh
fi
