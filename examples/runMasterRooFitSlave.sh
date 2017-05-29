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



# Generate the toy MC
#echo "Generating MC"
#./SlaveRooFit gen DD $nexpt $firstexpt > gen-log-DD.out 2>&1
#./SlaveRooFit gen LL $nexpt $firstexpt > gen-log-LL.out 2>&1


# Do the simultaneous fit
./Master 0 $nexpt $firstexpt $numslaves > master-log.out 2>&1 &
sleep 5

port=`tail -1 master-log.out | awk '{print $NF}'`
echo $port

./SlaveRooFit fit DD $port > slave-dd-log.out 2>&1 &
sleep 1
./SlaveRooFit fit LL $port > slave-ll-log.out 2>&1



