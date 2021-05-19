import numpy as np
import matplotlib.pyplot as plt, mpld3
from matplotlib import cm
import random
import statistics as st
from collections import OrderedDict
from kde_fit import init_kde
from enum import Enum

class app(Enum):
    VIDEO    = 0
    ROSBAG   = 1


# Some parameters

random.seed()
# initial # of  sbd
n_sbd = 10

# write size
append_size = 128
sector_size = 512
sample_size = 8000
trace_count = 10
# 1 tick = 0.01s ==> timeout = 1s
timeout = 100
max_gen = 500

actual_lineage = 0

history = []
ts_global = [None] * sample_size
care_list = set()
care_list.add(actual_lineage)
# generated samples from real distribution
samples = []
gens = {}
fses = []
# offspring set
s1 = []
s2 = []
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
        self.age = 0
        self.id = _id
        # metadata change
        self.written = 0
        self.gen     = 0
        # metadata for retiring strategy
        self.retired = False
        # the parent, must be one of genesis fses
        self.parent  = -1

        # plotting, optional
        self.plt     = plt


    def __str__(self):
        return "[fs: %d, gen: %d, timer = %d, clock = %d, parent = %d]" % (self.id, self.gen, self.timer, self.clock, self.parent)

    def __repr__(self):
        return "[fs: %d, gen: %d, timer = %d, clock = %d, parent = %d]" % (self.id, self.gen, self.timer, self.clock, self.parent)

    def __eq__(self, other):
        return self.id == other.id

    def reset_timer(self):
        self.timer = self.timer_val

    def curr_gen(self):
        return self.gen

    def is_retired(self):
        return (self.retired == True)

    def retire(self):
        self.retired = True


    def get_parent(self):
        return self.parent

    def set_parent(self, par):
        self.parent = par

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

    def is_same_parent(self, parent):
        return (self.parent == parent)

    def add_to_probable(self, fs_list):
        #print("s1: --------")
        #print(s1)
        #print("s2: --------")
        #print(s2)
        tmp = set()

        should_care = False
        for fs in fs_list:
            if fs.get_parent() in care_list:
                should_care = True
                break

        for fs in fs_list:
            if self.id == fs.id:
                continue
            # apply to rename across geneis fses
            if self.is_same_parent(fs.get_parent()) == True:
                continue
            else:
                self_id = self.id
                self_parent = self.get_parent()
                fs_id = fs.id
                fs_parent = fs.get_parent()

                # rename is transistive, e.g. consider rename of (0, 1), then (1, 2)
                # when we backtrack until (0, 1), we must consider the histories of 2 (because 1 mingled with 2)
                # the list grows as rename is transistive
                if should_care:
                    # what lineages are invovled in the rename
                    tmp.add(fs_parent)
                    tmp.add(self_parent)
                    # transistively care about other lineages
                    care_list.add(fs_parent)
                    if len(care_list) > 1:
                        print("carelist => ", care_list)

                # add to S2 of both parent
                if len(s1[self_parent]) > 1:
                    if self_id in s1[self_parent]:
                        s1[self_parent].remove(self_id)
                    s2[self_parent].add(self_id)
                if len(s1[fs_parent]) > 1:
                    if fs_id in s1[fs_parent]:
                        s1[fs_parent].remove(fs_id)
                    s2[fs_parent].add(fs_id)
                s2[self_parent].add(fs_id)
                s2[fs_parent].add(self_id)
                if self_parent == 0:
                    print("actual has ", len(s2[self_parent]), " indistinguishable histories")
        if len(tmp) > 0:
            history.append(tmp)
            print(self.clock)
            #ts_global[self.clock] = tmp


    def rename(self, fs_list):
        global rename_ts, rename_count
        #rename_ts[self.gen][self.clock] = []
        rename_count += 1
        _c = self.get_color()
        paint = False
        #print("[rename]:", fs_list)
        for fs in fs_list:
            #rename_ts[self.gen][self.clock].append(fs.id)
            fs.reset_timer()
            fs.add_to_probable(fs_list)
            #self.plt.plot(self.clock, fs.id, marker = '|', c = _c, markersize=10, lw=2);
            #self.plt.plot(self.clock, fs.id, marker = '|', c = _colors[self.gen % len(_colors)], markersize=10, lw=2);

    def get_color(self):
        r = random.random()
        g = random.random()
        b = random.random()
        return (r,g,b)

    def fork(self):
        global fork_count
        fork_count += 1

        parent = self.get_parent()
        new_fs = fs(self.timer_val, len(fses), plt)
        new_fs.gen = self.gen
        new_fs.clock = self.clock
        new_fs.set_parent(parent)
        # add to S1
        s1[parent].add(new_fs.id)
        #print("new fs gen =", new_fs.gen)
        gens[new_fs.gen].append(new_fs)
        fses.append(new_fs)
        _x = self.clock
        _y = new_fs.id
        '''
        if parent == actual_lineage:
            ts_global[self.clock] = 'fork'
        '''
        # point to next tick
        #ax.annotate('', xy=(_x + 1, _y), xycoords='data', xytext=(_x, self.id), textcoords='data', arrowprops=dict(arrowstyle="-|>", connectionstyle='bar', color='b', lw=1))
       #ax.annotate('', xy=(_x + 1, _y), xycoords='data', xytext=(_x, self.id), textcoords='data', arrowprops=dict(arrowstyle="-|>", connectionstyle='bar,fraction=-0.1', color='b', lw=1))
       #self.plt.plot(self.clock, self.id, marker = '*', color = 'r');
        return new_fs

    def tick(self):
        self.clock += 1
        self.timer -= 1
        self.age   += 1
        if self.timer == 0:
            #print("FS [" + str(self.id) + "] timed out!")
            self.reset_timer()
            rename_fs = self.can_rename()
            if rename_fs is not None:
                self.rename(rename_fs)
            else:
                new_fs = self.fork()
                #print(self, " forked to ", new_fs)


    def write(self, cnt):
        self.written += cnt
        # triggers block allocation
        if self.written > sector_size:
            written = self.written
            new_blks = int(written / sector_size)
            assert (new_blks >= 1), "Not triggering block allocation! Bug..."
            remaining = written % sector_size
            gens[self.curr_gen()].remove(self)
            self.gen += new_blks
            if self.curr_gen() not in gens.keys():
                gens[self.curr_gen()] = [self]
            else:
                gens[self.curr_gen()].append(self)
            #print("gens size: ", len(gens))
            #self.written -= sector_size
            self.written = remaining
            #print("fs[" + str(self.id) + "]-> gen[" + str(self.gen) + "]")
            #if self.plt is not None and self.parent == 0:
                #self.plt.plot(self.clock, self.id, marker = 'o', color = colors[self.gen % len(colors)]);


