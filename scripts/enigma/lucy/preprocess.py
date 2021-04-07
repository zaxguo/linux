import os
import sys

filename = "keyword2.log"
f = open(filename, 'r')
post_file = filename + '.post'
out = open(post_file, 'w')

for line in f:
    line = line.split('\t')
    path = line[1]
    idx = path.find('mail_index')
    path = path[idx:]
    offset = int(line[2])
    size = int(line[-1])
    output = f'{path},{size},{offset}\n'
    out.write(output)

out.close()

