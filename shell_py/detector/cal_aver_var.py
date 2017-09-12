#!/usr/bin/python
#coding=utf8

import csv
import math
with open('detect_result.csv', 'r+') as csvfile:
    reader = csv.reader(csvfile)
    # energy 0 , decay length 1, energy /mm 2, decay event number 3
    one = [0.0, 0.0, 0.0, 0]
    # 能量方差，衰变长度方差，energy /mm 方差
    two = [0.0, 0.0, 0.0]
    count = -1
    eventnum = 0
    for column in reader:
        if count == -1:
            count =0
            continue
        if int(column[2]) == 1:
            if float(column[1]) > 0:
                length = 25.0 - float(column[1])
                one[1] += length
                two[1] += length**2
            else:
                length = 20.0-5.0-float(column[1])
                one[1] += length
                two[1] += length**2
            eventnum += 1
        else:
            length = 40.0
            one[1] += length
            two[1] += length**2

        one[0] += float(column[0])
        two[0] += float(column[0])**2
        dp = float(column[0]) / length
        one[2] += dp
        two[2] += dp**2
        count += 1


    i = 0
    while i < 3:
        one[i] = one[i]/count
        two[i] = math.sqrt(abs(two[i]/count - one[i]**2))
        i = i + 1
    one[3] = eventnum
csvfile = open('detect_averge_variance.csv', 'w')
write = csv.writer(csvfile)
write.writerow(one)
write.writerow(two)
