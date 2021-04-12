#!/usr/bin/python3
import os
import sys
import re

traces = [
        "densenet121.log",
        "efficientnetb0.log",
        "inceptionresnetv2.log",
        "inceptionv3.log",
        "mobilenet_v3_small.log",
        "nasnetmobile.log",
        "resnet101.log",
        "resnet50.log",
        "vgg16.log",
        "xception.log"
        ]

# syacall pattern
p = "(read|write|lseek)\(4, (.*), (.*)\)"
syscall = re.compile(p)

def process_one(t):
    f = open(t, 'r')
    out = open(t + '.pread', 'w')
    offset = 0
    for line in f:
        call = syscall.search(line)
        if call:
            op = call[1]
            size = 0
            if op == 'lseek':
                size = call[2]
                arg = call[3]
                offset = int(size)
            elif op == 'read':
                size = int(call[3])
                s = '{0},{1},{2}\n'.format(0, size, offset)
                offset += size
                out.write(s)
            else:
                while True:
                    print("wrong op!!!")
    out.close()
    f.close()

for t in traces:
    process_one(t)

