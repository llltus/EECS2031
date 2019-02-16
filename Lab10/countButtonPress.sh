#!/bin/bash
waitButton ()
{
echo -n "Waiting for button ... "
while [ `gpio read 5` = 1 ]; do
sleep 0.1
done
echo "Got it"
}
waitReleaseButton ()
{
echo -n "Waiting for button to be released ... "
while [ `gpio read 5` = 0 ]; do
sleep 0.1
done
echo "Got it"
}
i=0
while :
do
waitButton
waitReleaseButton
let "i=i+1"
if [ $i -lt 16 ]; then
./setbits.sh $i
fi
if [ $i -ge 16 ]; then
for pin in 0 1 2 3; do
gpio write $pin 0
done
gpio write 4 1
sleep 1
gpio write 4 0
i=0
fi
done
