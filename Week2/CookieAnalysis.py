#! /usr/bin/env python

# imports of external packages to use in our code
import sys
import math
import numpy as np
import matplotlib.pyplot as plt

# import our Random class from python/Random.py file
import MySort as mys

# main function for our CookieAnalysis Python code
if __name__ == "__main__":
   
    haveInput = False

    for i in range(1,len(sys.argv)):
        if sys.argv[i] == '-h' or sys.argv[i] == '--help':
            continue

        InputFile = sys.argv[i]
        haveInput = True
    
    if '-h' in sys.argv or '--help' in sys.argv or not haveInput:
        print ("Usage: %s [options] [input file]" % sys.argv[0])
        print ("  options:")
        print ("   --help(-h)          print options")
        print
        sys.exit(1)
    
    Nmeas = 1
    times = []
    times_avg = []

    need_rate = True
    
    with open(InputFile) as ifile:
        for line in ifile:
            if need_rate:
                need_rate = False
                rate = float(line)
                continue
            
            lineVals = line.split()
            Nmeas = len(lineVals)
            t_avg = 0
            for v in lineVals:
                t_avg += float(v)
                times.append(float(v))

            t_avg /= Nmeas
            times_avg.append(t_avg)

    Sorter = mys.MySort()

    times = Sorter.DefaultSort(times)
    times_avg = Sorter.DefaultSort(times_avg)
    # try some other methods! see how long they take
    # times_avg = Sorter.BubbleSort(times_avg)
    # times_avg = Sorter.InsertionSort(times_avg)
    # times_avg = Sorter.QuickSort(times_avg)
#print(times)
	# my code for calculating quantiles from our sorted data array times[]
q1x = int(len(times)/4)
q2x = 2*q1x
q3x = 3*q1x
q4x = 4*q1x
#print(q1x)
q4 = times[q1x]
q3 = times[q2x]
q2 = times[q3x]
q1 = times[q4x]
print("quantile 1 = " + str(q1))
print("quantile 2 = " + str(q2))
print("quantile 3 = " + str(q3))
print("quantile 4 = " + str(q4))

    # ADD YOUR CODE TO PLOT times AND times_avg HERE

n, bins, patches = plt.hist(times, 50, density=True, facecolor='r', alpha=0.75)

# plot formating options
plt.xlabel('Time')
plt.ylabel('Cookies')
plt.title('Cookies existance versus time')
plt.grid(True)

# show figure (program only ends once closed
plt.show()
