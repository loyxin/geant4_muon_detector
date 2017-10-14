#!/bin/bash
#########################################################################
# File Name: thesis.sh
# Author: loyxin
# mail: rafrozenluoxin@gmail.com
# Created Time: 2017-10-14 15:29:03
#########################################################################

xelatex muon.tex
xelatex muon.tex
rm *.aux *.log muon.out
