#!/bin/bash
#########################################################################
# File Name: all.sh
# Author: loyxin
# mail: rafrozenluoxin@gmail.com
# Created Time: 2017-10-07 00:26:27
#########################################################################
cp ./result/shell_py/detector/*.py ./result/shell_py/detector/*.sh ./result/shell_py/pmt/*.py ./result/shell_py/pmt/*.sh ./data/GeV

a=$1
b=$2
c=$3

cd ./data/GeV
./detect.sh $1 $2 $3
./detect_one_csv.sh
./pmt.sh
./pmt_cal.sh
cd ../../
rm ./data/GeV/*.sh ./data/GeV/*.py 
