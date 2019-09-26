#!/usr/bin/python
import os, sys, re

def write_xml(out, event_name, block, event_id, descr):
  out.write("  <metric\n" +
            "    name=\"" + event_name + "\" block=" + block + " event=" + event_id + " descr=\"" + descr + "\"\n" +
            "  ></metric>\n")

# parse event from the matched string and output to xml
def parse_nrai_event(handler, m, ngroups, pref, pattern_trim, pattern_norm, out, block, nth_event):
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
    # others, e.g., ATCL2/MCVML2/ATC
    event_name = event_suff
    # replace some special chars
    p = re.compile('[,-/]')
    event_descr = p.sub(' ', event_descr)
    # format the event desc
    event_name = '_'.join(event_descr.split()[:8])
    # add block suffix and change to uppercase
    event_name = (block+'_'+event_name).upper()
    # get rid of '(' and ')'
    event_name = re.sub('[\(\)]', '', event_name)

  if not handler.is_event_specified(event_name, event_ind, block): return event_ind

  # first time, output block info
  if nth_event == 0:
    out.write("  # " + block + " counters\n")

  write_xml(out, event_name, block, str(event_ind), event_descr)
  print str(event_ind) + ' : ' + event_name

  return event_ind

#############################################################

def parse_nrai(handler, inp, out, block='GCEA', pref='GCEA_PERF'):
  # pattern: all events in a line, see (vg10) gfx9_GCEA_PERFCOUNTER0_CFG.txt
  # 4 | rdram | {3`b0, start0} | Transaction `start` from latency sampler 0 5 | rdram | {3`b0, end0 } | Transaction `end` from latency sampler 0 ...
  pattern_rec = re.compile(r'\s+(\d+)\s*\|\s*(\w*)\s*\|[^|]*\|\s*([^|]+)(\s\d+\s*\||$)')
  # pattern2: one event per line, see (vg20/mi100) gfx906_gfx908_GCEA_PERFCOUNTER0_CFG.txt
  #  4 : EA_PERF_rdram_Transaction_start_from_latency_sampler_0 : "Transaction `start` from latency sampler 0"
  pattern2_rec = re.compile(r'^\s*(\d+)\s*\|\s*(\w*)\s*\|[^|]*\|\s*([^|]+)\s*$')
  # pattern3: one event per line, see gfx9x_MCVML2_PERFCOUNTER0_CFG.txt, or ATC/ATCL2
  #   1   side0 bank0 pte cache bigk0 request
  #event 1 = event start for statistical min sclks from ATC_RPB_req translation request to RPB_ATC_ret completion
  # \# Event1 : number of L1 requests
  pattern3_rec = re.compile(r'^#*[Eevnt\s]*(\d+)\s*-*\s*(\w*)\s*[:=]?\s*(.*)$')

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

        event_ind = parse_nrai_event(handler, m, ngroups, pref, pattern_trim, pattern_norm, out, block, next_event)

        if event_ind != next_event:
          print >>sys.stderr, "Warn: event skipped(" + str(next_event) + ")"
        next_event = event_ind + 1
      # matching pattern2
      elif m2:
        ngroups = len(m2.groups())
        parse_nrai_event(handler, m2, ngroups, pref, pattern_trim, pattern_norm, out, block, next_event)
        next_event += 1

        break
      # matching pattern3
      elif m3:
        ngroups = len(m3.groups())
        parse_nrai_event(handler, m3, ngroups, None, None, None, out, block, next_event)
        next_event += 1

        break
      # matching none, skip over
      else:
        print >>sys.stdout, "Skip line: \"" + line
        break
#############################################################
