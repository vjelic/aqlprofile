#!/usr/bin/python
import os, sys, re

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

# parse event from the matched string and output to xml
def parse_event(m, ngroups, pref, pattern_trim, pattern_norm, out, block, nth_event):
  assert (ngroups >= 3),"must be at least 3 groups"
  event_ind =  int(m.group(1).strip())
  event_suff = m.group(2).strip()
  event_descr = m.group(3).strip()
  if pref and pattern_trim and pattern_norm:
    # GCEA
    event_name = '_'.join([pref, event_suff, event_descr])
    event_name = pattern_trim.sub('', event_name)
    event_name = pattern_norm.sub('_', event_name)
    event_name = pattern_norm.sub('_', event_name)
  else:
    # others, e.g., MCVML2
    event_name = event_suff
    block = event_name.split("_")[0]

  # first time, output block info
  if nth_event == 0:
    out.write("  # " + block + " counters\n")

  write_xml(out, event_name, block, str(event_ind), event_descr)
  print str(event_ind) + ' : ' + event_name

  return event_ind

#############################################################

def parse_rai_descr(inp, out, block='GCEA', pref='EA_PERF'):
  # 4 | rdram | {3`b0, start0} | Transaction `start` from latency sampler 0 5 | rdram | {3`b0, end0 } | Transaction `end` from latency sampler 0 ...
  #  4 : EA_PERF_rdram_Transaction_start_from_latency_sampler_0 : "Transaction `start` from latency sampler 0"
  #  5 : EA_PERF_Transaction_end_from_latency_sampler_0 : "Transaction `end` from latency sampler 0"
  #pattern = re.compile(r'\s(\d+)\s|\s(\w*)\s?|[^|]*|([^|]*|?)')
  # pattern: all events in a line, see (vg10) GCEA_PERFCOUNTER0_CFG.txt
  pattern_rec = re.compile(r'\s+(\d+)\s*\|\s*(\w*)\s*\|[^|]*\|\s*([^|]+)(\s\d+\s*\||$)')
  # pattern2: one event per line, see VG20_MI100_GCEA_PERFCOUNTER0_CFG.txt
  pattern2_rec = re.compile(r'^\s*(\d+)\s*\|\s*(\w*)\s*\|[^|]*\|\s*([^|]+)\s*$')
  # pattern3: one event per line, see MC_VM_L2_PERFCOUNTER0_CFG.txt
  #   01 - MCVML2_PERF_SEL_BANK0_PTE_CACHE_REQ: number of bank0 pte cache requests
  pattern3_rec = re.compile(r'^\s*(\d+)\s*-\s*(\w*)\s*:\s*(.*)$')
  pattern_trim = re.compile(r'\s\d+\s\|$');
  pattern_norm = re.compile(r'(\W|_+)');
  pos = 0
  next_event = 0

  for line in inp.readlines():
    line = line[:-1]
    while pos < len(line):
      m = pattern_rec.search(line, pos)
      m2 = pattern2_rec.search(line, pos)
      m3 = pattern3_rec.search(line, pos)
      # matching first pattern
      if m:
        ngroups = len(m.groups())
        pos = m.end() - len(m.group(ngroups))

        event_ind = parse_event(m, ngroups, pref, pattern_trim, pattern_norm, out, block, next_event)

        if event_ind != next_event:
          print >>sys.stderr, "Warn: event skipped(" + str(next_event) + ")"
        next_event = event_ind + 1
      # matching pattern2
      elif m2:
        ngroups = len(m2.groups())
        parse_event(m2, ngroups, pref, pattern_trim, pattern_norm, out, block, next_event)
        next_event += 1

        break
      # matching pattern3
      elif m3:
        ngroups = len(m3.groups())
        parse_event(m3, ngroups, None, None, None, out, block, next_event)
        next_event += 1

        break
      # matching none, skip over
      else:
        print >>sys.stderr, "Skip line: \"" + line
        break
#############################################################

if (len(sys.argv) != 3):
  print >>sys.stderr, "Usage:", sys.argv[0], " <input description file> <gfxip in lower case, gfx8, gfx9, etc..>"
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
parse_rai_descr(inp, out)
close_xml(out, nms);
print "generated '" + out_name + "'"
#############################################################
