#!/bin/sh -x
SO_EXT="hsaco"

TEST_NAME=$1
DST_DIR=$2
ROCM_DIR=$3
TGT_LIST=$4

if [ -z "$TEST_NAME" ] ; then
  echo "Usage: $0 <test name> <dst dir>"
  echo "  Will look for <test name>.cl and will build <test name>.$SO_EXT dynamic code object library"
  exit 1
fi
OBJ_NAME=$(echo "_$(basename $TEST_NAME)" | sed -e 's/_./\U&\E/g' -e 's/_//g')

if [ -z "$DST_DIR" ] ; then
  DST_DIR=$(dirname TEST_NAME)
fi

if [ -z "$ROCM_DIR" ] ; then
  ROCM_DIR=/opt/rocm
fi

if [ -z "$TGT_LIST" ] ; then
  TGT_LIST=`$ROCM_DIR/bin/rocminfo | grep "amdgcn-amd-amdhsa--" | head -n 1 | sed -n "s/^.*amdgcn-amd-amdhsa--\(\w*\).*$/\1/p"`
fi

if [ -z "$TGT_LIST" ] ; then
  TGT_LIST=`("gfx900" "gfx906" "gfx908" "gfx90a" "gfx1030")`
fi

OCL_VER="2.0"

if [ -e $ROCM_DIR/llvm ] ; then
  LLVM_DIR=$ROCM_DIR/llvm
fi

BIN_DIR=$LLVM_DIR/bin
BITCODE_OPTS="-O2 -x cl -Xclang -finclude-default-header -cl-denorms-are-zero -cl-std=CL2.0 -Wl,--build-id=sha1 -target amdgcn-amd-amdhsa"

for GFXIP in $TGT_LIST ; do
  OBJ_PREF=$GFXIP
  OBJ_FILE="${OBJ_PREF}_${OBJ_NAME}.$SO_EXT"
  $BIN_DIR/clang $BITCODE_OPTS -mcpu=$GFXIP $TEST_NAME.cl -o $DST_DIR/$OBJ_FILE
  echo "'$OBJ_FILE' generated"
done

exit 0
