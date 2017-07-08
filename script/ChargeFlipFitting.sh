#!/bin/bash

echo "Which region? 1:global 2:BB 3:EE 4:BE 5:JETS1"
read -p 'Enter region : ' region


if [ "$region" == "1" ]
  then  root -l 'src/ChargeFlipZFitting.C("_global")'
fi

if [ "$region" == "2" ]
  then  root -l 'src/ChargeFlipZFitting.C("_BB")'
fi

if [ "$region" == "3" ]
  then  root -l 'src/ChargeFlipZFitting.C("_EE")'
fi

if [ "$region" == "4" ]
  then  root -l 'src/ChargeFlipZFitting.C("_BE")'
fi

if [ "$region" == "5" ]
  then  root -l 'src/ChargeFlipZFitting.C("_JETS1")'
fi
