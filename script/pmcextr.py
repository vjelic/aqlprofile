#!/usr/bin/python
import os, sys, re

from cfg_handler import CfgHandler
import pmcextr_misc

handler = CfgHandler()

REC_MAX_LEN = 1024

def open_xml(name, nms):
  f = open(name, 'w')
  f.write("<" + nms + ">\n");
  return f

def close_xml(f, nms):
  f.write("</" + nms + ">\n");
  f.close()

def parse_event(rec_pattern, record, block, out):
  m = rec_pattern.search(record)
  # not a match, return
  if not m: return False

  blk_name = block
  # for SQ block, events start with 'SQ' or 'SQC'
  if block == "SQ" and m.group(1).startswith('C'): blk_name += 'C'
  event_name = (blk_name + "_" + m.group(2)).upper()
  event_id = int(m.group(4), 0)
  if not handler.is_event_specified(event_name, event_id, block): return True
  descr = m.group(3);
  descr = re.sub("\s+", " ", descr)
  descr = re.sub("\s*,", ",", descr)
  descr = re.sub("\s+$", "", descr)
  descr = re.sub(",$", ".", descr)
  # merge multi adjacent spaces into one
  descr = re.sub(' +', ' ', descr)
  pmcextr_misc.write_xml(out, event_name, block, str(event_id), descr)

  return True
#############################################################

def parse_rai(inp, out, blist, nrai_blocks):
  # event block ends with '};' on a single line
  end_pattern = re.compile("^};$")

  for block in blist:
    # TD_PERFCOUNTER0_SELECT   <GpuF0Reg:0x36c00> <GpuF1Reg:0x36c00>   32    {
    #   "TD_PERF_SEL_td_sp_traffic  :  Count the number of times this TD sends data to the SP. " = 0x2e,
    #   "SPI_PERF_VS_POS0_STALL  :  Number of clocks stalled due to pos buf space in SH0. " = 0x6,
    #   "GRBM_PERF_SEL_CPAXI_BUSY  :  The CPAXI block is busy. " = 0x25 }  ;
    # block prefix formats: TD_PERFCOUNTER0_SELECT, GRBM_SE0_PERFCOUNTER_SELECT, SDMA0_PERFMON_CNTL
    beg_pattern = re.compile("^" + block + "(_PERFCOUNTER0_SELECT|0_PERFCOUNTER_SELECT|0_PERFMON_CNTL)\s")
    # event prefix formats: TCP_PERF_SEL_, GRBM_SE0_PERF_SEL, SPI_PERF_
    event_expr= "\"" + block + "([0C]?_PERF_SEL_|_PERF_)(\w*)\s*:?\s*(\w?[^\"]*)\s*\"\s*=\s*(\w*)"
    # pattern of non-final event
    rec_pattern = re.compile(event_expr + ",")
    # pattern of final event
    last_pattern = re.compile(event_expr + "\s*\}\s*;")

    found = 0
    record = ""
    line_num = -1
    inp.seek(0, os.SEEK_SET)
    for line in inp.readlines():
      # stop when coming to a line signaling the block end
      # only take effect when the last_pattern was not captured
      if found and end_pattern.search(line): break;

      record += line[:-1]

      line_num += 1
      if len(record) > REC_MAX_LEN:
        print "Error: bad record \"" + record + "\"\nfile '" + raifile + ", line (" + str(line_num) + ")"
        break;

      if found:
        if last_pattern.search(record):
          # final event for the block, extract and stop
          parse_event(last_pattern, record, block, out)
          break
        else:
          match = parse_event(rec_pattern, record, block, out)
          if not match:
            continue
      elif beg_pattern.match(record):
        found = 1
        print >>sys.stderr, "\tblock: " + block
        out.write("  # " + block + " counters\n")

      record = ""

    if not found:
      if block in handler.list_blocks(): nrai_blocks.append(block)
      else:
        print >>sys.stderr, "Error: block '" + block + "' not found"
        sys.exit(1)
#############################################################

if (len(sys.argv) < 3):
  print >>sys.stderr, "Usage:", sys.argv[0], " <path to .rai and misc> <gfxip in lower case, gfx8, gfx9, etc..>"
  sys.exit(1)

gfxip = sys.argv[1]     # gfxip version, e.g., gfx906

filepath = sys.argv[2]  # path to the .rai and misc files
if not os.path.isdir(filepath):
  print >>sys.stderr, "Error: path '" + filepath + "' not found"
  sys.exit(1)

# find out the regspec file
raifile = handler.get_file(filepath, gfxip, ".rai")
print >>sys.stderr, "read from: " + raifile

# parse the cfgfile, if there is one specified
if len(sys.argv) > 3:
  cfgfile = sys.argv[3]
  handler.parse_cfgfile(gfxip, cfgfile)

# blocks to be generated, including .rai and misc
# 1) all blocks, if no cfgfile
# 2) only designated ones, ow
all_blocks = handler.list_blocks()

# prepare output file
out_name = filepath + '/' + gfxip + '_metrics.xml'
out = open_xml(out_name, gfxip)

# parse .rai file, and meanwhile record those blocks not covered in the file
inp = open(raifile, 'r')
nrai_blocks = []
parse_rai(inp, out, all_blocks, nrai_blocks)
inp.close()

# parse the misc blocks not in .rai
for nrai_block in nrai_blocks:
  miscfile = handler.get_file(filepath, gfxip, nrai_block)
  print >>sys.stderr, "read from: " + miscfile
  print >>sys.stderr, "\tblock: " + nrai_block
  inp = open(miscfile, 'r')
  pmcextr_misc.parse_nrai(handler, inp, out, nrai_block)
  inp.close()
close_xml(out, gfxip);
print >>sys.stderr, "output to: " + out_name
#############################################################
