#!/bin/bash
for pin in 0 1 2 3; do
gpio mode $pin out
gpio write $pin 0
done
