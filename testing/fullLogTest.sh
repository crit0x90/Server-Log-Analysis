#!/bin/bash

g++ -o drive ../main/*.cpp -std=c++11

echo '-------------------------------------------------'
echo '#> LOG1 TEST RESULTS'
python ../utilities/printer.py testlogs/test1.log | ./drive
echo '#> LOG1 TEST COMPLETE'
echo '-------------------------------------------------'

sleep 2s

echo '-------------------------------------------------'
echo '#> FULL LOG TEST RESULTS'
python ../utilities/printer.py ../input/input.log | ./drive
echo '#> FULL LOG TEST COMPLETE'
echo '-------------------------------------------------'	