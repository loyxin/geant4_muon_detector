#!/bin/bash
#########################################################################
# File Name: all.sh
# Author: loyxin
# mail: rafrozenluoxin@gmail.com
# Created Time: 2017-10-07 00:26:27
#########################################################################
for var in dis_3 dis_5 dis_15 dis_20 dis_40 dis_60 dis_80 fir_10 fir_15 fir_25 fir_30 fir_35 fir_40 fir_60 
do
    cd ./$var/data/GeV/
    rm pmt.csv detect_one.csv
    mv ../../../sh/*.sh ../../../sh/*.py ./
    ./pmt.sh
    ./pmt_cal.sh
    cat ./pmt.csv >> ../../../all_pmt.csv
    mv ./*.sh ./*.py ../../../sh/
    cd ../../../
done
