#!/usr/bin/python
import os, sys, re
import cPickle as pickle

state_filename = 'defcut_py_state'
state_map = {}
if os.path.isfile(state_filename):
    with open(state_filename,'rb') as f: state_map = pickle.load(f)

def dump_def(text, index): 
    p = re.compile(r'\\\s*$')
    output = ""
    while index < len(text):
        line = text[index]
        output += line
        line = line[:-1]
        if not p.search(line): break
        index += 1
    return output
#############################################################

def dump_block(text, index): 
    p = re.compile(r'}')
    output = "\n"
    while index < len(text):
        line = text[index]
        output += line
        if p.match(line): break
        index += 1
    return output
#############################################################

def dump_static_block(text, index): 
    p = re.compile(r'};')
    output = "\n"
    while index < len(text):
        line = text[index]
        output += line
        if p.search(line): break
        index += 1
    return output
#############################################################

def dump_rev_block(text, index): 
    p = re.compile(r'typedef\s');
    tlist = []
    while index >= 0:
        line = text[index]
        tlist.insert(0, line)
        if p.match(line): break
        index -= 1
    output = '\n' + ''.join(tlist)
    return output
#############################################################

def lookup_enum(text, index): 
    p = re.compile(r'enum\s+(\S+)\s');
    while index >= 0:
        m = p.search(text[index])
        if m: return m.group(1)
        index -= 1
    return ''
#############################################################

def def_cut(infile, names, name_map):
    out_map = {}
    if infile in state_map: out_map = state_map[infile]

    inf = open(infile, 'r')
    text = inf.readlines()

    expr_map = {}
    enum_expr_map = {}
    for name in names:
        expr_map[name] = re.compile(r'((#define|typedef|union|struct|static|}).*' + name + r'|(typedef\s+|)enum|class|template)')
        enum_expr_map[name] = re.compile(r'  ' + name + r'\s*[=,]')
    enum_match = re.compile(r'enum\s+(\w+)\W')
    enum_end_match = re.compile(r'}')

    enum_map = {}
    in_enum = 0
    enum_name = ''
    found = 0

    text_len = len(text)
    block_len = 10000
    for block_index in xrange(0, text_len, block_len):
        sys.stderr.write( \
            "\r" + " "*100 + "\r" + str(found) + "\t" + infile \
        )
        if block_index: sys.stderr.write(" : " + str(block_index))

        in_enum_passed = in_enum
        enum_name_passed = enum_name
        for name in names:
            if name in name_map: continue;

            in_enum = in_enum_passed
            enum_name = enum_name_passed

            expr = expr_map[name]
            enum_expr = enum_expr_map[name]

            end_index = block_index + block_len
            if end_index > text_len: end_index = text_len;
            for index in xrange(block_index, end_index):
                line = text[index]
                if index in out_map:
                    m = enum_match.search(line)
                    if m:
                        in_enum = 1
                        enum_name = m.group(1)
                    elif in_enum == 1:
                        if enum_end_match.match(line): in_enum = 0
                    continue

                if in_enum == 1:
                    if enum_expr.match(line):
                        enum_item = re.sub(r',?\s*$', r',\n', line)
                        out_map[index] = enum_item
                        name_map[name] = index
                        enum_map[enum_name] = 1
                        found += 1
                        continue
                    if enum_end_match.match(line):
                        if (enum_name in enum_map) and (enum_map[enum_name] == 1):
                            out_map[index] = '};\n'
                        in_enum = 0
                        continue
                elif expr.match(line):
                    if re.match(r'#define\s+' + name + r'(\s|\()', line):
                        out_map[index] = dump_def(text, index)
                        name_map[name] = index
                        found += 1
                        continue
                    m = enum_match.search(line)
                    if m:
                        in_enum = 1
                        enum_name = m.group(1)
                        out_map[index] = "#enum " + enum_name + " "
                        if (name == enum_name):
                            name_map[name] = index
                            if not enum_name in enum_map: enum_map[enum_name] = 0
                            found += 1
                            continue
                    if re.match(r'(typedef\s)?\s*(\w+)\s+' + name + r'(\W.*)?$', line):
                        if re.search(r'{', line) or re.match(r'{', text[index + 1]):
                            out_map[index] = dump_block(text, index)
                            name_map[name] = index
                            name = '_'
                            found += 1
                            continue
                    if re.match(r'typedef\s+((struct|union)\s+)?\w+\s+' + name + r';', line):
                        out_map[index] = line
                        name_map[name] = index
                        found += 1
                        continue
                    if re.match(r'}(\s*|.*\W)' + name + r'\W', line):
                        out_map[index] = dump_rev_block(text, index)
                        name_map[name] = index
                        found += 1
                        continue
                    if re.match(r'static\s+const\s+\w+\s+' + name + r'\W.*;', line):
                        out_map[index] = line
                        name_map[name] = index
                        found += 1
                        continue
                    if re.match(r'static\s+const\s+\w+\s+' + name + r'\W.*{', line):
                        out_map[index] = dump_static_block(text, index)
                        name_map[name] = index
                        found += 1
                        continue
                    if re.match(r'(class|template)', line):
                        out_map[index] = dump_block(text, index)
                        continue

    sys.stderr.write("\r" + " "*100 + "\r" + str(found) + "\t" + infile + "\n")
    for index in sorted(out_map.keys()):
        m = enum_match.search(out_map[index])
        if m:
            enum_name = m.group(1)
            if enum_name in enum_map:
                if enum_map[enum_name] == 1:
                    out_map[index] = "\nenum " + enum_name + " {\n"
                else:
                    index = name_map[enum_name]
                    out_map[index] = dump_block(text, index)
            if re.match('#', out_map[index]): del out_map[index]

    if len(out_map) != 0:
        out_code = "// include " + re.sub("^[\.\/]*", "", infile) + "\n"
        for index in sorted(out_map.keys()):
            out_code += out_map[index]
        sys.stdout.write(out_code)

    state_map[infile] = out_map
    
    return found
#############################################################

name_map = {}

nmfile = sys.argv[1]
path = sys.argv[2]

nmf = open(nmfile, 'r')
names = [ item[:-1] for item in nmf.readlines() ]

found = 0
if os.path.isfile(path):
    f = open(path, 'r')
    for line in f.readlines():
        m = re.search(r'include\W+([\.\/\w-]+)\W', line)
        if m:
            infile = m.group(1)
            found += def_cut('../' + infile, names, name_map)
elif os.path.isdir(path):
    for root, dirs, files in os.walk(path):
        for file_name in files:
            infile = root + '/' + file_name
            found += def_cut(infile, names, name_map)
else:
    sys.stderr.write("Path '" + path + "' is not found\n")
    sys.exit(1)

for name in names:
    if not name in name_map: sys.stderr.write(name + " is not found\n")

requested_names = len(names)
found_names = len(name_map)
missed_names = requested_names - found_names
total = found + missed_names;
sys.stderr.write(str(found) + "/" + str(missed_names) + "/" + str(total) + "/" + str(requested_names) + " found/missed/total/requested\n")

with open(state_filename, 'wb') as f: pickle.dump(state_map, f)
#############################################################
