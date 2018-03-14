#!/bin/bash

g++ -o drive testing.cpp ../main/*.cpp

echo '-------------------------------------------------'
echo '#> TEST 1 RESULTS'
python ../utilities/printer.py testlogs/test4.log | ./drive
echo '-------------------------------------------------'