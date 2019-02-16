#!/bin/bash
while :
do
for i in 1 2 4 8; do
./setbits.sh $i
sleep 0.25
./setbits.sh $i
done
for j in 4 2; do
./setbits.sh $j
sleep 0.25
./setbits.sh $j
done
done
