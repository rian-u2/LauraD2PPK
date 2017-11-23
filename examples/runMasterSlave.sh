#!/bin/bash

if [ $# -lt 1 ]
then
    echo "Usage: $0 <nExpt> [firstExpt = 0]"
    exit 1
fi

nexpt=$1
firstexpt=0
numslaves=2

if [ $# -gt 1 ]
then
    firstexpt=$2
fi

# Do whatever you need to do to setup your ROOT environment



# Generate the toy MC
if [ ! -e gen-DD-Slave.root ]
then
    echo "Generating MC for DD category"
    ./Slave gen DD $nexpt $firstexpt > gen-log-DD.out 2>&1
fi
if [ ! -e gen-LL-Slave.root ]
then
    echo "Generating MC for LL category"
    ./Slave gen LL $nexpt $firstexpt > gen-log-LL.out 2>&1
fi

# Do the simultaneous fit
for ifit in `seq 0 19`
do
    echo "Running fit $ifit"

    ./Master $ifit $nexpt $firstexpt $numslaves > master-log-$ifit.out 2>&1 &
    sleep 5

    NUMOFLINES=$(wc -l < "master-log-$ifit.out")
    while [ $NUMOFLINES -lt 1 ]
    do
        sleep 5
        NUMOFLINES=$(wc -l < "master-log-$ifit.out")
    done

    port=`tail -1 master-log-$ifit.out | awk '{print $NF}'`

    ./Slave fit DD $ifit $port localhost > slave-dd-log-$ifit.out 2>&1 &
    sleep 1
    ./Slave fit LL $ifit $port localhost > slave-ll-log-$ifit.out 2>&1
done

# Extract the best fit
echo "Extracting the best fit results"

ls fitDD*.root > input-list-DD.txt
ls fitLL*.root > input-list-LL.txt
ls master-ntuple-*.root > input-list-master.txt

./ResultsExtractorMain $nexpt input-list-DD.txt best-fits-DD.root > resultsextractor-DD.out 2>&1
./ResultsExtractorMain $nexpt input-list-LL.txt best-fits-LL.root > resultsextractor-LL.out 2>&1
./ResultsExtractorMain $nexpt input-list-master.txt best-fits-master.root > resultsextractor-master.out 2>&1



