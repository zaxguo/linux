import os
import sys
import matplotlib
import matplotlib.pyplot as plt
import scipy
import scipy.stats
import numpy as np
import warnings
import pandas as pd
from statsmodels.nonparametric.kde import KDEUnivariate
from sklearn.neighbors import KernelDensity

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


def fit(data, key):
    X_plot = np.linspace(0, 100, 100)[:, np.newaxis]
    data = np.asarray(data)[:, np.newaxis]
    print(data)
    quit()
    dens = KernelDensity(kernel='gaussian').fit(data)
    ''' for validation only
    fig, ax = plt.subplots()
    log_dens = dens.score_samples(X_plot)
    samples = dens.sample(1000)
    print("generated samples:", samples.astype(int))
    print("validate samples...")
    dens_test = KernelDensity(kernel='gaussian').fit(samples)
    log_dens_test = dens_test.score_samples(X_plot)

    ax.plot(X_plot[:, 0], np.exp(log_dens), color='navy', label="sample for '{0}'".format(key))
    ax.plot(X_plot[:, 0], np.exp(log_dens_test), color='orange', label="test for '{0}'".format(key))

    plt.legend(loc='upper right')
    plt.show()
    '''
    return dens


def init_kde(keyword):
    obj = process_file("../../../../../Documents/research/enigma/bangor.csv")
    saved_file = open("./bangor.log", 'w')
    for interval in obj[keyword]:
        to_write = "{}\n".format(interval)
        saved_file.write(to_write)
    print(obj[keyword])
#    return fit(obj[keyword], keyword)

init_kde('bus')
