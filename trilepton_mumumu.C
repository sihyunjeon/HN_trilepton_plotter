#include "TFile.h"
#include "TDirectory.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TString.h"
#include "THStack.h"
#include "TLegend.h"
#include "TStyle.h"
#include "canvas_margin.h"
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
  void draw_hist();
  void make_bkglist();
  TString find_MCsector(int index);
  void clear_legend_info();
  void fill_legend(TLegend* lg, TH1F* hist, int index);
  void draw_legend(TLegend* lg);
  int n_rebin(TString cut, TString var);
  double y_max(TString cut, TString var);

  // variables
  TString filename_prefix, filename_suffix;
  vector<TString> histname_prefix, bkglist, samples_to_use, histname, x_title;
  map< TString, vector<TString> > map_sample_string_to_list;
  map< TString, pair<TString, Color_t> > map_sample_string_to_legendinfo;
  vector<int> MCsector_first_index;
  map<TString, bool> MCsector_survive;
  TFile *outputfile;
  vector<TH1F*> hist_for_legend;

  
};

trilepton_mumumu::trilepton_mumumu(){
  
  TH1::SetDefaultSumw2(true);
  TH1::AddDirectory(kFALSE);
  gStyle->SetOptStat(0);
  filename_prefix = "./rootfiles/trilepton_mumumu_SK";
  filename_suffix = "_dilep_catv7-6-3.root";
  histname_prefix = {"cut0_", "cutdR_", "cutdR_cutW_"};
  
  map_sample_string_to_list["DY_MCatNLO"] = {"DY10to50_MCatNLO", "DY50plus_MCatNLO"};
  map_sample_string_to_list["DY_madgraph"] = {"DY50plus_madgraph"};
  map_sample_string_to_list["WJets_MCatNLO"] = {"WJets_MCatNLO"};
  map_sample_string_to_list["VV_excl_MCatNLO"] = {"WZ_lllnu_MCatNLO", "WZ_llqq_MCatNLO", "ZZ_llqq_MCatNLO", "ZZ_llll_MCatNLO"};
  map_sample_string_to_list["VV_excl"] = {"WZ_lllnu_powheg", "WW_llnn_powheg", "ZZ_llnunu_powheg", "ZZ_llll_powheg"};
  map_sample_string_to_list["VV_incl"] = {"WZ_pythia8", "WW_pythia8", "ZZ_pythia8"};
  map_sample_string_to_list["VVV_MCatNLO"] = {"WZZ_MCatNLO"};
  map_sample_string_to_list["t"] = {"singletop_s_MCatNLO", "singletop_tbar_Powheg", "singletop_t_Powheg", "singletop_tbarW_Powheg", "singletop_tW_Powheg"};
  //map_sample_string_to_list["ignore"] = {"ggHtomm_Powheg", "TTG_MCatNLO", "TT_MCatNLO", "TT_MG5", "ttWJetsToLNu_MCatNLO", "ttWJetsToQQ_MCatNLO", "ttZToQQ_MCatNLO", "TT_powheg", "vhf_Htomm_Powheg", "WG_lnuG_madgraph", , , "WW_doublescattering", "WpWp_madgraph", "WpWp_qcd_madgraph", "ZG_llG_MCatNLO", "ttHnobb_Powheg", "ttHtobb_Powheg"};
  
  map_sample_string_to_legendinfo["DY_MCatNLO"] = make_pair("DY", kAzure+8);
  map_sample_string_to_legendinfo["DY_madgraph"] = make_pair("DY", kAzure+8);
  map_sample_string_to_legendinfo["WJets_MCatNLO"] = make_pair("WJets", kOrange);
  map_sample_string_to_legendinfo["VV_excl_MCatNLO"] = make_pair("VV", kGreen);
  map_sample_string_to_legendinfo["VV_excl"] = make_pair("VV", kGreen);
  map_sample_string_to_legendinfo["VV_incl"] = make_pair("VV", kGreen);
  map_sample_string_to_legendinfo["VVV_MCatNLO"] = make_pair("VVV", kYellow);
  map_sample_string_to_legendinfo["t"] = make_pair("top", kRed);
  
  samples_to_use =
  {"DY_MCatNLO", "WJets_MCatNLO", "VV_excl_MCatNLO", "t"};
  //{"DY_madgraph", "WJets_MCatNLO", "VV_excl_MCatNLO", "t"};
  
  
  make_bkglist();
  //for(int i=0; i<(int)bkglist.size(); i++) cout << bkglist[i] << endl;
  
  histname = {"HN_mass", "W_on_shell_mass", "deltaR_OS_min", "gamma_star_mass", "n_jet", "z_candidate_mass"};
  x_title = {"m(#mu#mu#nu) [GeV]", "m(#mu#mu#mu#nu) [GeV]", "#DeltaR(OS)_{min}", "m(#mu+#mu-) [GeV]", "# of jets", "m(#mu+#mu-) [GeV]"};
  
  outputfile = new TFile("./plots/hists.root", "RECREATE");

}

