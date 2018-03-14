#!/bin/bash

g++ -o drive testing.cpp ../main/*.cpp

echo '-------------------------------------------------'
echo '#> TEST RESULTS'
python ../utilities/printer.py ../input/input.log | ./drive
echo '#> TEST COMPLETE'
echo '-------------------------------------------------'