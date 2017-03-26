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

  hist_for_error = new TH1D("hist_for_error", "", 1, 0., 1.);
  hist_for_error_up = new TH1D("hist_for_error_up", "", 1, 0., 1.);
  
  for(Long64_t jentry=0; jentry<nentries;jentry++) {
    GetEntry(jentry);
    bool pass = true;
    double this_weight = 1.;

    if(!isSearchRegion()) continue;

    if(SearchRegion=="Preselection"){
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
        if( ! (PFMET > cut_PFMET) ) continue;
        //if( ! (W_sec_highmass_mass < cut_W_sec_mass) ) continue;
      }
    }
    
    n_weighted += weight;
    n_unweighted++;

    hist_for_error->Fill(0. ,weight);
    hist_for_error_up->Fill(0., weight+weight_err);

    
  }
  
}

Double_t cutop::HN_mass_by_signalclass(){
  
  if(signalclass==1) return HN_1_mass;
  else if(signalclass==2) return HN_2_mass;
  else if(signalclass==3) return HN_3_mass;
  else return HN_4_mass;
  
}

bool cutop::isSearchRegion(){

  bool pass = true;

  if(SearchRegion=="Preselection"){
    if(isPreselection==0) pass = false;
  }
  else if(SearchRegion=="WZ"){
    if(isWZ==0) pass = false;
  }
  else if(SearchRegion=="ZJets"){
    if(isZJets==0) pass = false;
  }
  else{

  }

  return pass;

}