trilepton_mumumu::~trilepton_mumumu(){
  
  
  
}

void trilepton_mumumu::draw_hist(){
  
  for(int i_cut = 0; i_cut < (int)histname_prefix.size(); i_cut++){
    
    outputfile->mkdir(histname_prefix[i_cut]);
    
    cout << "############## Writing in Directory " << histname_prefix[i_cut] << " ##############" << endl;
    
    for(int i_var = 0; i_var < (int)histname.size(); i_var++){
      
      TH1F* hist_data = NULL;
      TH1F* MC_stacked_err = NULL;
      THStack* MC_stacked = new THStack("MC_stacked", "");
      TLegend* lg = new TLegend(0.8, 0.6, 0.97, 0.9);
      clear_legend_info();
      
      for(int i_file = 0; i_file < 1+(int)bkglist.size(); i_file++){
      
        TString filepath, current_sample;
        
        if( i_file != (int)bkglist.size() ){ // bkg
          filepath = filename_prefix+bkglist[i_file]+filename_suffix;
          current_sample = bkglist[i_file];
        }
        else{ // data
          filepath = "./rootfiles/trilepton_mumumu_data_catv7-6-3.root";
          current_sample = "data";
        }
        /* 
        cout
        << "current_sample = " << find_MCsector(i_file) << endl
        << "filepath = " << filepath << endl
        << "current MCsector = " << current_MCsector << endl
        << "color = " << map_sample_string_to_legendinfo[current_MCsector].second << endl << endl;
        */
        TFile* file = new TFile(filepath);
        TH1F* hist_temp = (TH1F*)file->Get(histname_prefix[i_cut]+histname[i_var]+"_PU");
        
        if(!hist_temp){
          cout << current_sample << " is empty!" << endl;
          continue;
        }
        
        TString current_MCsector = find_MCsector(i_file);
        
        hist_temp->Rebin( n_rebin(histname_prefix[i_cut], histname[i_var]) );
        
        if( i_file != (int)bkglist.size() ){ // bkg
          int n_bins = hist_temp->GetXaxis()->GetNbins();
          if(!MC_stacked_err){
            MC_stacked_err = new TH1F("MC_stacked_err", "",
                                      n_bins,
                                      hist_temp->GetXaxis()->GetBinLowEdge(1),
                                      hist_temp->GetXaxis()->GetBinUpEdge(n_bins));
          }
          hist_temp->SetFillColor(map_sample_string_to_legendinfo[current_MCsector].second);
          hist_temp->SetLineColor(map_sample_string_to_legendinfo[current_MCsector].second);
          MC_stacked->Add(hist_temp);
          MC_stacked_err->Add(hist_temp);
        }
        else{ // data
          hist_temp->SetMarkerStyle(3);
          hist_temp->SetMarkerSize(1);
          hist_data = (TH1F*)hist_temp->Clone();
        }
        
        fill_legend(lg, hist_temp, i_file);
        
        file->Close();
        
      } // END loop over samples
      
      TCanvas* c1 = new TCanvas(histname[i_var], "", 800, 600);
      canvas_margin(c1);
      c1->cd();
      MC_stacked->Draw("hist");
      MC_stacked->SetMaximum(y_max(histname_prefix[i_cut], histname[i_var]));
      MC_stacked->GetXaxis()->SetTitle(x_title[i_var]);
      MC_stacked->GetYaxis()->SetTitleOffset(1.2);
      //if(histname[i_var] == "z_candidate_mass") MC_stacked->GetXaxis()->SetRangeUser(70, 110);
      MC_stacked->GetYaxis()->SetTitle("Events");
      hist_data->Draw("PE1same");
      
      MC_stacked_err->SetMarkerColorAlpha(kAzure-9, 0);
      MC_stacked_err->SetFillStyle(3004);
      MC_stacked_err->SetFillColor(kBlue);
      MC_stacked_err->Draw("sameE2");
      
      draw_legend(lg);
      c1->SaveAs("./plots/"+histname_prefix[i_cut]+histname[i_var]+".png");
      outputfile->cd(histname_prefix[i_cut]);
      c1->Write();
      
      //TH1F* hist_data = NULL;
      //TH1F* MC_stacked_err = NULL;
      //THStack* MC_stacked = new THStack("MC_stacked", "");
      
      
      delete c1;
      delete lg;
      
    } // END loop over variables
    

    
  } // END loop over cuts
  
  
  outputfile->Close();
  
}

