import os

lumi = 27200.

import csv
from urllib import urlopen

dbs_url = "https://docs.google.com/spreadsheets/d/1aUoEq40MjpZ4LpcEoxXdd9-prrDmJkWWgeKPLPsmBhk/pub?gid=0&single=true&output=csv"
xsec_url = "https://docs.google.com/spreadsheets/d/1aUoEq40MjpZ4LpcEoxXdd9-prrDmJkWWgeKPLPsmBhk/pub?gid=753464804&single=true&output=csv"

masses = [5, 10, 20, 30, 40, 50, 60, 70, 90, 100, 150, 200, 300, 400, 500, 700, 1000]

channel = "MajoranaNeutrinoToMuMuMu"

for mass in masses:

  ## dataset name of MiniAOD ##
  dataset = ""
  lines_dbs = csv.reader(urlopen(dbs_url).readlines())
  for row in lines_dbs:
    if row[0] == channel+"_M-"+str(mass):
      dataset = row[4]
      break

  ## xsec ##
  xsec = ""
  err = ""
  lines_xsec = csv.reader(urlopen(xsec_url).readlines())
  for row in lines_xsec:
    if row[0] == channel+"_M-"+str(mass):
      xsec = row[1]
      err = row[2]
      break

  dataset = dataset.replace("_","\_")

  efflumi = 100000./float(xsec)

  print '$'+str(mass)+'$\t& {\\tt '+dataset+'}\t& $'+xsec+' \\pm '+err+'$\t& $'+str(int(efflumi))+'$ \\\\'
