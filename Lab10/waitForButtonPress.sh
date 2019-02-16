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
while true ; do
waitButton
waitReleaseButton
done
