#!/bin/sh -x
BIN_DIR=`dirname $0`

head_len=3
tail_len=1

if [ "$#" != "2" ] ; then
  echo "$# args, need 2 args: <generated header> <input header/dir>"
  exit 1
fi

header=$1
fpath=$2

header_temp=`basename ${header}`_temp
header_head=${header_temp}_head
header_defs=${header_temp}_defs
header_tail=${header_temp}_tail

head -n $head_len $header > $header_head
tail -n $tail_len $header > $header_tail

while [ 1 ] ; do
  make > log.txt 2>&1
  cat log.txt | sed -n '/\( forward declaration \| unknown type name \| undeclared identifier \)/ p' | sed "s/^[^']*'//" | sed "s/'.*$//" | sed "s/^.*://" | sed "s/\s.*$//" > list.txt
  list_len=`cat list.txt | wc -l`
  if [ "$list_len" = "0" ] ; then
    echo done
    exit 0
  fi

  cat list.txt > list_passed.txt
  $BIN_DIR/lstfiltr.py list_passed.txt > list.txt
  wc -l list.txt
  
  time $BIN_DIR/defcut.py list.txt $fpath > $header_defs
  cat $header_head > $header
  echo "//#include \"$fpath\"" >> $header
  cat $header_defs >> $header
  cat $header_tail >> $header
done
