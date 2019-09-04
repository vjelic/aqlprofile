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
rai_path="$path/rai_files"
mem_path="$path/mem_files"

#---------------------- gfxip input settings -----------------
# gfx9/Vega10
gfx9_rai_file=$rai_path/"gfx9_greenland_chip_interface.rai"
gfx9_gcea_file=$mem_path/"VG10_GCEA_PERFCOUNTER0_CFG.txt"
gfx9_atc_file=$mem_path/"ATC.txt"
gfx9_atcl2_file=$mem_path/"ATC_L2.txt"
gfx9_mcvml2_file=$mem_path/"MC_VM_L2_PERFCOUNTER0_CFG.txt"

# gfx906/Vega20
gfx906_rai_file=$rai_path/"vega20_chip_interface_internal.rai"
gfx906_gcea_file=$mem_path/"VG20_MI100_GCEA_PERFCOUNTER0_CFG.txt"
gfx906_atc_file=$mem_path/"ATC.txt"
gfx906_atcl2_file=$mem_path/"ATC_L2.txt"
gfx906_mcvml2_file=$mem_path/"MC_VM_L2_PERFCOUNTER0_CFG.txt"

# gfx908/MI100
gfx908_rai_file=$rai_path/"mi100_chip_interface_internal.rai"
gfx908_gcea_file=$mem_path/"VG20_MI100_GCEA_PERFCOUNTER0_CFG.txt"
gfx908_atc_file=$mem_path/"ATC.txt"
gfx908_atcl2_file=$mem_path/"ATC_L2.txt"
gfx908_mcvml2_file=$mem_path/"MC_VM_L2_PERFCOUNTER0_CFG.txt"
#-------------------------------------------------------------

# input files, selected using the specified gfxip
rai_filename="${gfxip}_rai_file"; rai_file=${!rai_filename}
gcea_filename="${gfxip}_gcea_file"; gcea_file=${!gcea_filename}
atc_filename="${gfxip}_atc_file"; atc_file=${!atc_filename}
atcl2_filename="${gfxip}_atcl2_file"; atcl2_file=${!atcl2_filename}
mcvml2_filename="${gfxip}_mcvml2_file"; mcvml2_file=${!mcvml2_filename}

# output files
xml_file="$path/${gfxip}_${codename}_metrics.xml"       # all blocks
blocks_xml="${gfxip}_`basename $rai_file .rai`.xml"     # general blocks
gcea_xml="${gfxip}_`basename $gcea_file .txt`.xml"      # gcea block
atc_xml="${gfxip}_`basename $atc_file .txt`.xml"        # atc block
atcl2_xml="${gfxip}_`basename $atcl2_file .txt`.xml"    # atcl2 block
mcvml2_xml="${gfxip}_`basename $mcvml2_file .txt`.xml"  # mcvml2 block
echo $xml_file

# parse general blocks like SQ/TCP/TA/..., generate blocks_xml/xml_file
$BDIR/pmcextr.py $rai_file $gfxip
mv $blocks_xml $xml_file

sed -i 's/TCC_EA0_/TCC_EA_/g' $xml_file # rename 'TCC_EA0' to 'TCC_EA'

# parse GCEA and vm blocks (ATC/ATCL2/MCVML2), and merge results into xml_file
mem_parts="gcea atc atcl2 mcvml2"
for mem_part in $mem_parts
do
    printf "\nParse [%s]\tblock, appended to '$xml_file'\n" \
        `echo $mem_part | tr a-z A-Z`
    in_filename="${mem_part}_file"; in_file=${!in_filename}
    $BDIR/pmc_mem_extr.py $in_file $gfxip > /dev/null 2>&1
    out_filename="${mem_part}_xml"; out_file=${!out_filename}
    sed -i '$d' $xml_file                   # delete last line </gfx9>
    tail -n+2 $out_file >> $xml_file        # skip first line <gfx9>
    rm $out_file
done
