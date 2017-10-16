#!/bin/bash
#########################################################################
# File Name: test1.sh
# Author: loyxin
# mail: rafrozenluoxin@gmail.com
# Created Time: 2017-08-27 22:49:17
#########################################################################

for var in 0.01 0.011 0.012 0.013 0.014 0.015 0.016 0.017 0.018 0.019 0.02 0.021 \
0.022 0.023 0.024 0.025 0.026 0.027 0.028 0.029 0.03 0.031 0.032 \
0.033 0.034 0.035 0.036 0.037 0.038 0.039 0.04 0.041 0.042 0.043 
do
    ./muon.sh macro/run.mac $var > macro/new.mac
    ./muon macro/new.mac
    mkdir data
    cd data
    mkdir GeV
    cd GeV
    mkdir $var
    cd ../../
    mv *.csv ./data/GeV/$var
done
