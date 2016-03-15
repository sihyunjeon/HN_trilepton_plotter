#include "trilepton_mumumu.h"

trilepton_mumumu::trilepton_mumumu(){
  
  TH1::SetDefaultSumw2(true);
  TH1::AddDirectory(kFALSE);
  gStyle->SetOptStat(0);
  filename_prefix = "./rootfiles/trilepton_mumumu_SK";
  filename_suffix = "_5_3_14.root";
  histname_suffix = {"_cut0", "_cutdR", "_cutdR_cutW"};
  
  map_sample_string_to_list["DY"] = {"DY10to50", "DY50plus", "Zbb"};
  map_sample_string_to_list["VV"] = {"WZtollln_mg", "WZtollqq_mg", "WZtoqqln_mg", "ZZtollll_mg", "ZZtollnn_mg", "ZZtollqq_mg", "WW_mg"};
  map_sample_string_to_list["others"] = {"Wbb", "topDIL", "TTG", "TTWW", "WWG", "WWW", "WWZ", "WZZ", "ZZZ", "ttZ"};
  map_sample_string_to_list["Higgs"] = {"HtoWW", "ggHtoZZ"};
  map_sample_string_to_list["Wgamma"] = {"Wtollln_new"};
  
  map_sample_string_to_legendinfo["DY"] = make_pair("DY", kAzure+8);
  map_sample_string_to_legendinfo["VV"] = make_pair("VV", kGreen);
  map_sample_string_to_legendinfo["others"] = make_pair("others", kRed-7);
  map_sample_string_to_legendinfo["Higgs"] = make_pair("Higgs", kYellow);
  map_sample_string_to_legendinfo["Wgamma"] = make_pair("W#rightarrowlll#nu", kOrange);
  
  samples_to_use =
  //{"DY_MCatNLO", "WJets_MCatNLO", "VV_excl_MCatNLO", "t"};
  {"DY", "VV", "Higgs", "Wgamma", "others"};
  
  make_bkglist();
  cout << "We will use :" << endl;
  for(unsigned int i=0; i<bkglist.size(); i++) cout << " " << bkglist[i] << endl;
  
  histname = {
    "HN_mass_class1", "HN_mass_class2", "HN_mass_class3", "HN_mass_class4",
    "W_pri_lowmass_mass",
    "deltaR_OS_min", "gamma_star_mass", "n_jet", "z_candidate_mass", "h_PFMET",
    "h_leadingLepton_Pt",
    "h_secondLepton_Pt",
    "h_thirdLepton_Pt",
    "h_leadingLepton_Eta",
    "h_secondLepton_Eta",
    "h_thirdLepton_Eta",
    "h_leadingLepton_LeptonRelIso",
    "h_secondLepton_LeptonRelIso",
    "h_thirdLepton_LeptonRelIso",
    "h_leadingLepton_dXY",
    "h_secondLepton_dXY",
    "h_thirdLepton_dXY",
    "h_leadingLepton_dZ",
    "h_secondLepton_dZ",
    "h_thirdLepton_dZ",
    "h_leadingLepton_GlobalChi2",
    "h_secondLepton_GlobalChi2",
    "h_thirdLepton_GlobalChi2"
  };
  x_title = {
    "m(#mu#mu#nu) [GeV]", "m(#mu#mu#nu) [GeV]", "m(#mu#mu#nu) [GeV]", "m(#mu#mu#nu) [GeV]",
    "m(#mu#mu#mu#nu) [GeV]",
    "#DeltaR(OS)_{min}", "m(#mu+#mu-) [GeV]", "# of jets", "m(#mu+#mu-) [GeV]", "PFMET [GeV]",
    "pT [GeV]",
    "pT [GeV]",
    "pT [GeV]",
    "#eta",
    "#eta",
    "#eta",
    "LepRelIso03",
    "LepRelIso03",
    "LepRelIso03",
    "dXY [cm]",
    "dXY [cm]",
    "dXY [cm]",
    "dZ [cm]",
    "dZ [cm]",
    "dZ [cm]",
    "GlobalChi2",
    "GlobalChi2",
    "GlobalChi2"
  };
  
  signal_mass = {40, 50, 60, 150, 700};
  signal_color = {kRed, kBlack, kBlue, kYellow+3, kViolet};
  
  outputfile = new TFile("./plots/hists.root", "RECREATE");

}

