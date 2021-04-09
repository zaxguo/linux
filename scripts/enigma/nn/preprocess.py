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
    out = open(t + '.trace', 'w')
    offset = 0
    for line in f:
        call = syscall.search(line)
        if call:
            op = call[1]
            s = '{0},{1},{2}\n'
            if op == 'lseek':
                size = call[2]
                arg = call[3]
                s = s.format(1,size,0)
                # out.write(s)
            elif op == 'read':
                size = call[3]
                s = s.format(0, size, 0)
                # out.write(s)
            else:
                while True:
                    print("wrong op!!!")
            out.write(s)
    out.close()
    f.close()

for t in traces:
    process_one(t)

