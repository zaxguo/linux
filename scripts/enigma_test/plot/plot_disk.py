import numpy as np
import numpy.random
import matplotlib.pyplot as plt
import seaborn as sns


f = open('./emu_disk.dump', 'r')
y = []
prev = -1
for line in f:
    tmp = line.split(',')
    curr = int(tmp[-1])
    y.append(curr)
    # 2 consecutive 0 marks the end
    if prev == 0 and curr == 0:
        print("emu disk consumes ", tmp[0], " phys blocks")
        break
    else:
        prev = curr

fig, ax = plt.subplots()
y = np.asarray(y)
#colormap = sns.color_palette("Greens")
colormap = sns.color_palette("RdYlGn_r", as_cmap=True)
sns.heatmap([y], cmap=colormap)
plt.show()
