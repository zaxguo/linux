import os
import sys
import matplotlib.pyplot as plt
import scipy
import scipy.stats
from distfit import distfit
import numpy as np
import warnings

def process_file(_f):
    f = open(_f)
    objects = {}
    for line in f:
        tmp = line.split(',')
        obj = str(tmp[1])
        ts = int(tmp[0])
        if obj not in objects.keys():
            objects[obj] = [ts]
        else:
            prev = objects[obj].pop(-1)
            # update it to be interval
            objects[obj].append(ts - prev)
            objects[obj].append(ts)
    for key in objects.keys():
        objects[key].pop(-1)
    return objects


def fit(obj, key):
    y = obj[key]
    _y = np.asarray(y)
    dist = distfit(alpha = 0.05, smooth=10)
    model = dist.fit_transform(_y)
    dist.plot(model)
    dist.plot_summary()


obj = process_file("./bangor.csv")
fit(obj, 'bicycle')



