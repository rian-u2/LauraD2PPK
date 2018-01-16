#!/bin/bash

# Copyright 2017 University of Warwick
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Laura++ package authors:
# John Back
# Paul Harrison
# Thomas Latham


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



