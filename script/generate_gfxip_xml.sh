#!/bin/bash

BDIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

# gfxip name, gfx9/gfx906/gfx908
gfxip=$1

# check the input gfxip, and create corresponding codename
codename=""
if [[ $gfxip == gfx9 ]]; then codename="vg10";
elif [[ $gfxip == gfx906 ]]; then codename="vg20";
elif [[ $gfxip == gfx908 ]]; then codename="mi100";
else
    printf "Usage: $0 <gfxip in lower case, supported gfx9, gfx906, gfx908>\n"
    exit
fi

# file path
path="$BDIR/../gfxip"

#---------------------- gfxip input settings -----------------
# gfx9/Vega10
gfx9_rai_file=$path/"gfx9_greenland_chip_interface.rai"
gfx9_gcea_file=$path/"GCEA_PERFCOUNTER0_CFG.txt"
gfx9_mcvml2_file=$path/"MC_VM_L2_PERFCOUNTER0_CFG.txt"

# gfx906/Vega20
gfx906_rai_file=$path/"vega20_chip_interface_internal.rai"
gfx906_gcea_file=$path/"VG20_MI100_GCEA_PERFCOUNTER0_CFG.txt"
gfx906_mcvml2_file=$path/"MC_VM_L2_PERFCOUNTER0_CFG.txt"

# gfx908/MI100
gfx908_rai_file=$path/"mi100_chip_interface_internal.rai"
gfx908_gcea_file=$path/"VG20_MI100_GCEA_PERFCOUNTER0_CFG.txt"
gfx908_mcvml2_file=$path/"MC_VM_L2_PERFCOUNTER0_CFG.txt"
#-------------------------------------------------------------

# input files, selected using the specified gfxip
rai_filename="${gfxip}_rai_file"; rai_file=${!rai_filename}
gcea_filename="${gfxip}_gcea_file"; gcea_file=${!gcea_filename}
mcvml2_filename="${gfxip}_mcvml2_file"; mcvml2_file=${!mcvml2_filename}

# output files
xml_file="$path/${gfxip}_${codename}_metrics.xml"       # all blocks
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
rm $gcea_xml                            # delete gcea xml file

# parse MCVML2 block, and merge results into xml_file
printf "\nParse [MCVML2] block, appended to '$xml_file'\n"
$BDIR/pmc_mem_extr.py $mcvml2_file $gfxip > /dev/null 2>&1
sed -i '$d' $xml_file                   # delete last line </gfx9>
tail -n+2 $mcvml2_xml >> $xml_file      # skip first line <gfx9>
rm $mcvml2_xml                          # delete mcvml2 xml file
