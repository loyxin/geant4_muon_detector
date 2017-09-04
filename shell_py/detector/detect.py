#!/usr/bin/python
#coding=utf8
"""
# Author: loyxin
# Created Time : 2017-08-27 15:42:49

# File Name: cd.py
# Description:

"""
import csv

reader = csv.reader(open("muon_nt_detector.csv"))

csvfile = open('detect_result.csv', 'w')
write = csv.writer(csvfile)

flag = 0
result = 0.0
position = []
# 第一列 总沉积能量 第二列 离开位置或者衰变位置，第三列 是否衰变 1 为衰变 0 为未衰变
# 第四列 事件 id
line = ['MeV', 'leave position /ns', 'flag whether decay', 'event id']
write.writerow(line)
line = []
for row in reader:
    if len(row) < 2:
        continue
    l = len(row)
    i = 0
    temp = int(row[3])
    if temp == flag:
        result = result + float(row[0])
        position.append(float(row[1]))


    else:
        flag = flag+1
        line.append(result)
        line.append(min(position))
        if float(min(position)) > float(-25.0):
            line.append(1)
        else:
            line.append(0)
        line.append(flag)
        write.writerow(line)
        result = 0.0
        result = float(row[0])
        position = []
        position.append(float(row[1]))
        line = []

line.append(result)
line.append(min(position))
if float(min(position)) > float(-25.0):
    line.append(1)
else:
    line.append(0)#decay event
line.append(flag+1)
write.writerow(line)
