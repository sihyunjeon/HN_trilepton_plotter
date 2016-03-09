#include "trilepton_mumumu.h"

trilepton_mumumu::trilepton_mumumu(){
  
  TH1::SetDefaultSumw2(true);
  TH1::AddDirectory(kFALSE);
  gStyle->SetOptStat(0);
  filename_prefix = "./rootfiles/v7-6-3.4/trilepton_mumumu_SK";
  filename_suffix = "_dilep_cat_v7-6-3.root";
  histname_suffix = {"_cut0", "_cutdR", "_cutdR_cutW"};
  
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
  //{"DY_MCatNLO", "WJets_MCatNLO", "VV_excl_MCatNLO", "t"};
  {"DY_MCatNLO", "WJets_MCatNLO", "VV_excl", "t"};
  
  
  make_bkglist();
  cout << "We will use :" << endl;
  for(unsigned int i=0; i<bkglist.size(); i++) cout << " " << bkglist[i] << endl;
  
  histname = {"HN_mass", "W_on_shell_mass", "deltaR_OS_min", "gamma_star_mass", "n_jet", "z_candidate_mass", "h_PFMET", "h_leadingLeptonPt", "h_leadingLeptonEta"};
  x_title = {"m(#mu#mu#nu) [GeV]", "m(#mu#mu#mu#nu) [GeV]", "#DeltaR(OS)_{min}", "m(#mu+#mu-) [GeV]", "# of jets", "m(#mu+#mu-) [GeV]", "PFMET [GeV]", "pT [GeV]", "#eta"};
  
  outputfile = new TFile("./plots/hists.root", "RECREATE");

}

trilepton_mumumu::~trilepton_mumumu(){
  
  
  
}

