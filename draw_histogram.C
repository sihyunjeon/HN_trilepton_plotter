#include "TFile.h"
#include "TDirectory.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TString.h"
#include "THStack.h"
#include "TLegend.h"
#include "TStyle.h"
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class trilepton_mumumu{
public:
  // constructors
  trilepton_mumumu();
  ~trilepton_mumumu();

  // functions
  int n_rebin(TString cut, TString var);
  double y_max(TString cut, TString var);
  void draw_hist();

  // variables
  TString filename_prefix, filename_suffix;
  vector<TString> histname_prefix, bkg, histname, x_title;
  vector<Color_t> fillcolors;
  TFile *outputfile;

};

trilepton_mumumu::trilepton_mumumu(){

  TH1::SetDefaultSumw2(true);
  TH1::AddDirectory(kFALSE);
  gStyle->SetOptStat(0);
  filename_prefix = "./rootfiles/trilepton_mumumu_SK";
  filename_suffix = "_dilep_catv7-4-5.root";
  histname_prefix = {"cut0_", "cutdR_", "cutdR_cutW_"};
  bkg = {
    "DY10to50", "DY50plus",
    "WJets", "WZ", "ZZ", "WW",
    "singletop_tbar", "singletop_t", "singletop_tbarW", "singletop_tW",
    "TTJets_MG5", "ttWJetsToLNu", "ttWJetsToQQ", "ttZToLLNuNu", "ttZToQQ"
  };
  histname = {"HN_mass", "W_on_shell_mass", "deltaR_OS_min", "gamma_star_mass", "n_jet", "z_candidate_mass"};
  x_title = {"m(#mu#mu#nu) [GeV]", "m(#mu#mu#mu#nu) [GeV]", "#DeltaR(OS)_{min}", "m(#mu+#mu-) [GeV]", "# of jets", "m(#mu+#mu-) [GeV]"};
  fillcolors = {
    kAzure+8, kAzure+8,
    kGreen, kGreen, kGreen, kGreen,
    kRed, kRed, kRed, kRed,
    kYellow, kYellow, kYellow, kYellow, kYellow
  };

  outputfile = new TFile("./plots/hists.root", "RECREATE");

}

trilepton_mumumu::~trilepton_mumumu(){



}

void trilepton_mumumu::draw_hist(){
  
  vector<int> MCsector_first_index = {0, 2, 6, 10};
  vector<TString> MCsector_name = {"DY", "VV", "t", "tt"};
  TLegend* lg = new TLegend(0.9, 0.7, 1.0, 0.9);
  
  for(int i_cut = 0; i_cut < (int)histname_prefix.size(); i_cut++){
    outputfile->mkdir(histname_prefix[i_cut]);
    cout << "############## Writing in Directory " << histname_prefix[i_cut] << " ##############" << endl;
    for(int i_var = 0; i_var < (int)histname.size(); i_var++){
      TH1F* hist_data = NULL;
      TH1F* MC_stacked_err = NULL;
      THStack* MC_stacked = new THStack("MC_stacked", "");
      
      for(int i_file = 0; i_file < 1+(int)bkg.size(); i_file++){
        TString filepath, sample;
        if(i_file==0){
          filepath = "./rootfiles/trilepton_mumumu_data_catv7-4-5.root";
          sample = "data";
        }
        else{
          filepath = filename_prefix+bkg[i_file-1]+filename_suffix; // i_file = 1 부터 bkg
          sample = bkg[i_file-1];
        }
        //cout << "sampe = " << sample << endl;
        TFile* file = new TFile(filepath);
        TH1F* hist_temp = (TH1F*)file->Get(histname_prefix[i_cut]+histname[i_var]+"_PU");
        
        if(!hist_temp){
          cout << sample << " is empty!" << endl;
          continue;
        }
        hist_temp->Rebin( n_rebin(histname_prefix[i_cut], histname[i_var]) );
        
        if(i_file == 0){ // data
          hist_data = (TH1F*)hist_temp->Clone();
          int n_bins = hist_data->GetXaxis()->GetNbins();
          MC_stacked_err = new TH1F("MC_stacked_err", "",
                                    n_bins,
                                    hist_data->GetXaxis()->GetBinLowEdge(1),
                                    hist_data->GetXaxis()->GetBinUpEdge(n_bins));
        }
        else{ // bkg -> stack
          hist_temp->SetFillColor(fillcolors[i_file-1]);
          hist_temp->SetLineColor(fillcolors[i_file-1]);
          MC_stacked->Add(hist_temp);
          MC_stacked_err->Add(hist_temp);
        }
        
        file->Close();
        
        if(i_cut==0 && i_var==0){ // fill legend only for the first variable
          for(int i = 0; i < (int)MCsector_first_index.size(); i++){
            if(i_file-1 == MCsector_first_index[i]) lg->AddEntry(hist_temp, MCsector_name[i], "f");
            
          }
        }
      }
      
      TCanvas* c1 = new TCanvas(histname[i_var], "", 800, 600);
      c1->cd();
      MC_stacked->Draw("hist");
      MC_stacked->SetMaximum(y_max(histname_prefix[i_cut], histname[i_var]));
      MC_stacked->GetXaxis()->SetTitle(x_title[i_var]);
      //if(histname[i_var] == "z_candidate_mass") MC_stacked->GetXaxis()->SetRangeUser(70, 110);
      MC_stacked->GetYaxis()->SetTitle("Events");
      hist_data->Draw("PE1same");
      
      MC_stacked_err->SetMarkerColorAlpha(kAzure-9, 0);
      MC_stacked_err->SetFillStyle(3004);
      MC_stacked_err->SetFillColor(kBlue);
      MC_stacked_err->Draw("sameE2");
      
      lg->Draw();
      c1->SaveAs("./plots/"+histname_prefix[i_cut]+histname[i_var]+".png");
      outputfile->cd(histname_prefix[i_cut]);
      c1->Write();
      delete c1;
      
    }
  }
  
  
  outputfile->Close();
  
}

