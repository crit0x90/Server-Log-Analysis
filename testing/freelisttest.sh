#!/bin/bash

g++ -o drive testing.cpp ../main/*.cpp

echo '-------------------------------------------------'
echo '#> TEST 1 RESULTS'
python ../utilities/printer.py testlogs/test1.log | ./drive
echo '-------------------------------------------------'

echo '#> TEST 2 RESULTS'
python ../utilities/printer.py testlogs/test2.log | ./drive
echo '-------------------------------------------------'

echo '#> TEST 3 RESULTS'
python ../utilities/printer.py testlogs/test3.log | ./drive
echo '-------------------------------------------------'