void trilepton_mumumu::draw_hist(){
  
  for(unsigned int i_cut = 0; i_cut < histname_suffix.size(); i_cut++){
    
    outputfile->mkdir(histname_suffix[i_cut]);
    
    cout << "############## Writing in Directory " << histname_suffix[i_cut] << " ##############" << endl;
    
    for(unsigned int i_var = 0; i_var < histname.size(); i_var++){
      
      TH1F* hist_data = NULL;
      TH1F* MC_stacked_err = NULL;
      THStack* MC_stacked = new THStack("MC_stacked", "");
      TLegend* lg = new TLegend(0.8, 0.6, 0.97, 0.9);
      clear_legend_info();
      
      for(unsigned i_file = 0; i_file < 1+bkglist.size(); i_file++){
      
        TString filepath, current_sample;
        
        if( i_file != bkglist.size() ){ // bkg
          filepath = filename_prefix+bkglist[i_file]+filename_suffix;
          current_sample = bkglist[i_file];
        }
        else{ // data
          filepath = "./rootfiles/v7-6-3.4/trilepton_mumumu_data_cat_v7-6-3.root";
          current_sample = "data";
        }
         
        //cout
        //<< "filepath = " << filepath << endl
        //<< "hisname = " << histname[i_var]+histname_suffix[i_cut]+"_PU" << endl; 
        
        TFile* file = new TFile(filepath);
        TH1F* hist_temp = (TH1F*)file->Get(histname[i_var]+histname_suffix[i_cut]+"_PU");
        
        if(!hist_temp){
          cout << "Empty : " << current_sample << endl;
          continue;
        }
        
        TString current_MCsector = find_MCsector(i_file);
        
        hist_temp->Rebin( n_rebin(histname_suffix[i_cut], histname[i_var]) );
        
        if( i_file != bkglist.size() ){ // bkg
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
      MC_stacked->SetMaximum(y_max(histname_suffix[i_cut], histname[i_var]));
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
      c1->SaveAs("./plots/"+histname[i_var]+histname_suffix[i_cut]+".png");
      outputfile->cd(histname_suffix[i_cut]);
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
  for(unsigned int i=0; i<samples_to_use.size(); i++){
    MCsector_first_index.push_back( bkglist.size() );
    //cout << "[make_bkglist] " << "MCsector_first_index.push_back(" <<  bkglist.size() << ")" << endl;
    bkglist.insert(bkglist.end(),
                   map_sample_string_to_list[samples_to_use.at(i)].begin(),
                   map_sample_string_to_list[samples_to_use.at(i)].end()
                   );
  }
}

TString trilepton_mumumu::find_MCsector(int index){
  for(unsigned int i=0; i<(int)MCsector_first_index.size()-1; i++){
    if(MCsector_first_index.at(i) <= index && index < MCsector_first_index.at(i+1)){
      //cout << "[find_MCsector] " << "("<<MCsector_first_index.at(i)<<","<<MCsector_first_index.at(i+1)<<") => index " << index << ", returned MCsector is " << samples_to_use.at(i) << endl;
      return samples_to_use.at(i);
    }
  }
  //cout << "[find_MCsector] " << "index " << index << ", returned MCsector is " << *samples_to_use.end() << endl;
  return samples_to_use.back();
}

void trilepton_mumumu::clear_legend_info(){
  hist_for_legend.clear();
  MCsector_survive.clear();
  for(int i=0; i<samples_to_use.size(); i++){
    MCsector_survive[samples_to_use.at(i)] = false;
  }

}

void trilepton_mumumu::fill_legend(TLegend* lg, TH1F* hist, int index){
  TString current_MCsector = find_MCsector(index);
  //cout << "[fill_legend] " << "index " << index << ", current_MCsector is " << current_MCsector << endl;
  if( !MCsector_survive[current_MCsector] ){
    //cout << "[fill_legend] " << bkglist[index] << " is saved" << endl;
    hist_for_legend.push_back((TH1F*)hist->Clone());
    MCsector_survive[current_MCsector] = true;
  }
  if( index == (int)bkglist.size() ){ // data
    hist_for_legend.push_back((TH1F*)hist->Clone()); // last element of hist_for_legend is data
  }
}

void trilepton_mumumu::draw_legend(TLegend* lg){
  // Ex
  //                      0    1    2    3
  // samples_to_use   = {"A", "B", "C", "D"}
  // MCsector_survive = { T ,  T ,  F ,  T }
  //
  //                       0    1    2      3 
  // hist_for_legend are {"A", "B", "D", "data"}
  // i_data = 4-1 = 3
  // 
  int i_data = (int)hist_for_legend.size()-1; // last element of hist_for_legend is data
  lg->AddEntry(hist_for_legend.at(i_data), "data", "p");
  int j=0;
  //cout << "[draw_legend] printing MCsector_survive" << endl;
  for(auto it = MCsector_survive.begin(); it != MCsector_survive.end(); ++it){
    //cout << "[draw_legend] " << it->first << " is " << it->second << endl;
  }
  for(unsigned int i=0; i<samples_to_use.size(); i++){
    if(MCsector_survive[samples_to_use.at(i)]){
      //cout << "[draw_legend] " << samples_to_use.at(i) << " is added in legend" << endl;
      lg->AddEntry(hist_for_legend.at(j), map_sample_string_to_legendinfo[samples_to_use.at(i)].first, "f");
      j++;
    }
  }
  lg->SetFillStyle(0);
  lg->SetBorderSize(0);
  lg->Draw();
}

int trilepton_mumumu::n_rebin(TString cut, TString var){
  if(cut == "_cut0"){
    if(var == "HN_mass") return 1;
    else if(var == "W_on_shell_mass") return 1;
    else if(var == "deltaR_OS_min") return 1;
    else if(var == "gamma_star_mass") return 1;
    else if(var == "n_jet") return 1;
    else if(var == "z_candidate_mass") return 1;
    else if(var == "h_PFMET") return 1;
    else if(var == "h_leadingLeptonPt") return 1;
    else if(var == "h_leadingLeptonEta") return 1;
    else return 1;
  }
  else if(cut == "_cutdR"){
    if(var == "HN_mass") return 1;
    else if(var == "W_on_shell_mass") return 1;
    else if(var == "deltaR_OS_min") return 1;
    else if(var == "gamma_star_mass") return 1;
    else if(var == "n_jet") return 1;
    else if(var == "z_candidate_mass") return 1;
    else if(var == "h_PFMET") return 1;
    else if(var == "h_leadingLeptonPt") return 1;
    else if(var == "h_leadingLeptonEta") return 1;
    else return 1;
  }
  else if(cut == "_cutdR_cutW"){
    if(var == "HN_mass") return 1;
    else if(var == "W_on_shell_mass") return 1;
    else if(var == "deltaR_OS_min") return 1;
    else if(var == "gamma_star_mass") return 1;
    else if(var == "n_jet") return 1;
    else if(var == "z_candidate_mass") return 1;
    else if(var == "h_PFMET") return 1;
    else if(var == "h_leadingLeptonPt") return 1;
    else if(var == "h_leadingLeptonEta") return 1;
    else return 1;
  }
  else return 1;
}

double trilepton_mumumu::y_max(TString cut, TString var){
  if(cut == "_cut0"){
    if(var == "HN_mass") return 120;
    else if(var == "W_on_shell_mass") return 150;
    else if(var == "deltaR_OS_min") return 100;
    else if(var == "gamma_star_mass") return 60;
    else if(var == "n_jet") return 400;
    else if(var == "z_candidate_mass") return 70;
    else if(var == "h_PFMET") return 100;
    else if(var == "h_leadingLeptonPt") return 100;
    else if(var == "h_leadingLeptonEta") return 100;
    else return 1;
  }
  else if(cut == "_cutdR"){
    if(var == "HN_mass") return 80;
    else if(var == "W_on_shell_mass") return 50;
    else if(var == "deltaR_OS_min") return 50;
    else if(var == "gamma_star_mass") return 40;
    else if(var == "n_jet") return 300;
    else if(var == "z_candidate_mass") return 70;
    else if(var == "h_PFMET") return 100;
    else if(var == "h_leadingLeptonPt") return 100;
    else if(var == "h_leadingLeptonEta") return 100;
    else return 1;
  }
  else if(cut == "_cutdR_cutW"){
    if(var == "HN_mass") return 30;
    else if(var == "W_on_shell_mass") return 40;
    else if(var == "deltaR_OS_min") return 20;
    else if(var == "gamma_star_mass") return 20;
    else if(var == "n_jet") return 40;
    else if(var == "z_candidate_mass") return 20;
    else if(var == "h_PFMET") return 100;
    else if(var == "h_leadingLeptonPt") return 100;
    else if(var == "h_leadingLeptonEta") return 100;
    else return 1;
  }
  else return 1;
}












