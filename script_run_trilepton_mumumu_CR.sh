#!/bin/bash

for c in "CR2"
do
  root -l -b -q "run_trilepton_mumumu_CR.cc(0,\"$c\")"
  root -l -b -q "run_trilepton_mumumu_CR.cc(1,\"$c\")"
  root -l -b -q "run_trilepton_mumumu_CR.cc(2,\"$c\")"
  root -l -b -q "run_trilepton_mumumu_CR.cc(3,\"$c\")"
  root -l -b -q "run_trilepton_mumumu_CR.cc(4,\"$c\")"
  root -l -b -q "run_trilepton_mumumu_CR.cc(5,\"$c\")"
  root -l -b -q "run_trilepton_mumumu_CR.cc(6,\"$c\")"
  root -l -b -q "run_trilepton_mumumu_CR.cc(7,\"$c\")"
  root -l -b -q "run_trilepton_mumumu_CR.cc(8,\"$c\")"
done


