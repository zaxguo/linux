import os
import sys
import matplotlib
import matplotlib.pyplot as plt
import scipy
import scipy.stats
import numpy as np
import warnings
import pandas as pd

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


# https://stackoverflow.com/questions/6620471/fitting-empirical-distribution-to-theoretical-ones-with-scipy-python
def fit(data, bins=200):
    dist_names = [ 'alpha', 'anglit', 'arcsine', 'beta', 'betaprime', 'bradford', 'burr', 'cauchy', 'chi', 'chi2', 'cosine', 'dgamma', 'dweibull', 'erlang', 'expon', 'exponweib', 'exponpow', 'f', 'fatiguelife', 'fisk', 'foldcauchy', 'foldnorm', 'frechet_r', 'frechet_l', 'genlogistic', 'genpareto', 'genexpon', 'genextreme', 'gausshyper', 'gamma', 'gengamma', 'genhalflogistic', 'gilbrat', 'gompertz', 'gumbel_r', 'gumbel_l', 'halfcauchy', 'halflogistic', 'halfnorm', 'hypsecant', 'invgamma', 'invgauss', 'invweibull', 'johnsonsb', 'johnsonsu', 'ksone', 'kstwobign', 'laplace', 'logistic', 'loggamma', 'loglaplace', 'lognorm', 'lomax', 'maxwell', 'mielke', 'nakagami', 'ncx2', 'ncf', 'nct', 'norm', 'pareto', 'pearson3', 'powerlaw', 'powerlognorm', 'powernorm', 'rdist', 'reciprocal', 'rayleigh', 'rice', 'recipinvgauss', 'semicircular', 't', 'triang', 'truncexpon', 'truncnorm', 'tukeylambda', 'uniform', 'vonmises', 'wald', 'weibull_min', 'weibull_max', 'wrapcauchy']
    y, x = np.histogram(data, bins=bins, density=True)
    x = (x + np.roll(x, -1))[:-1] / 2.0

    best_distribution = 'norm'
    best_params = (0.0, 1.0)
    best_sse = np.inf

    for dist in dist_names:
        try:
            with warnings.catch_warnings():
                warnings.filterwarnings('ignore')
                dist = getattr(scipy.stats, dist)
                param = dist.fit(y)
                print("tried ", dist.name)

                arg = param[:-2]
                loc = param[-1]
                scale = param[-1]

                pdf = dist.pdf(x, loc=loc, scale=scale, *arg)
                sse = np.sum(np.power(_y - pdf, 2.0))

                if best_sse > sse > 0:
                    best_distribution = dist
                    best_params = param
                    best_sse = sse
                    print("Best dist:", dist.name)
                    print("SSE:", best_sse)
        except Exception:
            pass
    return (best_distribution, best_params)

def make_pdf(dist, params, size=10000):
    arg = params[:-2]
    loc = params[-2]
    scale = params[-1]

    dist = getattr(scipy.stats, dist)
    # Get sane start and end points of distribution
    start = dist.ppf(0.01, *arg, loc=loc, scale=scale) if arg else dist.ppf(0.01, loc=loc, scale=scale)
    end = dist.ppf(0.99, *arg, loc=loc, scale=scale) if arg else dist.ppf(0.99, loc=loc, scale=scale)


    x = np.linspace(start, end, size)
    y = dist.pdf(x, loc=loc, scale=scale, *arg)
    pdf = pd.Series(y,x)
    return pdf


obj = process_file("./bangor.csv")

data = pd.Series(obj['bicycle'])

print(data)

best_dist, best_params = fit(data)

print("Best dist:", best_dist)
print("Best params:", best_params)

pdf = make_pdf(best_dist, best_params)



plt.figure(figsize=(12, 8))



ax = pdf.plot(lw = 2, label='Best PDF', legend=True)

data.plot(kind='hist', bins=200, density=True, alpha=0.5, label='bicycle', legend=True, color=plt.rcParams['axes.prop_cycle'].by_key()['color'][1], ax=ax)

plt.show()