int trilepton_mumumu::n_rebin(TString cut, TString var){
  if(cut == "cut0_"){
    if(var == "HN_mass") return 1;
    else if(var == "W_on_shell_mass") return 1;
    else if(var == "deltaR_OS_min") return 1;
    else if(var == "gamma_star_mass") return 1;
    else if(var == "n_jet") return 1;
    else if(var == "z_candidate_mass") return 1;
    else return 1;
  }
  else if(cut == "cutdR_"){
    if(var == "HN_mass") return 1;
    else if(var == "W_on_shell_mass") return 1;
    else if(var == "deltaR_OS_min") return 1;
    else if(var == "gamma_star_mass") return 1;
    else if(var == "n_jet") return 1;
    else if(var == "z_candidate_mass") return 1;
    else return 1;
  }
  else if(cut == "cutdR_cutW_"){
    if(var == "HN_mass") return 1;
    else if(var == "W_on_shell_mass") return 1;
    else if(var == "deltaR_OS_min") return 1;
    else if(var == "gamma_star_mass") return 1;
    else if(var == "n_jet") return 1;
    else if(var == "z_candidate_mass") return 1;
    else return 1;
  }
  else return 1;
}

double trilepton_mumumu::y_max(TString cut, TString var){
  if(cut == "cut0_"){
    if(var == "HN_mass") return 50;
    else if(var == "W_on_shell_mass") return 50;
    else if(var == "deltaR_OS_min") return 80;
    else if(var == "gamma_star_mass") return 50;
    else if(var == "n_jet") return 300;
    else if(var == "z_candidate_mass") return 50;
    else return 1;
  }
  else if(cut == "cutdR_"){
    if(var == "HN_mass") return 50;
    else if(var == "W_on_shell_mass") return 50;
    else if(var == "deltaR_OS_min") return 40;
    else if(var == "gamma_star_mass") return 30;
    else if(var == "n_jet") return 250;
    else if(var == "z_candidate_mass") return 30;
    else return 1;
  }
  else if(cut == "cutdR_cutW_"){
    if(var == "HN_mass") return 30;
    else if(var == "W_on_shell_mass") return 35;
    else if(var == "deltaR_OS_min") return 15;
    else if(var == "gamma_star_mass") return 15;
    else if(var == "n_jet") return 40;
    else if(var == "z_candidate_mass") return 15;
    else return 1;
  }
  else return 1;
}












