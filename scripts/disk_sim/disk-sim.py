import numpy as np
import matplotlib.pyplot as plt, mpld3
from matplotlib import cm
import random
from collections import OrderedDict
from kde_fit import init_kde




# Some parameters

# initial # of  sbd
n_sbd = 5
# write size
append_size = 32
sector_size = 512
sample_size = 10000
timeout = 100
max_gen = 500


# generated samples from real distribution
samples = []
gens = {}
fses = []
rename_ts = {}
rename_count = 0
fork_count = 0
colors = ['r', 'g', 'b', 'c', 'm', 'y', 'k']
mymap = plt.get_cmap("tab20b")
_colors = mymap.colors

class fs:
    def __init__(self, timer, _id, plt=None):
        # timer
        self.timer   = timer
        self.timer_val = timer
        # global clock
        self.clock   = 0
        self.id = _id
        # metadata change
        self.written = 0
        self.gen     = 0
        # plotting, optional
        self.plt     = plt

    def __str__(self):
        return "[fs: %d, gen: %d, timer = %d, clock = %d]" % (self.id, self.gen, self.timer, self.clock)

    def __eq__(self, other):
        return self.id == other.id

    def reset_timer(self):
        self.timer = self.timer_val

    def curr_gen(self):
        return self.gen

    # if other fses have same metadata
    def can_rename(self):
        # must have at least 2 fses to be meaningful
        if len(gens[self.gen]) > 1:
            ret = []
            for fs in gens[self.gen]:
                if fs.written == self.written:
                    ret.append(fs)
            if len(ret) > 1:
                return ret
        return None

    def _can_rename(self):
        # must have at least 2 fses to be meaningful
        return (len(gens[self.gen]) > 1)



    def rename(self, fs_list):
        print("rename at ", self.clock, "gen = ", self.gen, ", fs # =", len(fs_list))
        random.shuffle(fs_list)
        global rename_ts, rename_count
        rename_ts[self.gen][self.clock] = []
        rename_count += 1
        _c = self.get_color()
        for fs in fs_list:
            rename_ts[self.gen][self.clock].append(fs.id)
            fs.reset_timer()
            self.plt.plot(self.clock, fs.id, marker = '|', c = _c, markersize=10, lw=2);
            #self.plt.plot(self.clock, fs.id, marker = '|', c = _colors[self.gen % len(_colors)], markersize=10, lw=2);


    def get_color(self):

        r = random.random()
        g = random.random()
        b = random.random()
        return (r,g,b)


    def fork(self):
        global fork_count
        fork_count += 1
        new_fs = fs(self.timer_val, len(fses), plt)
        new_fs.gen = self.gen
        new_fs.clock = self.clock
        print("new fs gen =", new_fs.gen)
        gens[new_fs.gen].append(new_fs)
        fses.append(new_fs)
        _x = self.clock
        _y = new_fs.id
        # point to next tick
        #ax.annotate('', xy=(_x + 1, _y), xycoords='data', xytext=(_x, self.id), textcoords='data', arrowprops=dict(arrowstyle="-|>", connectionstyle='bar', color='b', lw=1))
        ax.annotate('', xy=(_x + 1, _y), xycoords='data', xytext=(_x, self.id), textcoords='data', arrowprops=dict(arrowstyle="-|>", connectionstyle='bar,fraction=-0.1', color='b', lw=1))
        self.plt.plot(self.clock, self.id, marker = '*', color = 'r');


    def tick(self):
        self.clock += 1
        self.timer -= 1
        if self.timer == 0:
            print("FS [" + str(self.id) + "] timed out!")
            self.reset_timer()
            rename_fs = self.can_rename()
            if rename_fs is not None:
                self.rename(rename_fs)
            else:
                self.fork()
                print(self, "cannot rename!! fork!!")

    def write(self, cnt):
        self.written += cnt
        if self.written > sector_size:
            gens[self.curr_gen()].remove(self)
            self.gen += 1
            if self.curr_gen() not in gens.keys():
                gens[self.curr_gen()] = [self]
            else:
                gens[self.curr_gen()].append(self)
            print("gens size: ", len(gens))
            self.written -= sector_size
            print("fs[" + str(self.id) + "]->[" + str(self.gen) + "]")
            if self.plt is not None:
                self.plt.plot(self.clock, self.id, marker = 'o', color = colors[self.gen % len(colors)]);




def disk_sim(tick, traces, fses, plt):
    for i in range(tick):
        n_fs = len(fses)
        for j in range(n_fs):
            trace = traces[j % n_sbd]
            fs = fses[j]
            fs.write(trace[i])
            fs.tick()

fig, ax = plt.subplots()
#ax.xaxis.set_ticks(np.arange(0, sample_size + 20, 10))
plt.xlim(0, sample_size)
#ax.yaxis.set_ticks(np.arange(0, n_sbd , 1))
#ax.yaxis.set_ticks(np.arange(0, 50, 1))
#ax.yaxis.grid(color='k')

kde = init_kde('bus')

# initialize
for i in range(n_sbd):
    # sampled interval
    interval = kde.sample(sample_size).astype(int)
    # post process into timestamp
    sample = [0] * sample_size
    sample = np.asarray(sample)
    j = 0
    k = 0
    j += interval[k]
    while j < sample_size and k < sample_size:
        sample[j] = 1
        next_write = interval[k]
        if next_write < 0:
            next_write = 0
        j += next_write
        k += 1

    samples.append(sample * append_size)
    print(samples[i])

    _fs = fs(timeout, i, plt)
    if 0 not in gens.keys():
        gens[0] = [_fs]
    else:
        gens[0].append(_fs)
    fses.append(_fs)

for i in range(max_gen):
    rename_ts[i] = {}

print(gens)
disk_sim(sample_size, samples, fses, plt)
print("rename:", rename_ts)

print("rename count:", rename_count)
print("fork count:", fork_count)
plt.show()
# for interactive html
#mpld3.save_html(fig, 'disk_sim.html')
#mpld3.show()