def _retire(to_retire):
    success = 0
    # stats
    ages = []
    for e in to_retire:
        fses[e].retire()
        ages.append(fses[e].age)
        #plt.plot(fses[e].clock, fses[e].id, marker = 'x', color = 'k');
        success += 1
    '''
    if success >= 1:
        print("--age stat--")
        print("min:", min(ages), "max:", max(ages))
        print("mean:", st.mean(ages), "median:", st.median(ages))
    '''
    return success

def retire():
    s3 = set()
    # first get rid of all s2
    for i in range(len(s2)):
        s3  = s3.union(s2[i])
        assert (len(s1[i]) >= 1), "Empty S1!!!"
        s2[i].clear()
        # get as much as possible fs from s1
        while len(s1[i]) > 1:
            s3.add(s1[i].pop())
        # S3 = S3 - S1
        s3 = s3.difference(s1[i])

    num = _retire(s3)
    '''
    print("retired ", num, "fses:", s3)
    print("remaining: ", len(s1), "fses...")
    print(s1)
    '''
    return

def disk_sim(tick, traces, fses, plt):
    for i in range(tick):
        n_fs = len(fses)
        for j in range(n_fs):
            if fses[j].is_retired() == True:
                continue
            # reuse
            #trace = traces[j % n_sbd]
            trace = traces[j % len(traces)]
            fs = fses[j]
