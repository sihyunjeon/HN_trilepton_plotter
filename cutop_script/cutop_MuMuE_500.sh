cd /share_home/shjeon/HN_trilepton_plotter/
source /share_home/shjeon/HN_trilepton_plotter/setup.sh
source /share_home/shjeon/HN_trilepton_plotter/cmssetup.sh
root -l -b -q '/share_home/shjeon/HN_trilepton_plotter/src/run_cutop.C(500)' &> output/HN_SSSF_MuMuE_500.txt