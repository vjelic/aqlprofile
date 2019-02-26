#!/usr/bin/python
import os, sys, re

infile = sys.argv[1]
name_map = {}

inf = open(infile, 'r')
for line in inf.readlines():
    line = line[:-1]
    if line in name_map:
        continue
    name_map[line] = 1
    print(line)
