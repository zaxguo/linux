#!/usr/bin/python3
import os
import sys
import pandas as pd
import matplotlib.pyplot as plt

files = ['./actual.log', './sybil.log', './padding.log']

for f in files:
    ff = pd.read_csv(f, index_col=False, header=None)
    # ns to us
    time = ff.iloc[:, 1]
    plt.plot(time, label=f)

axes = plt.gca()
axes.set_ylim([3000,100000])
axes.legend()

plt.show()

