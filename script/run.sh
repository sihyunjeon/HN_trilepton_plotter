#!/bin/bash
whichRun=$1

if [ $whichRun = "SR" ]; then
  root -l -b -q "src/run_trilepton_mumumu_2016.C(2)"
fi

if [ $whichRun = "CR" ]; then
  if [ -z "$2" ]; then
    root -l -b -q "src/run_trilepton_mumumu_CR_2016.C(1)"
  else
    whichCR=$2
    if [ $whichCR = "dilep" ]; then
      root -l -b -q "src/run_trilepton_mumumu_CR_2016.C(2)"
    fi
  fi
fi

if [ $whichRun = "FR" ]; then
  dXYSig=$2
  RelIso=$3

  if [ $dXYSig = "all" ]; then
		for i in 3.0 4.0 5.0
		do
			for j in 0.2 0.3 0.4 0.6 0.8 1.0
			do
				root -l -b -q "src/fake_calculator_2016.C($i, $j)"
			done
		done
  else
    root -l -b -q "src/fake_calculator_2016.C($dXYSig, $RelIso)" 
  fi
fi

if [ $whichRun = "syst" ]; then
  for mass in 5 10 20 30 40 50 60 70
  do
    root -l -b -q "src/syst_UpDowns.C($mass,true,false)"
  done
  for mass in 90 100 150 200 300 400 500 700 1000
  do
    root -l -b -q "src/syst_UpDowns.C($mass,true,false)"
  done
fi
  
