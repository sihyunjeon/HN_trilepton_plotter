#!/bin/bash
for i in 3.0 4.0 5.0
do
  for j in 0.2 0.3 0.4 0.6 0.8 1.0
  do
    root -l -b -q "fake_calculator_2016.C($i, $j)"
  done
done
