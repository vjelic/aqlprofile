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
def parse_event(m, ngroups, pref, pattern_trim, pattern_norm, out, block):
  assert (ngroups >= 3),"must be at least 3 groups"
  event_id =  int(m.group(1).strip())
  event_suff = m.group(2).strip()
  event_descr = m.group(3).strip()
  event_name = '_'.join([pref, event_suff, event_descr])
  event_name = pattern_trim.sub('', event_name)
  event_name = pattern_norm.sub('_', event_name)
  event_name = pattern_norm.sub('_', event_name)

  write_xml(out, event_name, block, str(event_id), event_descr)
  print str(event_id) + ' : ' + event_name

  return event_id

#############################################################

def parse_rai_descr(inp, out, block, pref):
  # 4 | rdram | {3`b0, start0} | Transaction `start` from latency sampler 0 5 | rdram | {3`b0, end0 } | Transaction `end` from latency sampler 0 ...
  #  4 : EA_PERF_rdram_Transaction_start_from_latency_sampler_0 : "Transaction `start` from latency sampler 0"
  #  5 : EA_PERF_Transaction_end_from_latency_sampler_0 : "Transaction `end` from latency sampler 0"
  #pattern = re.compile(r'\s(\d+)\s|\s(\w*)\s?|[^|]*|([^|]*|?)')
  # pattern: all events in a line
  pattern_rec = re.compile(r'\s+(\d+)\s*\|\s*(\w*)\s*\|[^|]*\|\s*([^|]+)(\s\d+\s*\||$)')
  # pattern2: one event per line
  pattern2_rec = re.compile(r'\s*(\d+)\s*\|\s*(\w*)\s*\|[^|]*\|\s*([^|]+)\s*$')
  pattern_trim = re.compile(r'\s\d+\s\|$');
  pattern_norm = re.compile(r'(\W|_+)');
  pos = 0
  next_event = 0

  out.write("  # " + block + " counters\n")
  for line in inp.readlines():
    line = line[:-1]
    while pos < len(line):
      m = pattern_rec.search(line, pos)
      m2 = pattern2_rec.search(line, pos)
      # matching first pattern
      if m:
        ngroups = len(m.groups())
        pos = m.end() - len(m.group(ngroups))

        event_id = parse_event(m, ngroups, pref, pattern_trim, pattern_norm, out, block)

        if event_id != next_event:
          print >>sys.stderr, "Error: event skipped(" + str(next_event) + ")"
          sys.exit(1)
        next_event = event_id + 1
      # matching pattern2
      elif m2:
        ngroups = len(m2.groups())
        parse_event(m2, ngroups, pref, pattern_trim, pattern_norm, out, block)

        break
      # matching neither, skip over
      else:
        print >>sys.stderr, "Error: bad line: \"" + line
        break
#############################################################

if (len(sys.argv) != 3):
  print >>sys.stderr, "Usage:", sys.argv[0], " <input GCEA description file> <gfxip in lower case, gfx8, gfx9, etc..>"
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
parse_rai_descr(inp, out, 'GCEA', 'EA_PERF')
close_xml(out, nms);
print "generated '" + out_name + "'"
#############################################################
