wd=`pwd`
export VO_CMS_SW_DIR=/cvmfs/cms.cern.ch
export SCRAM_ARCH=slc6_amd64_gcc530
source $VO_CMS_SW_DIR/cmsset_default.sh
cd /data4/Users/shjeon/cmssw/CMSSW_8_0_20/src/
cmsenv
cd $wd

