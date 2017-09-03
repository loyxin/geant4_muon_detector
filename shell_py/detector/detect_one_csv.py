#!/usr/bin/python
#coding=utf8
"""
# Author: loyxin
# Created Time : 2017-09-01 15:28:41

# File Name: detect_one_csv.py
# Description:

"""
import csv
import os
import sys

reader = csv.reader(open("detect_averge_variance.csv"))

for row in reader:
    for item in row:
        print(item+",", end=" ")
print(os.path.split(os.getcwd())[-1])
