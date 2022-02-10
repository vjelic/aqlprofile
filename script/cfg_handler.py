#!/usr/bin/python
import sys, re
import os, glob
from collections import OrderedDict

# blocks: 1) covered by .rai file; 2)missing in .rai, and are specified in misc files
# GCEA disabled
BLOCKS = [ "CPC", "CPF", "GDS", "GRBM", "SPI", "SQ", "SX", "TA", "TCA", "TCC", "TCP", "TD", "GRBM_SE",
           "ATCL2", "MCVML2", "ATC", "SDMA" ]

class CfgHandler:
  '''A handler to deal with user-specified configurations'''
  def __init__(self):
    self.prev_ip = ""                       # gfxip specified in prior lines
    self.blocks_dict = OrderedDict()        # dict to store blocks/events

  def get_file(self, path, gfxip, sym):
    '''locate the input file using the given path/gfxip/sym'''
    owd = os.getcwd()
    os.chdir(path)
    # filename formats:
    #  rai: <path>/rai_files/<gfxip>_*.rai,
    #       e.g., gfx9_greenland_chip_interface.rai
    #  misc: <path>/misc_files/*<gfxip>_*<block>_*,
    #       e.g., gfx906_gfx908_GCEA_PERFCOUNTER0_CFG.txt
    if sym != ".rai": sym = sym + '_*[!~]'
    # first, try to find exact match
    files = glob.glob('*/*' + gfxip +'_*' + sym)
    # not found, then try to find pattern match (gfx9x: gfx9/gfx906/gfx908)
    #       e.g, gfx9x_ATCL2_PERFCOUNTER_CFG.txt
    if (len(files) == 0):
      files.extend(glob.glob('*/*' + gfxip[0:4] + 'x_*' + sym))
    # a unique file is expected
    assert (len(files) == 1)

    os.chdir(owd)

    return path + '/' + files[0]

  def __parse_evts(self, evts_str):
    """process the events, which is inputted as a string"""
    ptn = re.compile(r"\w\[(\d+-?\d*)\]")   # event with pattern like SQ[10]
    evts = evts_str.strip().split()         # split the event string
    for evt in evts:                        # traverse the events
      blk = ""                              # which block the event belongs to
      m = ptn.search(evt)                   # is matching defined pattern?
      if not m:                             # no
        blk = evt.split('_')[0]
      else:                                 # yes
        blk = evt.split('[')[0]
        evt = m.group(1)
      # store the block and event
      if blk not in self.blocks_dict: self.blocks_dict[blk] = []
      self.blocks_dict[blk].append(evt)

  def parse_cfgfile(self, gfxip, cfgfile):
    """extract blocks and events from the provided cfg file, and save the"""
    """blocks and their events into a dict"""
    cfgin = open(cfgfile, 'r')
    ptn_cmnt = re.compile(r"^\s*#*")
    gfip_events = re.compile(r"^\s*(gfx\d+)\s*:(\w|(\[\d+-?\d*\])|\s)*$")
    only_events = re.compile(r"^\s*([\w]*)\s*:?\s*(\w|(\[\d+-?\d*\])|\s)*$")
    # read and check each line
    for line in cfgin.readlines():
      if not line.strip():                      # blank line, skip
        continue
      if gfip_events.match(line):               # gfxip:events line
        parts = line.strip().split(':')
        assert (len(parts) == 2)
        gfip = parts[0]; self.prev_ip = gfip    # record gfxip
        if gfip != gfxip: continue              # not desired gfxip
        evts = parts[1]
        self.__parse_evts(evts)
      elif only_events.match(line):             # events line
        if self.prev_ip != gfxip: continue      # not desired gfxip
        evts = line.replace(':', '').strip()
        self.__parse_evts(evts)
      elif ptn_cmnt.match(line): continue       # comment line (#), skip
      else: print "WARN: skip line: ",line
    cfgin.close()
    print self.blocks_dict

  def list_blocks(self):
    """list bocks, covered in .rai file, to be generated"""
    desired_blocks = BLOCKS
    if (len(self.blocks_dict) > 0): desired_blocks = self.blocks_dict.keys()

    return desired_blocks

  def __get_events_of_a_block(self, block):
    """list the specified events of a particular block"""
    desired_events = []
    if block in self.blocks_dict: desired_events = self.blocks_dict[block]

    return desired_events

  def is_event_specified(self, name, nid, block):
    """check whether an event, denoted using <name>/<nid>, is covered in the"""
    """specified <events>; return true, if covered or the <events> is not"""
    """specified, i.e., empty"""
    events = self.__get_events_of_a_block(block)
    # no particularly specified events, or the event falls into the specified
    if (len(events) == 0) or \
        (name in events) or (str(nid) in events): return True
    # do further check, if desired events are spcified in range, i.e., <x>-[y]
    else:
      for evt in events:
        if '-' not in evt: continue   # skip basic ones
        ids = evt.split('-')          # extract start and end
        startId = int(ids[0])
        endId = -1                    # -1 means max event id of the block
        if ids[1]: endId = int(ids[1])
        if nid >= startId and (nid <= endId or endId == -1): return True
    return False
