#!/bin/bash

if [ $# -lt 4 ]
then
    echo "Usage: $0 <mcfile> <mctree> <datafile> <datatree> [outfile=\"p2pTest.dat\"] [seed=0] [nSamples=100] [nPerms=100] [sigma=0.01]"
    exit 1
fi

mcfile=$1
mctree=$2
datafile=$3
datatree=$4
outfile="p2pTest.dat"
seed=0
nSamples=100
nPerms=100
sigma=0.01

if [ $# -gt 4 ]
then
    outfile="$5"
    if [ $# -gt 5 ]
    then
        seed=$6
        if [ $# -gt 6 ]
        then
            nSamples=$7
            if [ $# -gt 7 ]
            then
                nPerms=$8
                if [ $# -gt 8 ]
                then
                    sigma=$9
                fi
            fi
        fi
    fi
fi

if [ -f $outfile ]
then
    echo "File $outfile already exists"
    exit 1
fi

echo $nSamples
for iSample in $(seq 1 $nSamples);
do
  ./point2PointTestSample $mcfile $mctree $datafile $datatree 0 $iSample $nSamples $nPerms $sigma | tail -n1 >> $outfile
  echo "" >> $outfile
  echo $iSample of $nSamples...;
done;
