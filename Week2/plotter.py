import sys
import numpy as np
import matplotlib.pyplot as plt

# open the text file, assign it to a variable named data

# we need to parse this data back into an array named "myx"

with open('myx_data.txt') as f:
    myx_init = list(f)

myx = []
for list_element in myx_init:
	myx.append(float(list_element[:-1]))

#print(myx)

n, bins, patches = plt.hist(myx, 50, density=True, facecolor='b', alpha=0.75)

# plot formating options
plt.xlabel('x')
plt.ylabel('Probability')
plt.title('Uniform random number')
plt.grid(True)

# show figure (program only ends once closed
plt.show()
