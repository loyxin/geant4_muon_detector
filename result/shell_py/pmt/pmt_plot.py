#!/usr/bin/python
#coding=utf8
"""
# Author: loyxin
# Created Time : 2017-10-17 17:45:41

# File Name: pmt_plot.py
# Description:

"""
import csv
import matplotlib.pyplot as plt

reader = csv.reader(open("pmt.csv"))

time = range(250,10050,100)

count = [0 for x in range(0, 98)]
for row in reader:
    for index in range(0,98):
        count[index]+=int(row[index])

plt.plot(time,count)
plt.show()