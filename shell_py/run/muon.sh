#!/bin/bash
#########################################################################
# File Name: muon.sh
# Author: loyxin
# mail: rafrozenluoxin@gmail.com
# Created Time: 2017-08-27 11:31:09
#########################################################################
cat $1 | while read line
do
    if [[ $line == /gun/energy*  ]];then
        line="/gun/energy "$2" GeV" 
    fi
    echo $line
done

