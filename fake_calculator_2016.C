#include "canvas_margin.h"
#include "TSystem.h"
#include "setTDRStyle.C"

//==== MC list = {first, second, third ...}
//==== then, first will be filled at the bottom, so we want them in the bottom of legend
void make_legend(TLegend *lg, TString MCtype, vector<TH1D*> hists, vector<TString> alias);

void fake_calculator_2016(){

  TH1::SetDefaultSumw2(true);
  TH1::AddDirectory(kFALSE);
  gStyle->SetOptStat(0);
  setTDRStyle();

  TString dataclass = "v8-0-2.8/FakeRateCalculator/";
  TString cmssw_version = "cat_v8-0-2";
  TString plotpath = "./plots/"+dataclass;
  
  if( !gSystem->mkdir(plotpath, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }

  map< TString, vector<TString> > map_string_to_MC_list;
  map< TString, vector<TString> > map_string_to_MC_alias;
  map< TString, vector<Color_t> > map_string_to_MC_color;
  vector<TString> all_MC_list;
  
	all_MC_list = {"singletop", "TTJets_aMC", "DY", "WJets", "VV", "QCD_DoubleEM", "QCD_mu", "HN40_mumumu_VmuN_0p1"};
	map_string_to_MC_list["SingleMuon"] = {"singletop", "TTJets_aMC", "DY", "WJets"};
  map_string_to_MC_alias["SingleMuon"] = {"singletop", "ttbar", "DY", "WJets"};
	map_string_to_MC_color["SingleMuon"] = {kOrange, kRed, kYellow, kGreen};
	map_string_to_MC_list["DiMuon"] = {"VV", "TTJets_aMC", "DY"};
  map_string_to_MC_alias["DiMuon"] = {"VV", "ttbar", "DY"};
	map_string_to_MC_color["DiMuon"] = {kSpring-1, kRed, kYellow};
	map_string_to_MC_list["TriMuon"] = {"VV"};
  map_string_to_MC_alias["TriMuon"] = {"VV"};
	map_string_to_MC_color["TriMuon"] = {kSpring-1};
  
  //==== get all files here
  map< TString, TFile* > map_string_to_file;
  map_string_to_file["data"] = new TFile("./rootfiles/"+dataclass+"/FakeRateCalculator_Mu_data_DoubleMuon_cat_v8-0-2.root");
  //map_string_to_file["data_low_pt"] = new TFile("./rootfiles/"+dataclass+"/FakeRateCalculator_Mu_periodD_SKmuon_lowpt_5_3_20.root");
  for(unsigned int i=0; i<all_MC_list.size(); i++){
    TString this_samplename = all_MC_list.at(i);
    map_string_to_file[this_samplename] = new TFile("./rootfiles/"+dataclass+"/FakeRateCalculator_Mu_SK"+this_samplename+"_"+cmssw_version+".root");
    if(!map_string_to_file[this_samplename]) cout << "[No file] :" << this_samplename << endl;
  }
  

  
  //======================
  //==== LooseMuon study
  //======================
  
  cout << "######################## Loose Muon study ########################" << endl;
  
  vector<TString> type_Loose_study = {"SingleMuonTrigger", "SingleMuonTrigger_HighdXY", "DiMuonTrigger_HighdXY"};
  vector<TString> var_Loose_study = {"RelIso", "Chi2", "dXY", "dXYSig"};
  for(unsigned int it_type_Loose_study=0; it_type_Loose_study<type_Loose_study.size(); it_type_Loose_study++){

    //==== e.g., "SingleMuon"
    TString this_type_Loose_study = type_Loose_study.at(it_type_Loose_study);
    cout << this_type_Loose_study << endl;
    
    //==== prepare MC iterator end point
    vector<TString>::iterator it_MC_END;
    TString this_MC_type;
    if(this_type_Loose_study.Contains("SingleMuon")) this_MC_type = "SingleMuon";
    if(this_type_Loose_study.Contains("DiMuon")) this_MC_type = "DiMuon";
    it_MC_END = map_string_to_MC_list[this_MC_type].end();
    
    for(unsigned int it_var_Loose_study=0; it_var_Loose_study<var_Loose_study.size(); it_var_Loose_study++){
    
      //==== e.g., "RelIso"
      TString this_var_Loose_study = var_Loose_study.at(it_var_Loose_study);
      
      //==== data
      TH1D* hist_data = (TH1D*)map_string_to_file["data"]->Get(this_type_Loose_study+"_LooseMuon_"+this_var_Loose_study);
      hist_data->SetMarkerStyle(8);
      hist_data->SetMarkerColor(kBlack);
      
      //==== prepare stack for MC
      THStack* MC_stack = new THStack("MC_Stack", "");
      
      //==== hists for legend
      vector<TH1D*> MChist_for_legend;
      vector<TString> MCalias_for_legend;
      MChist_for_legend.clear();
      MCalias_for_legend.clear();
      
      //==== MC iterator
      vector<TString>::iterator it_MC;
      it_MC = map_string_to_MC_list[this_MC_type].begin();

      //==== MC loop
      for(int aaa=0; it_MC != it_MC_END; ++it_MC, aaa++ ){
        TString this_samplename = *it_MC;
        TH1D* MC_temp = (TH1D*)map_string_to_file[this_samplename]->Get(this_type_Loose_study+"_LooseMuon_"+this_var_Loose_study);
        
        if( !MC_temp ){
          cout << "No Histogram : " << this_samplename << endl;
          continue;
        }
        else{
          MC_temp->SetFillColor( map_string_to_MC_color[this_MC_type].at(aaa) );
          MC_temp->SetLineColor( map_string_to_MC_color[this_MC_type].at(aaa) );
        }
        
        MChist_for_legend.push_back( (TH1D*)MC_temp->Clone() );
        MCalias_for_legend.push_back( map_string_to_MC_alias[this_MC_type].at(aaa) );
        MC_stack->Add(MC_temp);
      }
      
      
      //==== legend
      TLegend* lg = new TLegend(0.6, 0.6, 0.9, 0.9);
      lg->SetFillStyle(0);
      lg->SetBorderSize(0);
      lg->AddEntry(hist_data, "Data", "p");
      make_legend(lg, this_MC_type, MChist_for_legend, MCalias_for_legend);
      
      TCanvas* c_Loose_study = new TCanvas("c_Loose_study", "", 800, 600);
      //canvas_margin(c_Loose_study);
      c_Loose_study->cd();
      gPad->SetLogy();
      //==== MC
      MC_stack->Draw("hist");
      MC_stack->GetXaxis()->SetTitle(this_var_Loose_study);
      MC_stack->GetYaxis()->SetTitle("Events");
      MC_stack->SetTitle("");
      MC_stack->SetMaximum(1000000);
      MC_stack->SetMinimum(1);
      //==== data
      hist_data->Draw("psame");
      lg->Draw();
      c_Loose_study->SaveAs(plotpath+"/"+this_type_Loose_study+"_LooseMuon_study_"+this_var_Loose_study+".png");
      c_Loose_study->Close();
      delete c_Loose_study;
      
    }
  }
  
  //======================================================
  //==== dXYSig cut optimization plots using DY, QCD
  //======================================================

  cout << "######################## dXYSig cut optimization study ########################" << endl;
  
  vector<TString> MuonId = {"Loose", "Tight"};
  vector<TString> var_dXY_cut_study = {"dXY", "dXYSig", "dXYSig_dXYcut_10mm"};
  for(unsigned int i=0; i<MuonId.size(); i++){
    for(unsigned int j=0; j<var_dXY_cut_study.size(); j++){
      
      //if(MuonId.at(i)=="Loose" && var_dXY_cut_study.at(j).Contains("0p1mm")) continue;
      //if(MuonId.at(i)=="Loose" && var_dXY_cut_study.at(j).Contains("0p1mm")) continue;
      
      cout << MuonId.at(i)+"IsoMuon_prompt_"+var_dXY_cut_study.at(j) << endl;
      cout << MuonId.at(i)+"IsoMuon_fake_"+var_dXY_cut_study.at(j) << endl;

      TH1D* hist_DY = (TH1D*)map_string_to_file["DY"]->Get("DiMuonTrigger_"+MuonId.at(i)+"IsoMuon_prompt_"+var_dXY_cut_study.at(j));
      TH1D* hist_signal = (TH1D*)map_string_to_file["HN40_mumumu_VmuN_0p1"]->Get("DiMuonTrigger_"+MuonId.at(i)+"IsoMuon_prompt_"+var_dXY_cut_study.at(j));
      //TH1D* hist_QCD_mumu = (TH1D*)map_string_to_file["QCD_DoubleEM"]->Get("DiMuonTrigger_"+MuonId.at(i)+"IsoMuon_fake_"+var_dXY_cut_study.at(j));
      TH1D* hist_QCD_mumu = (TH1D*)map_string_to_file["QCD_mu"]->Get("DiMuonTrigger_"+MuonId.at(i)+"IsoMuon_fake_"+var_dXY_cut_study.at(j)); //FIXME no bb sample in v8-0-2
      
      hist_DY->SetLineColor(kBlue);
      hist_signal->SetLineColor(kRed);
      hist_QCD_mumu->SetLineColor(kBlack);
      
      TLegend* lg_dXY = new TLegend(0.6, 0.6, 0.9, 0.9);
      lg_dXY->SetFillStyle(0);
      lg_dXY->SetBorderSize(0);
      lg_dXY->AddEntry(hist_DY, "Drell-Yan", "l");
      lg_dXY->AddEntry(hist_signal, "HN40", "l");
      lg_dXY->AddEntry(hist_QCD_mumu, "Fake (ttbar+QCD)", "l");
      
      TCanvas* c_dXY = new TCanvas("c_dXY", "", 800, 600);
      //canvas_margin(c_dXY);
      c_dXY->cd();
      c_dXY->SetLogy(kTRUE);
      
      hist_DY->DrawNormalized("histsame", 1);
      hist_DY->SetTitle("");
      hist_DY->GetYaxis()->SetTitle("Normalized Events");
      hist_signal->DrawNormalized("histsame", 1);
      hist_QCD_mumu->DrawNormalized("histsame", 1);
      lg_dXY->Draw();
      c_dXY->SaveAs(plotpath+"/"+MuonId.at(i)+"IsoMuon_"+var_dXY_cut_study.at(j)+".png");
      
      //==== dXY/sigma cut efficiecny
      if(var_dXY_cut_study.at(j).Contains("Err")){
        double dXY_cut[3] = {3., 4., 5.};
        for(int c=0; c<3; c++){
          double eff_prompt = hist_DY->Integral( dXY_cut[c]/0.2 + 1 ,hist_DY->GetXaxis()->GetNbins() ) / hist_DY->Integral();
          double eff_fake   = hist_QCD_mumu->Integral( dXY_cut[c]/0.2 + 1  ,hist_QCD_mumu->GetXaxis()->GetNbins() ) / hist_QCD_mumu->Integral();
          cout
          << "MuonID = " << MuonId.at(i) << endl
          << "Err Type = " << var_dXY_cut_study.at(j) << endl
          << "Cut : dXY/sigma > " << dXY_cut[c] << endl
          << "  eff_prompt = " << eff_prompt << endl
          << "  eff_fake = " << eff_fake << endl
          << "  ===> eff_fake/eff_prompt = " << eff_fake/eff_prompt << endl
          << endl;
        }
      }
      
      c_dXY->Close();
      delete c_dXY;
      delete lg_dXY;

      
    }
  }

  //=============================================
  //==== FR plots (Num/Den, 2D FR, 1D FR curve)
  //=============================================
  
  cout << "######################## FR plots ########################" << endl;
  
  vector<TString> FR_method = {
    "SingleMuonTrigger_Dijet",
    "SingleMuonTrigger_HighdXY", "SingleMuonTrigger_HighdXY_0jet", "SingleMuonTrigger_HighdXY_withjet", "SingleMuonTrigger_HighdXY_withjet_0bjet", "SingleMuonTrigger_HighdXY_withjet_withbjet",
    "DiMuonTrigger_HighdXY"
  };
  vector<TString> var_FR = {"eta", "pt", "RelIso", "Chi2", "dXY", "dXYSig"};
  vector<TString> x_title_FR = {"#eta", "p_{T}", "RelIso", "#chi^{2}", "|dXY|", "|dXY/#sigma(dXY)|"};
  
  for(unsigned int it_FR_method=0; it_FR_method<FR_method.size(); it_FR_method++){
    
    TString this_FR_method = FR_method.at(it_FR_method);
    cout << "######################## " << this_FR_method << endl;
    
    //==== prepare MC iterator end point
    vector<TString>::iterator it_MC_END;
    TString this_MC_type;
    if(this_FR_method.Contains("SingleMuon")) this_MC_type = "SingleMuon";
    if(this_FR_method.Contains("DiMuon")) this_MC_type = "DiMuon";
    if(this_FR_method.Contains("TagZ")) this_MC_type = "TriMuon";
    
    it_MC_END = map_string_to_MC_list[this_MC_type].end();
    
    //==== Num/Den
    for(unsigned int it_var_FR=0; it_var_FR<var_FR.size(); it_var_FR++){
    
      TString this_var_FR = var_FR.at(it_var_FR);
      TString this_x_title_FR = x_title_FR.at(it_var_FR);
      
      //==== data
      TH1D *num_data = (TH1D*)map_string_to_file["data"]->Get(this_FR_method+"_"+this_var_FR+"_F");
      TH1D *den_data = (TH1D*)map_string_to_file["data"]->Get(this_FR_method+"_"+this_var_FR+"_F0");
      num_data->SetMarkerStyle(8);
      num_data->SetMarkerColor(kBlack);
      den_data->SetMarkerStyle(8);
      den_data->SetMarkerColor(kBlack);
      
      //==== prepare stack for prompt MC
      THStack* num_MC_stack = new THStack("num_MC_stack", "");
      THStack* den_MC_stack = new THStack("den_MC_stack", "");
      
      //==== rebin pT..
      if(this_var_FR == "pt"){
        num_data->Rebin(5);
        den_data->Rebin(5);
      }
      
      //==== hists for legend
      vector<TH1D*> MChist_for_legend;
      vector<TString> MCalias_for_legend;
      MChist_for_legend.clear();
      MCalias_for_legend.clear();
      
      //==== MC iterator
      vector<TString>::iterator it_MC;
      it_MC = map_string_to_MC_list[this_MC_type].begin();
      
      //==== MC loop
      for(int aaa=0; it_MC != it_MC_END; ++it_MC, aaa++ ){
        TString this_samplename = *it_MC;
        TH1D* num_MC_temp = (TH1D*)map_string_to_file[this_samplename]->Get(this_FR_method+"_"+this_var_FR+"_F");
        TH1D* den_MC_temp = (TH1D*)map_string_to_file[this_samplename]->Get(this_FR_method+"_"+this_var_FR+"_F0");
        
        if( !num_MC_temp || !den_MC_temp ){
          cout << "No Histogram : " << this_samplename << endl;
          continue;
        }
        else{
          if(this_var_FR == "pt"){
            num_MC_temp->Rebin(5);
            den_MC_temp->Rebin(5);
          }
          
          num_MC_temp->SetFillColor( map_string_to_MC_color[this_MC_type].at(aaa) );
          num_MC_temp->SetLineColor( map_string_to_MC_color[this_MC_type].at(aaa) );
          den_MC_temp->SetFillColor( map_string_to_MC_color[this_MC_type].at(aaa) );
          den_MC_temp->SetLineColor( map_string_to_MC_color[this_MC_type].at(aaa) );
        }
        
        MChist_for_legend.push_back( (TH1D*)num_MC_temp->Clone() );
        MCalias_for_legend.push_back( map_string_to_MC_alias[this_MC_type].at(aaa) );
        num_MC_stack->Add(num_MC_temp);
        den_MC_stack->Add(den_MC_temp);
      }
      
      //==== legend
      TLegend *lg = new TLegend(0.6, 0.6, 0.9, 0.9);
      lg->SetFillStyle(0);
      lg->SetBorderSize(0);
      lg->AddEntry(num_data, "Data", "p");
      make_legend(lg, this_MC_type, MChist_for_legend, MCalias_for_legend);
      
      //==== Y axis range
      if(this_FR_method == "SingleMuonTrigger_Dijet"){
        if(this_var_FR == "pt"){
          num_MC_stack->SetMaximum(10000);
          num_MC_stack->SetMinimum(1);
          den_MC_stack->SetMaximum(10000);
          den_MC_stack->SetMinimum(1);
        }
        if(this_var_FR == "eta"){
          num_MC_stack->SetMaximum(6000);
          num_MC_stack->SetMinimum(1);
          den_MC_stack->SetMaximum(6000);
          den_MC_stack->SetMinimum(1);
        }
        if(this_var_FR == "RelIso"){
          num_MC_stack->SetMaximum(1000000);
          num_MC_stack->SetMinimum(10);
          den_MC_stack->SetMaximum(1000000);
          den_MC_stack->SetMinimum(10);
        }
        if(this_var_FR == "Chi2"){
          num_MC_stack->SetMaximum(1000000);
          num_MC_stack->SetMinimum(10);
          den_MC_stack->SetMaximum(1000000);
          den_MC_stack->SetMinimum(10);
        }
      }
      if(this_FR_method == "SingleMuonTrigger_HighdXY"){
        if(this_var_FR == "pt"){
          num_MC_stack->SetMaximum(10000000);
          num_MC_stack->SetMinimum(1);
          den_MC_stack->SetMaximum(10000000);
          den_MC_stack->SetMinimum(1);
        }
        if(this_var_FR == "eta"){
          num_MC_stack->SetMaximum(1000000);
          num_MC_stack->SetMinimum(1);
          den_MC_stack->SetMaximum(1000000);
          den_MC_stack->SetMinimum(1);
        }
        if(this_var_FR == "RelIso"){
          num_MC_stack->SetMaximum(1000000);
          num_MC_stack->SetMinimum(1);
          den_MC_stack->SetMaximum(1000000);
          den_MC_stack->SetMinimum(1);
        }
        if(this_var_FR == "Chi2"){
          num_MC_stack->SetMaximum(1000000);
          num_MC_stack->SetMinimum(1);
          den_MC_stack->SetMaximum(1000000);
          den_MC_stack->SetMinimum(1);
        }
        if(this_var_FR == "dXY"){
          num_MC_stack->SetMaximum(1000000);
          num_MC_stack->SetMinimum(1);
          den_MC_stack->SetMaximum(1000000);
          den_MC_stack->SetMinimum(1);
        }
        if(this_var_FR == "dXYSig"){
          num_MC_stack->SetMaximum(1000000);
          num_MC_stack->SetMinimum(1);
          den_MC_stack->SetMaximum(1000000);
          den_MC_stack->SetMinimum(1);
        }
      }
      if(this_FR_method == "DiMuonTrigger_HighdXY"){
        if(this_var_FR == "pt"){
          num_MC_stack->SetMaximum(1000000);
          num_MC_stack->SetMinimum(0.1);
          den_MC_stack->SetMaximum(1000000);
          den_MC_stack->SetMinimum(1);
        }
        if(this_var_FR == "eta"){
          num_MC_stack->SetMaximum(1000000);
          num_MC_stack->SetMinimum(0.1);
          den_MC_stack->SetMaximum(1000000);
          den_MC_stack->SetMinimum(0.1);
        }
        if(this_var_FR == "RelIso"){
          num_MC_stack->SetMaximum(1000000);
          num_MC_stack->SetMinimum(0.1);
          den_MC_stack->SetMaximum(1000000);
          den_MC_stack->SetMinimum(0.1);
        }
        if(this_var_FR == "Chi2"){
          num_MC_stack->SetMaximum(1000000);
          num_MC_stack->SetMinimum(0.1);
          den_MC_stack->SetMaximum(1000000);
          den_MC_stack->SetMinimum(0.1);
        }
      }
      if(this_FR_method == "DiMuonTrigger_TagZ_width_10"){
        if(this_var_FR == "pt"){
          num_MC_stack->SetMaximum(1000000);
          num_MC_stack->SetMinimum(0.1);
          den_MC_stack->SetMaximum(1000000);
          den_MC_stack->SetMinimum(0.1);
        }
        if(this_var_FR == "eta"){
          num_MC_stack->SetMaximum(1000000);
          num_MC_stack->SetMinimum(0.1);
          den_MC_stack->SetMaximum(1000000);
          den_MC_stack->SetMinimum(0.1);
        }
        if(this_var_FR == "RelIso"){
          num_MC_stack->SetMaximum(1000000);
          num_MC_stack->SetMinimum(0.1);
          den_MC_stack->SetMaximum(1000000);
          den_MC_stack->SetMinimum(0.1);
        }
        if(this_var_FR == "Chi2"){
          num_MC_stack->SetMaximum(1000000);
          num_MC_stack->SetMinimum(0.1);
          den_MC_stack->SetMaximum(1000000);
          den_MC_stack->SetMinimum(0.1);
        }
      }
      if(this_FR_method == "DiMuonTrigger_TagZ_width_20"){
        if(this_var_FR == "pt"){
          num_MC_stack->SetMaximum(1000000);
          num_MC_stack->SetMinimum(0.1);
          den_MC_stack->SetMaximum(1000000);
          den_MC_stack->SetMinimum(0.1);
        }
        if(this_var_FR == "eta"){
          num_MC_stack->SetMaximum(1000000);
          num_MC_stack->SetMinimum(0.1);
          den_MC_stack->SetMaximum(1000000);
          den_MC_stack->SetMinimum(0.1);
        }
        if(this_var_FR == "RelIso"){
          num_MC_stack->SetMaximum(1000000);
          num_MC_stack->SetMinimum(0.1);
          den_MC_stack->SetMaximum(1000000);
          den_MC_stack->SetMinimum(0.1);
        }
        if(this_var_FR == "Chi2"){
          num_MC_stack->SetMaximum(1000000);
          num_MC_stack->SetMinimum(0.1);
          den_MC_stack->SetMaximum(1000000);
          den_MC_stack->SetMinimum(0.1);
        }
      }
      
      //==== draw numerator
      TCanvas* c_num = new TCanvas("c_num", "", 800, 600);
      //canvas_margin(c_num);
      c_num->cd();
      gPad->SetLogy();
      //==== MC
      num_MC_stack->Draw("hist");
      num_MC_stack->GetXaxis()->SetTitle(this_x_title_FR);
      num_MC_stack->GetYaxis()->SetTitle("Numerator Events");
      num_MC_stack->SetTitle("");
      //==== data
      num_data->Draw("psame");
      lg->Draw();
      c_num->SaveAs(plotpath+"/num_"+this_FR_method+"_"+this_var_FR+".png");
      c_num->Close();
      delete c_num;
      
      //==== draw denominator
      TCanvas* c_den = new TCanvas("c_den", "", 800, 600);
      //canvas_margin(c_den);
      c_den->cd();
      gPad->SetLogy();
      //==== MC
      den_MC_stack->Draw("hist");
      den_MC_stack->GetXaxis()->SetTitle(this_x_title_FR);
      den_MC_stack->GetYaxis()->SetTitle("Denominator Events");
      den_MC_stack->SetTitle("");
      //==== data
      den_data->Draw("psame");
      lg->Draw();
      c_den->SaveAs(plotpath+"/den_"+this_FR_method+"_"+this_var_FR+".png");
      c_den->Close();
      delete c_den;
      
      
    } // END var_FR loop
    
    //==== 2D FR
    
    //==== data
    TH2F* num_data = (TH2F*)map_string_to_file["data"]->Get(this_FR_method+"_events_F");
    TH2F* den_data = (TH2F*)map_string_to_file["data"]->Get(this_FR_method+"_events_F0");
    TH2F* num_data_subtracted = (TH2F*)num_data->Clone();
    TH2F* den_data_subtracted = (TH2F*)den_data->Clone();
    
    //==== MC iterator
    vector<TString>::iterator it_MC;
    it_MC = map_string_to_MC_list[this_MC_type].begin();
    
    //==== MC loop
    for(int aaa=0; it_MC != it_MC_END; ++it_MC, aaa++ ){
      TString this_samplename = *it_MC;
      TH2F *num_MC_temp = (TH2F*)map_string_to_file[this_samplename]->Get(this_FR_method+"_events_F");
      TH2F *den_MC_temp = (TH2F*)map_string_to_file[this_samplename]->Get(this_FR_method+"_events_F0");
      if( !num_MC_temp || !den_MC_temp ){
        cout << "No Histogram : " << this_samplename << endl;
        continue;
      }
      num_data_subtracted->Add(num_MC_temp, -1.);
      den_data_subtracted->Add(den_MC_temp, -1.);
    }

    //==== replace first pt bin by lowpt sample
    int n_xbins = num_data->GetXaxis()->GetNbins();
    int n_ybins = num_data->GetYaxis()->GetNbins();

    //==== before subtraction (= data only)
    TCanvas* c_data = new TCanvas("c_data", "", 1600, 1100);
    //canvas_margin(c_data);
    c_data->SetLeftMargin(0.07);
    c_data->SetRightMargin( 0.1 );
    gStyle->SetPaintTextFormat("0.4f");
    num_data->Divide(den_data);
    num_data->Draw("colztexte1");
    num_data->GetXaxis()->SetRangeUser(10, 60);
    num_data->SetXTitle("p_{T} [GeV]");
    num_data->SetYTitle("|#eta|");
    num_data->SetTitle("");
    c_data->SaveAs(plotpath+"/2D_fakerate_"+this_FR_method+"_before_Prompt_subtraction.png");
    c_data->Close();
    delete c_data;
    
    //==== after subtraction
    TCanvas* c_subtracted = new TCanvas("c_subtracted", "", 1600, 1100);
    //canvas_margin(c_subtracted);
    c_subtracted->SetLeftMargin(0.07);
    c_subtracted->SetRightMargin( 0.1 );
    gStyle->SetPaintTextFormat("0.4f");
    //==== check negative values
    for(int i_x=0; i_x<n_xbins; i_x++){
      for(int i_y=0; i_y<n_ybins; i_y++){
        if(num_data_subtracted->GetBinContent(i_x+1, i_y+1) <= 0 || den_data_subtracted->GetBinContent(i_x+1, i_y+1) <= 0 ){
          num_data_subtracted->SetBinContent(i_x+1, i_y+1, 0);
        }
      }
    }
    num_data_subtracted->Divide(den_data_subtracted);
    num_data_subtracted->Draw("colztexte1");
    num_data_subtracted->GetXaxis()->SetRangeUser(10, 60);
    num_data_subtracted->SetXTitle("p_{T} [GeV]");
    num_data_subtracted->SetYTitle("|#eta|");
    num_data_subtracted->SetTitle("");
    c_subtracted->SaveAs(plotpath+"/2D_fakerate_"+this_FR_method+"_after_Prompt_subtraction.png");
    c_subtracted->Close();
    delete c_subtracted;
    //==== write rootfile
    TString filename = plotpath+"/13TeV_trimuon_FR_"+this_FR_method+".root";
    TFile* file_FR = new TFile(filename, "RECREATE");
    file_FR->cd();
    num_data_subtracted->Write();
    //==== Edge bin numbers
    TH1I* hist_bins = new TH1I("hist_bins", "", 2, 0, 2);
    int n_pt_bins, n_eta_bins;
    if(this_FR_method.Contains("TagZ")){
      n_pt_bins = 3; // pt : 10-40-50-60
      n_eta_bins = 2; // eta : 0.0-1.479-2.5
    }
    else{
      n_pt_bins = 7; // pt : 10-15-20-25-30-35-45-60
      n_eta_bins = 4; // eta : 0.0-0.8-1.479-2.0-2.5
    }
    hist_bins->SetBinContent(1, n_pt_bins);
    hist_bins->SetBinContent(2, n_eta_bins);
    hist_bins->Write();
    
    //==== draw FR curve for each eta region
    TCanvas *c_FR_curve = new TCanvas("c_FR_curve", "", 800, 600);
    //canvas_margin(c_FR_curve);
    c_FR_curve->cd();
    TLegend* lg_FR_curve = new TLegend(0.6, 0.6, 0.9, 0.9);
    lg_FR_curve->SetFillStyle(0);
    lg_FR_curve->SetBorderSize(0);

    TH1D* FR_curve[n_eta_bins];
    Color_t colors[n_eta_bins];
    double x_bins[n_pt_bins+1];
    if(this_FR_method.Contains("TagZ")){
      //==== fill pt(x) bins
      x_bins[0] = 10.;
      x_bins[1] = 40.;
      x_bins[2] = 50.;
      x_bins[3] = 60.;
      //==== fill colors for each eta regions
      colors[0] = kBlack;
      colors[1] = kRed;
    }
    else{
      //==== fill pt(x) bins
      x_bins[0] = 10.;
      x_bins[1] = 15.;
      x_bins[2] = 20.;
      x_bins[3] = 25.;
      x_bins[4] = 30.;
      x_bins[5] = 35.;
      x_bins[6] = 45.;
      x_bins[7] = 60.;
      //==== fill colors for each eta regions
      colors[0] = kBlack;
      colors[1] = kRed;
      colors[2] = kBlue;
      colors[3] = kViolet;
    }
    
    for(int j=0; j<n_eta_bins; j++){
      FR_curve[j] = new TH1D("FR_eta_"+TString::Itoa(j,10), "", n_pt_bins, x_bins);
      for(int k=0; k<n_pt_bins; k++){
        FR_curve[j]->SetBinContent(k+1, num_data_subtracted->GetBinContent(k+1, j+1) );
      }
      FR_curve[j]->SetLineColor(colors[j]);
      FR_curve[j]->Draw("Lsame");
    }
    FR_curve[0]->GetYaxis()->SetRangeUser(0, 1.0);
    if(this_FR_method.Contains("TagZ")){
      lg_FR_curve->AddEntry(FR_curve[0], "0 < |#eta| < 1.479", "l");
      lg_FR_curve->AddEntry(FR_curve[1], "1.479 < |#eta| < 2.5", "l");
    }
    else{
      lg_FR_curve->AddEntry(FR_curve[0], "0 < |#eta| < 0.8", "l");
      lg_FR_curve->AddEntry(FR_curve[1], "0.8 < |#eta| < 1.479", "l");
      lg_FR_curve->AddEntry(FR_curve[2], "1.479 < |#eta| < 2.0", "l");
      lg_FR_curve->AddEntry(FR_curve[3], "2.0 < |#eta| < 2.5", "l");
    }
    lg_FR_curve->Draw();
    c_FR_curve->SaveAs(plotpath+"/FR_curve_"+this_FR_method+".png");
    c_FR_curve->Close();
    delete c_FR_curve;
    
    
  } // END FR_method loop

  //=============================
  //==== MCTruth (scale factor)
  //=============================
  
  cout << "######################## Scale factor ########################" << endl;
  
  vector<TString> MCTruth_trigger = {"SingleMuonTrigger", "DiMuonTrigger"};
  //vector<TString> MC_sample_MCTruth = {"QCD_DoubleEM", "QCD_mu"};
  vector<TString> MC_sample_MCTruth = {"QCD_mu", "QCD_mu"}; //FIXME no bb sample in v8-0-2

  vector<TString> sig_region = {"HighdXY_", ""};
  
  for(unsigned int it_MCTruth_trigger=0; it_MCTruth_trigger<MCTruth_trigger.size(); it_MCTruth_trigger++){

    TString this_MCTruth_trigger = MCTruth_trigger.at(it_MCTruth_trigger);
    
    for(unsigned int it_MC_sample_MCTruth=0; it_MC_sample_MCTruth<MC_sample_MCTruth.size(); it_MC_sample_MCTruth++){
    
      TString this_MC_sample_MCTruth = MC_sample_MCTruth.at(it_MC_sample_MCTruth);
      
      //==== 2D
      
      TH2F *large_2D, *small_2D;

      //==== FR for each significanve region
      //==== and save FR for SF
      for(unsigned int it_sig_region=0; it_sig_region<sig_region.size(); it_sig_region++){
        TH2F* hist_num = (TH2F*)map_string_to_file[this_MC_sample_MCTruth]->Get(this_MCTruth_trigger+"_MCTruth_"+sig_region.at(it_sig_region)+"events_F");
        TH2F* hist_den = (TH2F*)map_string_to_file[this_MC_sample_MCTruth]->Get(this_MCTruth_trigger+"_MCTruth_"+sig_region.at(it_sig_region)+"events_F0");
        if( !hist_num || !hist_den ) continue;
        hist_num->Divide(hist_den);
        if(sig_region.at(it_sig_region)=="HighdXY_") large_2D = (TH2F*)hist_num->Clone();
        if(sig_region.at(it_sig_region)=="")         small_2D = (TH2F*)hist_num->Clone();
        TCanvas* c_MCTruth = new TCanvas("c_MCTruth", "", 1600, 1100);
        //canvas_margin(c_MCTruth);
        c_MCTruth->SetLeftMargin(0.07);
        c_MCTruth->SetRightMargin( 0.1 );
        gStyle->SetPaintTextFormat("0.4f");
        c_MCTruth->cd();
        hist_num->Draw("coltexte1");
        hist_num->GetXaxis()->SetRangeUser(10, 60);
        hist_num->SetXTitle("p_{T} [GeV]");
        hist_num->SetYTitle("|#eta|");
        hist_num->SetTitle("");
        TString histname_suffix("");
        if(sig_region.at(it_sig_region) == "HighdXY_") histname_suffix = "Large";
        if(sig_region.at(it_sig_region) == "") histname_suffix = "Small";
        c_MCTruth->SaveAs(plotpath+"/2D_fakerate_MCTruth_"+this_MCTruth_trigger+"_"+this_MC_sample_MCTruth+"_"+histname_suffix+".png");
        c_MCTruth->Close();
        delete c_MCTruth;
      }
      
      //==== draw 2D SF
      TCanvas* c_2D_FR_SF = new TCanvas("c_2D_FR_SF", "", 1600, 1100);
      //canvas_margin(c_2D_FR_SF);
      c_2D_FR_SF->SetLeftMargin(0.07);
      c_2D_FR_SF->SetRightMargin( 0.1 );
      gStyle->SetPaintTextFormat("0.4f");
      c_2D_FR_SF->cd();
      small_2D->Divide(large_2D);
      small_2D->Draw("coltexte1");
      small_2D->GetXaxis()->SetRangeUser(10, 60);
      small_2D->SetXTitle("p_{T} [GeV]");
      small_2D->SetYTitle("|#eta|");
      small_2D->SetTitle("");
      c_2D_FR_SF->SaveAs(plotpath+"/2D_fakerate_MCTruth_"+this_MCTruth_trigger+"_"+this_MC_sample_MCTruth+"_SF.png");
      c_2D_FR_SF->Close();
      delete c_2D_FR_SF;
      
      //==== draw SF curve for each eta region
      TCanvas *c_2D_SF_curve = new TCanvas("c_2D_SF_curve", "", 800, 600);
      //canvas_margin(c_2D_SF_curve);
      c_2D_SF_curve->cd();
      TLegend* lg_SF_curve = new TLegend(0.6, 0.6, 0.9, 0.9);
      lg_SF_curve->SetFillStyle(0);
      lg_SF_curve->SetBorderSize(0);
      TH1D* SF_curve[4];
      double x_bins[8] = {10, 15, 20, 25, 30, 35, 45, 60};
      double y_bins[5] = {0.0, 0.8, 1.479, 2.0, 2.5};
      Color_t colors[4] = {kBlack, kRed, kBlue, kViolet};
      for(int j=0; j<4; j++){
        SF_curve[j] = new TH1D("FR_eta_"+TString::Itoa(j,10), "", 7, x_bins);
        for(int k=0; k<7; k++){
          SF_curve[j]->SetBinContent(k+1, small_2D->GetBinContent(k+1, j+1) );
        }
        SF_curve[j]->SetLineColor(colors[j]);
        SF_curve[j]->Draw("Lsame");
      }
      SF_curve[0]->GetYaxis()->SetRangeUser(0, 10.0);
      lg_SF_curve->AddEntry(SF_curve[0], "0 < |#eta| < 0.8", "l");
      lg_SF_curve->AddEntry(SF_curve[1], "0.8 < |#eta| < 1.479", "l");
      lg_SF_curve->AddEntry(SF_curve[2], "1.479 < |#eta| < 2.0", "l");
      lg_SF_curve->AddEntry(SF_curve[3], "2.0 < |#eta| < 2.5", "l");
      lg_SF_curve->Draw();
      c_2D_SF_curve->SaveAs(plotpath+"/fakerate_MCTruth_"+this_MCTruth_trigger+"_"+this_MC_sample_MCTruth+"_SF_curve.png");
      c_2D_SF_curve->Close();
      delete c_2D_SF_curve;
      
      //==== 1D (pt)
     
      TH1D *large_1D, *small_1D;
      
      //==== FR for each significanve region
      //==== and save FR for SF
      for(unsigned int it_sig_region=0; it_sig_region<sig_region.size(); it_sig_region++){
        TH1D *hist_num_before_rebin = (TH1D*)map_string_to_file[this_MC_sample_MCTruth]->Get(this_MCTruth_trigger+"_MCTruth_"+sig_region.at(it_sig_region)+"pt_F");
        TH1D *hist_den_before_rebin = (TH1D*)map_string_to_file[this_MC_sample_MCTruth]->Get(this_MCTruth_trigger+"_MCTruth_"+sig_region.at(it_sig_region)+"pt_F0");
        if( !hist_num_before_rebin || !hist_den_before_rebin ) continue;
        //==== rebin
        double rebins[] = {0,10,15,20,25,30,35,45,60,80,100,200};
        TH1D *hist_num = (TH1D *)hist_num_before_rebin->Rebin(11, hist_num_before_rebin->GetName(), rebins);
        TH1D *hist_den = (TH1D *)hist_den_before_rebin->Rebin(11, hist_den_before_rebin->GetName(), rebins);
        hist_num->Divide(hist_den);
        if(sig_region.at(it_sig_region)=="HighdXY_") large_1D = (TH1D*)hist_num->Clone();
        if(sig_region.at(it_sig_region)=="")         small_1D = (TH1D*)hist_num->Clone();
        TCanvas* c_MCTruth = new TCanvas("c_MCTruth", "", 1600, 1100);
        //canvas_margin(c_MCTruth);
        c_MCTruth->SetLeftMargin(0.07);
        c_MCTruth->SetRightMargin( 0.1 );
        gStyle->SetPaintTextFormat("0.4f");
        c_MCTruth->cd();
        hist_num->Draw("hist");
        hist_num->GetXaxis()->SetRangeUser(10, 60);
        hist_num->GetYaxis()->SetRangeUser(0, 1.2);
        hist_num->SetXTitle("p_{T} [GeV]");
        hist_num->SetYTitle("|#eta|");
        hist_num->SetTitle("");
        TString histname_suffix("");
        if(sig_region.at(it_sig_region) == "HighdXY_") histname_suffix = "Large";
        if(sig_region.at(it_sig_region) == "")         histname_suffix = "Small";
        c_MCTruth->SaveAs(plotpath+"/1D_pt_fakerate_MCTruth_"+this_MCTruth_trigger+"_"+this_MC_sample_MCTruth+"_"+histname_suffix+".png");
        c_MCTruth->Close();
        delete c_MCTruth;
      }
      
      //==== draw 1D SF
      TCanvas* c_1D_FR_SF = new TCanvas("c_1D_FR_SF", "", 1600, 1100);
      //canvas_margin(c_1D_FR_SF);
      c_1D_FR_SF->SetLeftMargin(0.07);
      c_1D_FR_SF->SetRightMargin( 0.1 );
      gStyle->SetPaintTextFormat("0.4f");
      c_1D_FR_SF->cd();
      small_1D->Divide(large_1D);
      small_1D->Draw("histtext1");
      small_1D->GetXaxis()->SetRangeUser(10, 60);
      small_1D->GetYaxis()->SetRangeUser(0, 3);
      small_1D->SetXTitle("p_{T} [GeV]");
      small_1D->SetTitle("");
      c_1D_FR_SF->SaveAs(plotpath+"/1D_pt_fakerate_MCTruth_"+this_MCTruth_trigger+"_"+this_MC_sample_MCTruth+"_SF.png");
      c_1D_FR_SF->Close();
      delete c_1D_FR_SF;
      
      //==== write rootfile
      TString filename = plotpath+"/13TeV_trimuon_FR_SF_"+this_MCTruth_trigger+"_"+this_MC_sample_MCTruth+".root";
      TFile* file_FR = new TFile(filename, "RECREATE");
      file_FR->cd();
      small_2D->Write();
      small_1D->Write();
      file_FR->Close();
      
      
      
      
    } // END MC sample loop
    
    
  } // END Trigger loop
  


  
}



void make_legend(TLegend *lg, TString MCtype, vector<TH1D*> hists, vector<TString> alias){
  
  for(int i=hists.size()-1; i>=0; i--){
    lg->AddEntry(hists.at(i), alias.at(i), "f");
  }
  /*
	if(MCtype == "SingleMuon"){
		lg->AddEntry(hists.at(4), "Wjets", "f");
		lg->AddEntry(hists.at(3), "DY 50 > m(ll)", "f");
		lg->AddEntry(hists.at(2), "ttbar", "f");
		lg->AddEntry(hists.at(1), "DY 10 < m(ll) < 50","f");
		lg->AddEntry(hists.at(0), "singletop", "f");
	}
	if(MCtype == "DiMuon"){
		lg->AddEntry(hists.at(2), "DY", "f");
		lg->AddEntry(hists.at(1), "ttbar", "f");
		lg->AddEntry(hists.at(0), "VV", "f");
	}
	if(MCtype == "TriMuon"){
		lg->AddEntry(hists.at(0), "VV", "f");
	}
  */
  
}




