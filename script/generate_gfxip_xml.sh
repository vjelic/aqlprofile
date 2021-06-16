#!/bin/bash

BDIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

gfxip=$1    # gfxip name, gfx9/gfx906/gfx908
# cfg file to specify which events to generate
# empty:        all blocks and events
# not-empty:    only those specified in cfgfile, e.g., block_events.cfg
cfgfile=$2

# check the number of arguments
if [ "$#" != "1" ] && [ "$#" != "2" ] ; then
    printf "Usage: $0 <gfxip, supported gfx9/gfx906/gfx908> [cfgfile]\n"
    printf "\t\tno cfgfile: generate all blocks and events\n"
    printf "\t\texample cfgfile: script/block_events.cfg\n"
    exit
fi

# check the input gfxip; supported versions are gfx9/gfx906/gfx908....
if [[ ! "$gfxip" =~ ^(gfx9|gfx906|gfx908|gfx90a)$ ]]; then
    printf "Unknown GFXIP version \"$gfxip\", supported: gfx9/gfx906/gfx908/gfx90a\n"
    exit
fi

# check the existence of cfg file
if [ ! -z "$cfgfile" ] && [ ! -f "$cfgfile" ]; then
    printf "File '$cfgfile' cannot be found. Default: script/block_events.cfg\n"
    exit
fi

# file path
fpath="$BDIR/../gfxip"

# output files
xml_file="$fpath/${gfxip}_metrics.xml"       # all blocks

# prepare args, and then start extracting events/blocks
args="$gfxip $fpath"
if [ ! -z "$cfgfile" ]; then
  args=$args" $cfgfile"
fi
$BDIR/pmcextr.py $args > /dev/null

# check python return, non-zero indicates error
pyrtn=$?
if [ "$pyrtn" != "0" ]; then exit; fi

# rename 'TCC_EA0' to 'TCC_EA' to unify all gfx9x versions
sed -i 's/TCC_EA0_/TCC_EA_/g' $xml_file
