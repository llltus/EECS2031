#!/bin/bash
n="$1"
for i in {0..3}; do
let "m=n>>i"
let "k=m&1"
if [ $k == 1 ]
then
gpio toggle $i
fi
done
