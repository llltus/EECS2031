#!/bin/bash
for pin in 0 1 2 3 4 5; do
if [ $pin == 5 ]; then
gpio mode $pin in
gpio mode $pin up
else
gpio mode $pin out
gpio write $pin 0
fi
done
