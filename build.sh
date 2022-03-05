#!/bin/sh -x
BIN_DIR=`dirname $0`
BLD_DIR=$BIN_DIR/build

rm -rf $BLD_DIR && mkdir $BLD_DIR && cd $BLD_DIR && cmake -DCPACK_GENERATOR="DEB;RPM" ..
make -j
if [ "$?" = 0 ] ; then
  make mytest
fi
if [ "$?" = 0 ] ; then
  ./run.sh
fi
