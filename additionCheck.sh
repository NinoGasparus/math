#!/bin/bash

x=$1
y=$2

./math.program "$x" "$y" > tmp1
python3 check.py "$x" "$y" > tmp2

sum1=$(sha256sum tmp1 | awk '{print $1}')
sum2=$(sha256sum tmp2 | awk '{print $1}')

if [ "$sum1" = "$sum2" ]; then
  echo "OK"
else
  echo "FAILED"
fi

rm tmp1
rm tmp2

