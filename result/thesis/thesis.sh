#!/bin/bash
#########################################################################
# File Name: thesis.sh
# Author: loyxin
# mail: rafrozenluoxin@gmail.com
# Created Time: 2017-10-14 15:29:03
#########################################################################

xelatex muon_last.tex
xelatex muon_last.tex
rm *.aux *.log *.out
