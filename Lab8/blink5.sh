#!/bin/bash
for i in {1..5}; do
for pin in {0..3}; do
gpio toggle $pin
sleep 1
gpio toggle $pin
sleep 1
done
done

