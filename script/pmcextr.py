#!/usr/bin/python
import os, sys, re

#blocks_list = [ "CPC", "CPF", "GDS", "GRBM", "GRBMSE", "SPI", "SQ", "SQCS", "SRBM", "SX", "TA", "TCA", "TCC", "TCP", "TD" ]
blocks_list = [ "CPC", "CPF", "GDS", "GRBM", "SPI", "SQ", "SX", "TA", "TCA", "TCC", "TCP", "TD", "GRBM_SE", "SDMA" ]

REC_MAX_LEN = 1024

def open_xml(name, nms):
  f = open(name, 'w')
  f.write("<" + nms + ">\n");
  return f

def close_xml(f, nms):
  f.write("</" + nms + ">\n");
  f.close()

def write_xml(out, event_name, block, event_id, descr):
  out.write("  <metric\n" +
            "    name=\"" + event_name + "\" block=" + block + " event=" + event_id + " descr=\"" + descr + "\"\n" +
            "  ></metric>\n")

def parse_event(rec_pattern, record, block, out):
  m = rec_pattern.search(record)
  # not a match, return
  if not m: return False

  # for SQ block, events start with 'SQ' or 'SQC'
  if block == "SQ" and m.group(1).startswith('C'): block += 'C'
  event_name = (block + "_" + m.group(2)).upper()
  event_id = int(m.group(4), 0)
  descr = m.group(3);
  descr = re.sub("\s+", " ", descr)
  descr = re.sub("\s*,", ",", descr)
  descr = re.sub("\s+$", "", descr)
  descr = re.sub(",$", ".", descr)
  write_xml(out, event_name, block, str(event_id), descr)

  return True
#############################################################

def parse_rai(inp, out, blist):
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

base = re.sub(r'(\.[^\.]+)$', '', raifile)
m = re.search(r'([^\/]*)$', base)
out_name = nms + '_' + m.group(1) + '.xml'

inp = open(raifile, 'r')
out = open_xml(out_name, nms)
parse_rai(inp, out, blocks_list)
close_xml(out, nms);
print "generated '" + out_name + "'"
#############################################################
