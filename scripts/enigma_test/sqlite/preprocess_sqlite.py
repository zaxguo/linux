import os
import sys

f = open('./selectA', 'r')
out = open('./strace_post', 'w')

for line in f:
    left = line.split('(')
    syscall = left[0] # pread or pwrite
    if syscall == "pread64":
        syscall = 0
    elif syscall == "pwrite64":
        syscall = 1
    else:
        print("Unrecognized syscall! exit..")
        break
    args = left[1].split(')')[0].split(',')
    size   = int(args[2])
    offset = int(args[-1])
    output = f'{syscall},{size},{offset}\n'
    out.write(output)

out.close()

