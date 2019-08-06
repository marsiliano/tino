#!/bin/bash

DIR="metrics/history/$(date +%Y%m%d_%H%M%S)/"
echo $DIR
mkdir $DIR

echo $(./countLines.sh) > "${DIR}lines.txt"

./runCppCheck.sh
cp checkout.xml $DIR

./runCoverage.sh
cp coverage/html/index.html $DIR
