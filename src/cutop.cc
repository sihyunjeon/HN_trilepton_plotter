#define cutop_cxx
#include "cutop.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void cutop::Loop()
{
  
  Long64_t nentries = fChain->GetEntriesFast();
  
  n_weighted = 0.;
  n_unweighted = 0;
  
  for(Long64_t jentry=0; jentry<nentries;jentry++) {
    GetEntry(jentry);
    bool pass = true;
    double this_weight = 1.;

    if(signalclass==1 || signalclass==2){
      if( ! (first_pt < cut_first_pt) ) continue;
      if( ! (second_pt < cut_second_pt) ) continue;
      if( ! (third_pt < cut_third_pt) ) continue;
      if( ! (W_pri_lowmass_mass < cut_W_pri_mass) ) continue;
    }
    else{
      if( ! (first_pt > cut_first_pt) ) continue;
      if( ! (second_pt > cut_second_pt) ) continue;
      if( ! (third_pt > cut_third_pt) ) continue;
      if( ! (W_pri_highmass_mass > cut_W_pri_mass) ) continue;
      if( ! (W_sec_highmass_mass < cut_W_sec_mass) ) continue;
    }
    
    //if( ! (HN_mass_by_signalclass() > min_HN_mass) ) continue;
    
    n_weighted += weight;
    n_unweighted++;
    
  }
  
}

Double_t cutop::HN_mass_by_signalclass(){
  
  if(signalclass==1) return HN_1_mass;
  else if(signalclass==2) return HN_2_mass;
  else if(signalclass==3) return HN_3_mass;
  else return HN_4_mass;
  
}
