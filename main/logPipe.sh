#!/bin/sh
#this script pipes the data that is being written to the log 
#file to the line parser in real time.

./drive | tail -f /fullpathoffile 