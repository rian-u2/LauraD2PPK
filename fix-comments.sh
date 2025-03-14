#!/bin/bash

# Copyright 2023 University of Warwick
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

if [ $# -ne 1 ]
then
    echo "Usage: $0 <filename>"
    exit 1
fi

filename=$1

sed -i -e 's/\t/    /g' $filename
sed -i -e 's/[[:space:]]\+$//' $filename
sed -i -e 's%\/param %\\param %' $filename
sed -i -e 's%\/return %\\return %' $filename
python3 fix-comments.py $filename
if [ -e $filename.new ]
then
    mv $filename.new $filename
fi

