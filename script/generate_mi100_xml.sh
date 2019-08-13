#!/bin/bash

BDIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

gfxip="gfx908"

path="$BDIR/../gfxip"
# input files
rai_file=$path/"mi100_chip_interface_internal.rai"
gcea_file=$path/"VG20_MI100_GCEA_PERFCOUNTER0_CFG.txt"
mcvml2_file=$path/"MC_VM_L2_PERFCOUNTER0_CFG.txt"

# output files
xml_file="$path/${gfxip}_mi100_metrics.xml"             # all blocks
blocks_xml="${gfxip}_`basename $rai_file .rai`.xml"     # general blocks
gcea_xml="${gfxip}_`basename $gcea_file .txt`.xml"      # gcea block
mcvml2_xml="${gfxip}_`basename $mcvml2_file .txt`.xml"  # mcvml2 block
echo $xml_file

# parse general blocks like SQ/TCP/TA/..., generate blocks_xml/xml_file
$BDIR/pmcextr.py $rai_file $gfxip
mv $blocks_xml $xml_file

# parse GCEA block, and merge results into xml_file
printf "\nParse [GCEA]   block, appended to '$xml_file'\n"
$BDIR/pmc_mem_extr.py $gcea_file $gfxip > /dev/null 2>&1
sed -i '$d' $xml_file                   # delete last line </gfx9>
sed -i 's/TCC_EA0_/TCC_EA_/g' $xml_file # rename 'TCC_EA0' to 'TCC_EA'
tail -n+2 $gcea_xml >> $xml_file        # skip first line <gfx9>

# parse MCVML2 block, and merge results into xml_file
printf "\nParse [MCVML2] block, appended to '$xml_file'\n"
$BDIR/pmc_mem_extr.py $mcvml2_file $gfxip > /dev/null 2>&1
sed -i '$d' $xml_file                   # delete last line </gfx9>
tail -n+2 $mcvml2_xml >> $xml_file      # skip first line <gfx9>
