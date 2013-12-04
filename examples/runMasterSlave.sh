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
echo "Generating MC"
./Slave gen DD $nexpt $firstexpt > gen-log-DD.out 2>&1
./Slave gen LL $nexpt $firstexpt > gen-log-LL.out 2>&1


# Do the simultaneous fit
for ifit in `seq 0 19`
do
    echo "Running fit $ifit"

    ./Master $ifit $nexpt $firstexpt $numslaves > master-log-$ifit.out 2>&1 &
    sleep 5

    port=`tail -1 master-log-$ifit.out | awk '{print $NF}'`

    ./Slave fit DD $ifit $port > slave-dd-log-$ifit.out 2>&1 &
    sleep 1
    ./Slave fit LL $ifit $port > slave-ll-log-$ifit.out 2>&1
done

# Extract the best fit
echo "Extracting the best fit results"

ls fitDD*.root > input-list-DD.txt
ls fitLL*.root > input-list-LL.txt
ls master-ntuple-*.root > input-list-master.txt

./ResultsExtractorMain $nexpt input-list-DD.txt best-fits-DD.root > resultsextractor-DD.out 2>&1
./ResultsExtractorMain $nexpt input-list-LL.txt best-fits-LL.root > resultsextractor-LL.out 2>&1
./ResultsExtractorMain $nexpt input-list-master.txt best-fits-master.root > resultsextractor-master.out 2>&1