#            if i % 10 == 0:
#           async write for video
#           sync write for historian
#            if fs.timer % 5 == 0:
            fs.write(trace[i % len(trace)])
                #fs.write(0)
            fs.tick()
        # every 500 ticks
        if i % 500 == 0:
            retire()

# initialize file trace for video analytics
def init_video_analytics_trace(sample_size):
    kde = init_kde('bus')
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
    #samples.append(sample * append_size)
    return (sample * append_size)

def init_rosbag_trace(sample_size):
    trace_file = '/home/liwei/Documents/research/enigma_logs/rosbag/test.log'
    f = open(trace_file, 'r')
    trace_lib = []
    sample = []
    for line in f:
        trace_lib.append(int(line.split(',')[-1]))
    # for i in range(sample_size):
    # for i in range(len(trace_lib)):
    for i in range(50):
        sample.append(random.choice(trace_lib))
        #sample.append(trace_lib[i])
    return sample


def init_file_trace(n_traces, app):
    funcs = {
            app.VIDEO: init_video_analytics_trace,
            app.ROSBAG: init_rosbag_trace
            }
    trace_init_one = funcs[app]
    samples.clear()
    for i in range(n_traces):
        sample = trace_init_one(sample_size)
        samples.append(sample)
        print(samples[i])
    return samples

def init_genesis_fs(n_sbd):
    s1.clear()
    s2.clear()
    gens.clear()
    fses.clear()
    for i in range(n_sbd):
        _fs = fs(timeout, i, plt)
        # genesis fses
        _fs.set_parent(i)
        if 0 not in gens.keys():
            gens[0] = [_fs]
        else:
            gens[0].append(_fs)
        fses.append(_fs)
        # init with itself
        s1.append(set([i]))
        # empty set
        s2.append(set())
    for i in range(max_gen):
        rename_ts[i] = {}
    return fses


if __name__ == '__main__':

    fig, ax = plt.subplots()
    #ax.xaxis.set_ticks(np.arange(0, sample_size + 20, 10))
    #ax.yaxis.set_ticks(np.arange(0, n_sbd , 1))
    #ax.yaxis.set_ticks(np.arange(0, 50, 1))
    #ax.yaxis.grid(color='k')

    #traces = init_file_trace(trace_count, app.VIDEO)
    it = 0
    while it < 1000:

        rename_count = 0
        fork_count = 0
        fses = init_genesis_fs(n_sbd)
        traces = init_file_trace(trace_count, app.ROSBAG)
        disk_sim(sample_size, traces, fses, plt)

        #print("rename:", rename_ts)
        print("iter = ", it)
        print("rename count:", rename_count)
        print("fork count:", fork_count)
        if len(history) > 1:
            print("dumping history of lineage 0....")
            print(history)
        def process_history(_history):
            # backward tracking
            _all = set()
            p = []
            p.append(1)
            #for i in range(len(_history)-1, -1,  -1):
            for i in range(len(_history)):
                one = _history[i]
                _all = _all.union(one)
                if actual_lineage not in _all:
                    p.append(1)
                else:
                    p.append(1/len(_all))
            print("P = ", p)
            return p
        p = process_history(history)
        it += 1
        if len(p) > 1:
            break
    #print(ts_global)

    ax.plot(np.arange(len(p)), p)
    plt.xlim(0, len(p))
    plt.show()
    #plt.show()
    # for interactive html
    #mpld3.save_html(fig, 'disk_sim.html')
    #mpld3.show()