void trilepton_mumumu::make_bkglist(){
  for(int i=0; i<(int)samples_to_use.size(); i++){
    MCsector_first_index.push_back( (int)bkglist.size() );
    bkglist.insert(bkglist.end(),
                   map_sample_string_to_list[samples_to_use.at(i)].begin(),
                   map_sample_string_to_list[samples_to_use.at(i)].end()
                   );
  }
}

TString trilepton_mumumu::find_MCsector(int index){
  for(int i=0; i<(int)MCsector_first_index.size()-1; i++){
    if(MCsector_first_index.at(i) <= index && index < MCsector_first_index.at(i+1)) return samples_to_use.at(i);
  }
  return *samples_to_use.end();
}

void trilepton_mumumu::clear_legend_info(){
  hist_for_legend.clear();
  MCsector_survive.clear();
  for(int i=0; i<(int)samples_to_use.size(); i++){
    MCsector_survive[samples_to_use.at(i)] = false;
  }

}

void trilepton_mumumu::fill_legend(TLegend* lg, TH1F* hist, int index){
  TString current_MCsector = find_MCsector(index);
  if( !MCsector_survive[current_MCsector] ){
    //cout << "[legend] " << bkglist[index] << " is saved" << endl;
    hist_for_legend.push_back((TH1F*)hist->Clone());
    MCsector_survive[current_MCsector] = true;
  }
  if( index == (int)bkglist.size() ){ // data
    hist_for_legend.push_back((TH1F*)hist->Clone()); // last element of hist_for_legend is data
  }
}

void trilepton_mumumu::draw_legend(TLegend* lg){
  int i_data = (int)hist_for_legend.size()-1;
  lg->AddEntry(hist_for_legend.at(i_data), "data", "p");
  int j=0;
  for(int i=0; i<(int)samples_to_use.size(); i++){
    if(MCsector_survive[samples_to_use.at(i)]){
      //cout << samples_to_use.at(i) << " is saved" << endl;
      lg->AddEntry(hist_for_legend.at(j), map_sample_string_to_legendinfo[samples_to_use.at(i)].first, "f");
      j++;
    }
  }
  lg->SetFillStyle(0);
  lg->SetBorderSize(0);
  lg->Draw();
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
    if(var == "HN_mass") return 150;
    else if(var == "W_on_shell_mass") return 250;
    else if(var == "deltaR_OS_min") return 150;
    else if(var == "gamma_star_mass") return 100;
    else if(var == "n_jet") return 500;
    else if(var == "z_candidate_mass") return 100;
    else return 1;
  }
  else if(cut == "cutdR_"){
    if(var == "HN_mass") return 100;
    else if(var == "W_on_shell_mass") return 70;
    else if(var == "deltaR_OS_min") return 60;
    else if(var == "gamma_star_mass") return 50;
    else if(var == "n_jet") return 400;
    else if(var == "z_candidate_mass") return 100;
    else return 1;
  }
  else if(cut == "cutdR_cutW_"){
    if(var == "HN_mass") return 40;
    else if(var == "W_on_shell_mass") return 40;
    else if(var == "deltaR_OS_min") return 20;
    else if(var == "gamma_star_mass") return 25;
    else if(var == "n_jet") return 50;
    else if(var == "z_candidate_mass") return 20;
    else return 1;
  }
  else return 1;
}












