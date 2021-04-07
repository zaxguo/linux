#!/usr/bin/python3
import os
import sys
from statistics import mean
from statistics import median

if len(sys.argv) != 3:
    print("Wrong number of args.");
    sys.exit(0)

dmsg_log = sys.argv[1]

f = open(dmsg_log, 'r')
out_actual = open('actual.log', 'w')
out_sybil  = open('sybil.log', 'w')
actual_timing = {}
sybil_timing = {}
timings = []
timings.append(actual_timing)
timings.append(sybil_timing)

for line in f:
    if "lo_read_simple" not in line:
        continue
    tmp = line.strip().split(' ')[-1].split(',')
    if len(tmp) != 4:
        continue
    tmp = list(map(int, tmp))
    fs = tmp[0]
    block = tmp[1]
    phys_block = tmp[2]
    time = tmp[-1]
    if fs == 1 and phys_block == 0:
        continue
    timing_dict = timings[fs]
    if block not in timing_dict:
        timing_dict[block] = [time]
    else:
        timing_dict[block].append(time)

# output based on sybil
actual_dic = timings[0]
sybil_dic = timings[1]

def get_time(dic, key):
    return int(median(dic[key]))

for key in sorted(actual_dic):
    if key not in sybil_dic:
        continue
    actual_time = get_time(actual_dic, key)
    sybil_time = get_time(sybil_dic, key)
    s = "{0},{1}\n".format(key, actual_time)
    out_actual.write(s)
    s = "{0},{1}\n".format(key, sybil_time)
    out_sybil.write(s)


# padding
sybil = timings[1]
padding = int(sys.argv[2])
out_padding = open('padding.log', 'w')
for key in sorted(sybil):
    time = get_time(sybil, key) + padding
    s = "{0},{1}\n".format(key, time)
    out_padding.write(s)

out_actual.close()
out_sybil.close()
out_padding.close()
f.close()



