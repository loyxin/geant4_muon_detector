#!/usr/bin/python
#coding=utf8
"""
# Author: loyxin
# Created Time : 2017-09-01 00:22:28

# File Name: pmt.py
# Description:

"""
import csv
import math

reader = csv.reader(open("muon_nt_pmt.csv"))

csvfile = open('pmt_result.csv','w')
write = csv.writer(csvfile)

flag = 0
muontime = []
decaytime = []
line = []
# decay daverage time, fangcha,
# decay guangzi number
# muon time fangcha
# muon guangzi number
# event id
decayphotonum = 0
muonphotonum = 0


def pinjun_fangcha(list):
    if len(list) == 0:
        return [0,0]
    count = 0
    one = 0.0
    two = 0.0
    for item in list:
        count += 1
        one += item
        two += item**2
    one /= count
    two = math.sqrt(abs(two/count - one**2))
    return [one,two];


for row in reader:
    if len(row) < 2:
        continue
    temp = int(row[3])
    if temp == flag:
        if float(row[1]) < 100.0:
            muontime.append(float(row[1]))
            muonphotonum +=1
        else:
            decayphotonum += 1
            decaytime.append(float(row[1]))
    else:
        flag += 1
        temp = pinjun_fangcha(decaytime)
        line.append(temp[0])
        line.append(temp[1])
        line.append(decayphotonum)
        decaytime =[]
        decayphotonum = 0
        temp = pinjun_fangcha(muontime)
        line.append(temp[0])
        line.append(temp[1])
        line.append(muonphotonum)
        muontime = []
        muonphotonum =0
        line.append(flag)
        write.writerow(line)
        line = []

temp = pinjun_fangcha(decaytime)
line.append(temp[0])
line.append(temp[1])
line.append(decayphotonum)
temp = pinjun_fangcha(muontime)
line.append(temp[0])
line.append(temp[1])
line.append(muonphotonum)
line.append(flag+1)
write.writerow(line)
