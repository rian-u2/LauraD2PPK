#!/bin/bash

if [ $# -lt 1 ]
then
    echo "Usage: $0 <nExpt> [firstExpt = 0] [numSlaves = 2]"
    exit 1
fi

nexpt=$1
firstexpt=0
numslaves=2

if [ $# -gt 1 ]
then
    firstexpt=$2
    if [ $# -gt 2 ]
    then
        numslaves=$3
    fi
fi

# Do whatever you need to do to setup your ROOT environment


./Master $nexpt $firstexpt $numslaves > master-log.out 2>&1 &
sleep 5

port=`tail -1 master-log.out | awk '{print $NF}'`

./Slave fit DD 0 $port > slave-dd-log.out 2>&1 &
sleep 1
./Slave fit LL 0 $port > slave-ll-log.out 2>&1