trilepton_mumumu::~trilepton_mumumu(){
  
  
  
}

void trilepton_mumumu::draw_hist(){
  
  for(unsigned int i_cut = 0; i_cut < histname_suffix.size(); i_cut++){
    
    outputfile->mkdir(histname_suffix[i_cut]);
    
    cout << "############## Writing in Directory " << histname_suffix[i_cut] << " ##############" << endl;
    
    for(unsigned int i_var = 0; i_var < histname.size(); i_var++){
    
      if( histname_suffix[i_cut] == "_cutdR_cutW" && ( histname[i_var].Contains("class3") || histname[i_var].Contains("class4") ) ) continue;
         
      cout << "[Drawing " << histname[i_var] << "]" << endl;
      
      TH1F* MC_stacked_err = NULL;
      THStack* MC_stacked = new THStack("MC_stacked", "");
      TH1F* hist_data = NULL;
      vector<TH1F*> hist_signal;
      
      TLegend* lg = new TLegend(0.65, 0.55, 0.97, 0.90);
      clear_legend_info();
      coupling_const.clear();
      
      for(unsigned i_file = 0; i_file < bkglist.size()+signal_mass.size()+1; i_file++){ // +1 for data
      
        TString filepath, current_sample;
        
        if( i_file < bkglist.size() ){ // bkg
          filepath = filename_prefix+bkglist[i_file]+filename_suffix;
          current_sample = bkglist[i_file];
        }
        else if( i_file == bkglist.size() ){ // data for i_file = bkglist.size()
          filepath = "./rootfiles/trilepton_mumumu_data_5_3_14.root";
          current_sample = "data";
        }
        else{ // signal starting from i_file = bkglist.size()+1
          int signal_index = i_file-bkglist.size()-1;
          //cout << "signal_index = " << signal_index << " => mass = " << signal_mass[signal_index] << endl;
          TString string_signal_mass = "HN"+TString::Itoa(signal_mass[signal_index],10)+"_mumumu_new";
          filepath = filename_prefix+string_signal_mass+filename_suffix;
          current_sample = string_signal_mass;
        }
         
        //cout
        //<< "filepath = " << filepath << endl
        //<< "hisname = " << histname[i_var]+histname_suffix[i_cut]+"_PU" << endl;
        
        TFile* file = new TFile(filepath);
        if( !file ){
          cout << "No file : " << filepath << endl;
          continue;
        }

        TH1F* hist_temp = (TH1F*)file->Get(histname[i_var]+histname_suffix[i_cut]+"_PU");
        if(!hist_temp){
          cout << "No histogram : " << current_sample << endl;
          file->Close();
          delete file;
          continue;
        }
        
        hist_temp->Rebin( n_rebin(histname_suffix[i_cut], histname[i_var]) );
        
        if( i_file < bkglist.size() ){ // bkg
          TString current_MCsector = find_MCsector(i_file);
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
        else if( i_file == bkglist.size() ){ // data for i_file = bkglist.size()
          hist_temp->SetMarkerStyle(3);
          hist_temp->SetMarkerSize(1);
          hist_data = (TH1F*)hist_temp->Clone();
        }
        else{ // signal starting from i_file = bkglist.size()+1
          int signal_index = i_file-bkglist.size()-1;
          //cout << "signal index = " << signal_index << ", mass = " << signal_mass[signal_index] << endl;
          hist_temp->SetLineColor(signal_color[signal_index]);
          hist_temp->SetLineWidth(2);
          if(signal_mass[signal_index] == 40){
            if( histname_suffix[i_cut] == "_cut0" || histname_suffix[i_cut] == "_cutdR" ){
              hist_temp->Scale(k_factor*0.001);
              coupling_const.push_back(0.001);
            }
            else{
              hist_temp->Scale(k_factor*0.0001);
              coupling_const.push_back(0.0001);
            }
          }
          else if(signal_mass[signal_index] == 50){
            if( histname_suffix[i_cut] == "_cut0" || histname_suffix[i_cut] == "_cutdR" ){
              hist_temp->Scale(k_factor*0.001);
              coupling_const.push_back(0.001);
            }
            else{
              hist_temp->Scale(k_factor*0.0001);
              coupling_const.push_back(0.0001);
            }
          }
          else if(signal_mass[signal_index] == 60){
            if( histname_suffix[i_cut] == "_cut0" || histname_suffix[i_cut] == "_cutdR" ){
              hist_temp->Scale(k_factor*0.001);
              coupling_const.push_back(0.001);
            }
            else{
              hist_temp->Scale(k_factor*0.0001);
              coupling_const.push_back(0.0001);
            }
          }
          else if(signal_mass[signal_index] == 150){
            hist_temp->Scale(k_factor*1.);
            coupling_const.push_back(1.);
          }
          else if(signal_mass[signal_index] == 700){
            hist_temp->Scale(k_factor*1000.);
            coupling_const.push_back(1000.);
          }
          else{
            cout << "[Warning] This should not happen!" << endl;
          }
          
          hist_signal.push_back( (TH1F*)hist_temp->Clone() );
        }
        
        fill_legend(lg, hist_temp, i_file);
        
        file->Close();
        delete file;
        
        //cout << "end of this sample" << endl;
        
      } // END loop over samples
      //cout << "-List of Files-" << endl;
      //gROOT->GetListOfFiles();
      //cout << endl;

    
      //cout << "[Draw Canvas]" << endl;
      //cout << "size of coupling_constant = " << coupling_const.size() << endl;
    
      draw_canvas(MC_stacked, MC_stacked_err, hist_data, hist_signal, lg, i_cut, i_var);

      // legend is already deleted in draw_canvas()
      //delete lg; 
      
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
  for(unsigned int i=0; i<MCsector_first_index.size()-1; i++){
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
  // here, hist_for_legned = {"A", "B", "D"}
  // now, push_back data and signal to make
  // hist_for_legned = {"A", "B", "D", "data", "HN40", "HN50", "HN60"}
  if( index == (int)bkglist.size() ){ // data
    hist_for_legend.push_back((TH1F*)hist->Clone());
    //cout << "Data added in hist_for_legend" << endl;
  }
  if( index > (int)bkglist.size() ){ // signal
    hist_for_legend.push_back((TH1F*)hist->Clone());
    //cout << "Signal added in hist_for_legend" << endl;
  }
  else{ // bkg
    TString current_MCsector = find_MCsector(index);
    //cout << "[fill_legend] " << "index " << index << ", current_MCsector is " << current_MCsector << endl;
    if( !MCsector_survive[current_MCsector] ){
      //cout << "[fill_legend] " << bkglist[index] << " is saved" << endl;
      hist_for_legend.push_back((TH1F*)hist->Clone());
      MCsector_survive[current_MCsector] = true;
    }
  }


}

void trilepton_mumumu::draw_legend(TLegend* lg, signal_class sc){
  // Example :
  //                      0    1    2    3
  // samples_to_use   = {"A", "B", "C", "D"}
  // MCsector_survive = { T ,  T ,  F ,  T }
  //
  //                       0    1    2      3        4          5
  // hist_for_legend are {"A", "B", "D", "data", "signal1", "signal2"}
  // i_data = 6 - 2 - 1 = 3
  
  int i_data = (int)hist_for_legend.size()-(int)signal_mass.size()-1;
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
  //cout << "i_data = " << i_data << ", size if hist_for_legend = " << hist_for_legend.size() << endl;
  if(sc == class1){
    lg->AddEntry(hist_for_legend.at(i_data+1), "HN40, |V_{N#mu}|^{2}=10^{"+TString::Itoa(TMath::Log10(coupling_const.at(0)), 10)+"}", "l");
    lg->AddEntry(hist_for_legend.at(i_data+2), "HN50, |V_{N#mu}|^{2}=10^{"+TString::Itoa(TMath::Log10(coupling_const.at(1)), 10)+"}", "l");
  }
  else if(sc == class2){
    lg->AddEntry(hist_for_legend.at(i_data+3), "HN60, |V_{N#mu}|^{2}=10^{"+TString::Itoa(TMath::Log10(coupling_const.at(2)), 10)+"}", "l");
  }
  else if(sc == no_class){
    lg->AddEntry(hist_for_legend.at(i_data+1), "HN40, |V_{N#mu}|^{2}=10^{"+TString::Itoa(TMath::Log10(coupling_const.at(0)), 10)+"}", "l");
    lg->AddEntry(hist_for_legend.at(i_data+2), "HN50, |V_{N#mu}|^{2}=10^{"+TString::Itoa(TMath::Log10(coupling_const.at(1)), 10)+"}", "l");
    lg->AddEntry(hist_for_legend.at(i_data+3), "HN60, |V_{N#mu}|^{2}=10^{"+TString::Itoa(TMath::Log10(coupling_const.at(2)), 10)+"}", "l");
    lg->AddEntry(hist_for_legend.at(i_data+4), "HN150, |V_{N#mu}|^{2}=10^{"+TString::Itoa(TMath::Log10(coupling_const.at(3)), 10)+"}", "l");
    lg->AddEntry(hist_for_legend.at(i_data+5), "HN700, |V_{N#mu}|^{2}=10^{"+TString::Itoa(TMath::Log10(coupling_const.at(4)), 10)+"}", "l");
  }
  else if(sc == class3){
    lg->AddEntry(hist_for_legend.at(i_data+4), "HN150, |V_{N#mu}|^{2}=10^{"+TString::Itoa(TMath::Log10(coupling_const.at(3)), 10)+"}", "l");
  }
  else if(sc == class4){
    lg->AddEntry(hist_for_legend.at(i_data+5), "HN700, |V_{N#mu}|^{2}=10^{"+TString::Itoa(TMath::Log10(coupling_const.at(4)), 10)+"}", "l");
  }
  else{
    cout << "[Warning] This should not happen!" << endl;
  }
  lg->SetFillStyle(0);
  lg->SetBorderSize(0);
  lg->Draw();
}

void trilepton_mumumu::draw_canvas(THStack* mc_stack, TH1F* mc_error, TH1F* hist_data, vector<TH1F*> hist_signal, TLegend* legend, int index_cut, int index_var){

  signal_class this_sc;
  if( histname[index_var].Contains("class1") ) this_sc = class1;
  else if( histname[index_var].Contains("class2") ) this_sc = class2;
  else this_sc = no_class;
  
  //y=0//
  double x_0[2], y_0[2];
  x_0[0] = -1000;  y_0[0] = 0;
  x_0[1] = 1000;  y_0[1] = 0;
  TGraph *g0 = new TGraph(2, x_0, y_0);
  //y=1//
  double x_1[2], y_1[2];
  x_1[0] = 1000;  y_1[0] = 1;
  x_1[1] = -1000;  y_1[1] = 1;
  TGraph *g1 = new TGraph(2, x_1, y_1);
  
  TCanvas* c1 = new TCanvas(histname[index_var], "", 800, 800);
  //canvas_margin(c1);
  TPad *c1_up = new TPad("c1_up", "", 0, 0.25, 1, 1);
  c1_up->SetTopMargin( 0.05 ); c1_up->SetBottomMargin( 0.02 ); c1_up->SetRightMargin( 0.02 ); c1_up->SetLeftMargin( 0.1 );
  TPad *c1_down = new TPad("c1_down", "", 0, 0, 1, 0.25);
  c1_down->SetTopMargin( 0.03 ); c1_down->SetBottomMargin( 0.25 ); c1_down->SetRightMargin( 0.02 ); c1_down->SetLeftMargin( 0.1 ); c1_down->SetGridx(); c1_down->SetGridy();
  c1_up->Draw();
  c1_down->Draw();
  c1_up->cd();
  //bkg//
  mc_stack->Draw("hist");
  mc_stack->SetMaximum( y_max( histname_suffix[index_cut], histname[index_var] ) );
  mc_stack->GetXaxis()->SetLabelSize(0);
  mc_stack->GetYaxis()->SetLabelSize(0.05);
  mc_stack->GetYaxis()->SetTitleSize(0.05);
  mc_stack->GetYaxis()->SetTitleOffset(1.03);
  mc_stack->GetYaxis()->SetTitle("Events"); //FIXME
  //mc_stack->GetYaxis()->SetTitle("Events / "+TString::Itoa(7,10)+" GeV"); //FIXME
  mc_stack->GetYaxis()->SetTitleOffset(1.03);
  //data//
  hist_data->Draw("PE1same");
  //signal//
  if(this_sc == class1){
    hist_signal[0]->Draw("histsame");
    hist_signal[1]->Draw("histsame");
  }
  else if(this_sc == class2){
    hist_signal[2]->Draw("histsame");
  }
  else if(this_sc == class3){
    hist_signal[3]->Draw("histsame");
  }
  else if(this_sc == class4){
    hist_signal[4]->Draw("histsame");
  }
  else if(this_sc == no_class){
    hist_signal[0]->Draw("histsame");
    hist_signal[1]->Draw("histsame");
    hist_signal[2]->Draw("histsame");
    hist_signal[3]->Draw("histsame");
    hist_signal[4]->Draw("histsame");
  }
  else{
    cout << "[Warning] This should not happen!" << endl;
  }
  //err//
  mc_error->SetMarkerColorAlpha(kAzure-9, 0);
  mc_error->SetFillStyle(3004);
  mc_error->SetFillColor(kBlue);
  mc_error->Draw("sameE2");
  //legend//
  draw_legend(legend, this_sc);
  //MC-DATA//
  c1_down->cd();
  TH1F* hist_compare = (TH1F*)hist_data->Clone();
  hist_compare->SetTitle("");
  hist_compare->Divide(mc_error);
  hist_compare->SetMaximum(2);
  hist_compare->SetMinimum(0);
  hist_compare->GetXaxis()->SetTitle(x_title[index_var]);
  hist_compare->GetXaxis()->SetLabelSize(0.10);
  hist_compare->GetXaxis()->SetTitleSize(0.10);
  hist_compare->GetYaxis()->SetLabelSize(0.08);
  hist_compare->SetYTitle("#frac{DATA}{MC}");
  hist_compare->GetYaxis()->SetTitleSize(0.08);
  hist_compare->GetYaxis()->SetTitleOffset(0.4);
  hist_compare->SetFillColorAlpha(45,0.35);
  hist_compare->Draw("PE1same");
  //X axis range//
  //if(histname[index_var] == "z_candidate_mass") MC_stacked->GetXaxis()->SetRangeUser(70, 110);
  if(histname[index_var] == "h_PFMET") SetXaxisRangeBoth(mc_stack, hist_compare, 0, 300);
  //if(histname[index_var].Contains("Lepton_Pt")) SetXaxisRangeBoth(mc_stack, hist_compare, 0, 200);
  if(histname[index_var].Contains("LeptonRelIso")) SetXaxisRangeBoth(mc_stack, hist_compare, 0, 0.1);
  
  //y=1 line//
  g1->Draw("same");
  
  c1->SaveAs("./plots/"+histname[index_var]+histname_suffix[index_cut]+".png");
  outputfile->cd(histname_suffix[index_cut]);
  c1->Write();
  
  delete legend;
  delete c1;
}

int trilepton_mumumu::n_rebin(TString cut, TString var){
  if(cut == "_cut0"){
    if(var.Contains("HN_mass")) return 1;
    else if(var == "W_pri_lowmass_mass") return 1;
    else if(var == "deltaR_OS_min") return 1;
    else if(var == "gamma_star_mass") return 1;
    else if(var == "n_jet") return 1;
    else if(var == "z_candidate_mass") return 1;
    else if(var == "h_PFMET") return 1;
    else if(var.Contains("Lepton_Pt")) return 1;
    else if(var.Contains("Lepton_Eta")) return 5;
    else return 1;
  }
  else if(cut == "_cutdR"){
    if(var.Contains("HN_mass")) return 1;
    else if(var == "W_pri_lowmass_mass") return 1;
    else if(var == "deltaR_OS_min") return 1;
    else if(var == "gamma_star_mass") return 1;
    else if(var == "n_jet") return 1;
    else if(var == "z_candidate_mass") return 1;
    else if(var == "h_PFMET") return 1;
    else if(var.Contains("Lepton_Pt")) return 1;
    else if(var.Contains("Lepton_Eta")) return 5;
    else return 1;
  }
  else if(cut == "_cutdR_cutW"){
    if(var.Contains("HN_mass")) return 1;
    else if(var == "W_pri_lowmass_mass") return 1;
    else if(var == "deltaR_OS_min") return 1;
    else if(var == "gamma_star_mass") return 1;
    else if(var == "n_jet") return 1;
    else if(var == "z_candidate_mass") return 1;
    else if(var == "h_PFMET") return 1;
    else if(var.Contains("Lepton_Pt")) return 1;
    else if(var.Contains("Lepton_Eta")) return 5;
    else return 1;
  }
  else return 1;
}

double trilepton_mumumu::y_max(TString cut, TString var){
  if(cut == "_cut0"){
    if(var.Contains("HN_mass")) return 500;
    else if(var == "W_pri_lowmass_mass") return 600;
    else if(var == "deltaR_OS_min") return 600;
    else if(var == "gamma_star_mass") return 600;
    else if(var == "n_jet") return 1400;
    else if(var == "z_candidate_mass") return 600;
    else if(var == "h_PFMET") return 600;
    else if(var.Contains("Lepton_Pt")){
      if(var.Contains("third")) return 2100;
      else return 600;
    }
    else if(var.Contains("Lepton_Eta")) return 1000;
    else if(var.Contains("LeptonRelIso")) return 1000;
    else if(var.Contains("dXY")) return 200;
    else if(var.Contains("dZ")) return 100;
    else return 1000;
  }
  else if(cut == "_cutdR"){
    if(var.Contains("HN_mass")) return 350;
    else if(var == "W_pri_lowmass_mass") return 600;
    else if(var == "deltaR_OS_min") return 200;
    else if(var == "gamma_star_mass") return 200;
    else if(var == "n_jet") return 1000;
    else if(var == "z_candidate_mass") return 2000;
    else if(var == "h_PFMET") return 400;
    else if(var.Contains("Lepton_Pt")){
      if(var.Contains("third")) return 1500;
      else return 400;
    }
    else if(var.Contains("Lepton_Eta")) return 1000;
    else return 1000;
  }
  else if(cut == "_cutdR_cutW"){
    if(var.Contains("HN_mass")) return 100;
    else if(var == "W_pri_lowmass_mass") return 150;
    else if(var == "deltaR_OS_min") return 100;
    else if(var == "gamma_star_mass") return 60;
    else if(var == "n_jet") return 100;
    else if(var == "z_candidate_mass") return 50;
    else if(var == "h_PFMET") return 100;
    else if(var.Contains("Lepton_Pt")){
      if(var.Contains("third")) return 150;
      else return 100;
    }
    else if(var.Contains("Lepton_Eta")) return 100;
    else return 100;
  }
  else return 1000;
}

  
void trilepton_mumumu::SetXaxisRangeBoth(THStack* mc_stack, TH1F* hist, float xmin, float xmax){
  mc_stack->GetXaxis()->SetRangeUser(xmin, xmax);
  hist->GetXaxis()->SetRangeUser(xmin, xmax);
}










