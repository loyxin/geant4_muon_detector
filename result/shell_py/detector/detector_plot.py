#!/usr/bin/python
#coding=utf8
"""
# Author: loyxin
# Created Time : 2017-10-17 17:45:07

# File Name: detector_plot.py
# Description:

"""
import csv
import matplotlib.pyplot as plt

reader = csv.reader(open("detect_one.csv"))

muenerge = []
energe = []
distance = []
en_dis = []
for row in reader:
    energe.append(float(row[0]))
    muenerge.append(float(row[7]))
    distance.append(float(row[1]))
    en_dis.append(float(row[2]))

plt.plot(muenerge, energe)
plt.xlabel('muon energe /GeV')
plt.ylabel('Deposition energy/MeV')
plt.figure()
plt.plot(muenerge, distance)
plt.xlabel('muon energe /GeV')
plt.ylabel('muon Penetration distance/mm')
plt.figure()
plt.plot(muenerge, en_dis)
plt.xlabel('muon energe /GeV')
plt.ylabel('Deposition energy per unit distance/MeV_mm')
plt.show()
