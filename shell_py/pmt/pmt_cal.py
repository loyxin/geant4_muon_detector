#!/usr/bin/python
#coding=utf8
"""
# Author: loyxin
# Created Time : 2017-09-03 10:06:09

# File Name: pmt_cal.py
# Description:

"""

import csv


reader = csv.reader(open("pmt_result.csv"))

count = [0 for x in range(0, 98)]
for row in reader:

    if float(row[0]) < 200.0:
        continue
    index = int((float(row[0])-200.0)/100.0)
    if index > 97 or index < 0:
        continue
    count[index] += 1

for item in count:
    print(str(item)+",", end=" ")
print()
