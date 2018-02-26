#!/usr/bin/python
import os, sys, re

#blocks_list = [ "CPC", "CPF", "GDS", "GRBM", "GRBMSE", "SPI", "SQ", "SQCS", "SRBM", "SX", "TA", "TCA", "TCC", "TCP", "TD" ]
blocks_list = [ "CPC", "CPF", "GDS", "GRBM", "SPI", "SQ", "SX", "TA", "TCA", "TCC", "TCP", "TD", "GRBMSE", "SQCS", "SRBM" ]

REC_MAX_LEN = 1024

def open_xml(name, nms):
  f = open(nms + "_metrics.xml", 'w')
  f.write("<" + nms + ">\n");
  return f

def close_xml(f, nms):
  f.write("</" + nms + ">\n");
  f.close()

def write_xml(out, event_name, block, event_id, descr):
  out.write("  <metric\n" +
            "    name=\"" + event_name + "\" block=" + block + " event=" + event_id + " descr=\"" + descr + "\"\n" +
            "  ></metric>\n")
#############################################################

def parse_rai(inp, out, blist):
  end_pattern = re.compile("}")

  for block in blist:
    # TD_PERFCOUNTER0_SELECT   <GpuF0Reg:0x36c00> <GpuF1Reg:0x36c00>   32    {
    #   "TD_PERF_SEL_td_sp_traffic  :  Count the number of times this TD sends data to the SP. " = 0x2e,
    #   "SPI_PERF_VS_POS0_STALL  :  Number of clocks stalled due to pos buf space in SH0. " = 0x6,
    beg_pattern = re.compile("^" + block + "_PERFCOUNTER0_SELECT\s")
    rec_pattern = re.compile("\"([A-Z]*_PERF_SEL_|SPI_PERF_)(\w*)\s*:?\s*(\w?[^\"]*)\s*\"\s*=\s*(\w*),")
  
    found = 0
    record = ""
    line_num = -1 
    inp.seek(0, os.SEEK_SET)
    for line in inp.readlines():
      record += line[:-1]
  
      line_num += 1
      if len(record) > REC_MAX_LEN:
        print "Error: bad record \"" + record + "\"\nfile '" + raifile + ", line (" + str(line_num) + ")"
        break;
  
  
      if found:
        if end_pattern.search(record): break
        else:
          m = rec_pattern.search(record)
          if m:
            event_name = (block + "_" + m.group(2)).upper()
            event_id = int(m.group(4), 0)
            descr = m.group(3);
            descr = re.sub("\s+", " ", descr)
            descr = re.sub("\s*,", ",", descr)
            descr = re.sub("\s+$", "", descr)
            descr = re.sub(",$", ".", descr)
            write_xml(out, event_name, block, str(event_id), descr)
          else:
            continue
      elif beg_pattern.match(record):
        found = 1
        print line
        out.write("  # " + block + " counters\n")
  
      record = ""
 
    if not found:
      print >>sys.stderr, "Error: block '" + block + " not found"
      #break
#############################################################

if (len(sys.argv) != 3):
  print >>sys.stderr, "Usage:", sys.argv[0], " <input .rai file> <gfxip in lower case, gfx8, gfx9, etc..>"
  sys.exit(1)

raifile = sys.argv[1]
if not os.path.isfile(raifile):
  print >>sys.stderr, "Error: input file '" + raifile + "' not found"
  sys.exit(1)

nms = sys.argv[2]

inp = open(raifile, 'r')
out = open_xml("counters_out.xml", nms);
parse_rai(inp, out, blocks_list)
close_xml(out, nms);
#############################################################

