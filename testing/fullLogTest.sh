#!/bin/bash

g++ -o drive ../main/*.cpp -std=c++11

echo '-------------------------------------------------'
echo '#> TEST RESULTS'
python ../utilities/printer.py testlogs/test1.log | ./drive
echo '#> TEST COMPLETE'
echo '-------------------------------------------------'