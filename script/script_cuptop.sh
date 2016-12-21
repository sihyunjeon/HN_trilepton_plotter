#!/bin/bash
root -l -b -q "run_cutop.cc(40)" &> plots/v8-0-2.9/CutOp/HN40.txt &
root -l -b -q "run_cutop.cc(60)" &> plots/v8-0-2.9/CutOp/HN60.txt &
root -l -b -q "run_cutop.cc(150)" &> plots/v8-0-2.9/CutOp/HN150.txt &
root -l -b -q "run_cutop.cc(700)" &> plots/v8-0-2.9/CutOp/HN700.txt &
