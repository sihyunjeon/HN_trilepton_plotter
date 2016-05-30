#include "canvas_margin.h"
#include "TSystem.h"

void fake_calculator(){

  TH1::SetDefaultSumw2(true);
  TH1::AddDirectory(kFALSE);
  gStyle->SetOptStat(0);

  TString dataclass = "dXY_0p01_dZ_0p5_leadpt_20/FakeRateCalculator_Prompt_Matching";
  TString cmssw_version = "5_3_20";

  TString plotpath = "./plots/"+dataclass;
  if( !gSystem->mkdir(plotpath, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }

  //=========================
  //==== SingleMuon Trigger
  //=========================
  
  //==== SingleMuon Trigger bkg MC list
  //====                                          0           1           2          3           4         5
  vector<TString> MC_sample_SingleMuon = {"Wgamma", "singletop", "DY10to50", "ttbarMS", "DY50plus", "Wjets"}; //FIXME add QCD here
  vector<Color_t> MC_color_SingleMuon = {kOrange, kViolet, kYellow, kBlue, kGreen, kRed-6};
  
  //==== LooseMuon study
  vector<TString> var_Loose_study = {"RelIso", "Chi2"};
  for(unsigned int i=0; i<var_Loose_study.size(); i++){
    TFile* file_data = new TFile("./rootfiles/"+dataclass+"/FakeRateCalculator_Mu_data_SKmuon_"+cmssw_version+".root");
    TH1F* hist_data = (TH1F*)file_data->Get("SingleMuon_LooseMuon_"+var_Loose_study.at(i));
    hist_data->SetMarkerStyle(8);
    hist_data->SetMarkerColor(kBlack);
    
    THStack* MC_stack = new THStack("MC_Stack", "");
    
    vector<TH1F*> MChist_for_legend;
    MChist_for_legend.clear();
    
    for(unsigned int j=0; j<MC_sample_SingleMuon.size(); j++){
      TFile* file_MC = new TFile("./rootfiles/"+dataclass+"/FakeRateCalculator_Mu_SK"+MC_sample_SingleMuon.at(j)+"_"+cmssw_version+".root");
      TH1F* MC_temp = (TH1F*)file_MC->Get("SingleMuon_LooseMuon_"+var_Loose_study.at(i));
      
      if( !MC_temp ){
        cout << "No Histogram : " << MC_sample_SingleMuon.at(j) << endl;
        continue;
      }
      else{
        //cout << " Numerator   : " << num_MC_temp->Integral() << endl;
        //cout << " Denominator : " << den_MC_temp->Integral() << endl;
        MC_temp->SetFillColor( MC_color_SingleMuon.at(j) );
        MC_temp->SetLineColor( MC_color_SingleMuon.at(j) );
      }
      
      MChist_for_legend.push_back( (TH1F*)MC_temp->Clone() );
      MC_stack->Add(MC_temp);
      
    }
    
    //==== legend
    TLegend* lg = new TLegend(0.6, 0.6, 0.9, 0.9);
    lg->SetFillStyle(0);
    lg->SetBorderSize(0);
    lg->AddEntry(hist_data, "Data", "p");
    lg->AddEntry(MChist_for_legend.at(5), "Wjets", "f");
    lg->AddEntry(MChist_for_legend.at(4), "DY 50 > m(ll)", "f");
    lg->AddEntry(MChist_for_legend.at(3), "ttbar", "f");
    lg->AddEntry(MChist_for_legend.at(2), "DY 10 < m(ll) < 50","f");
    lg->AddEntry(MChist_for_legend.at(1), "singletop", "f");
    lg->AddEntry(MChist_for_legend.at(0), "W#gamma", "f");
    
    TCanvas* c_Loose_study = new TCanvas("c_Loose_study", "", 800, 600);
    canvas_margin(c_Loose_study);
    c_Loose_study->cd();
    gPad->SetLogy();
    //==== MC
    MC_stack->Draw("hist");
    MC_stack->GetXaxis()->SetTitle(var_Loose_study.at(i));
    MC_stack->GetYaxis()->SetTitle("Events");
    MC_stack->SetTitle("SingleMuon Trigger, LooseMuon : "+var_Loose_study.at(i));
    if(var_Loose_study.at(i) == "RelIso"){
      MC_stack->SetMaximum(1000000);
      MC_stack->SetMinimum(10);
    }
    if(var_Loose_study.at(i) == "Chi2"){
      MC_stack->SetMaximum(1000000);
      MC_stack->SetMinimum(10);
    }
    //==== data
    hist_data->Draw("psame");
    lg->Draw();
    c_Loose_study->SaveAs(plotpath+"/SingleMuonLooseMuon_study_"+var_Loose_study.at(i)+".png");
    c_Loose_study->Close();
    delete c_Loose_study;
    
  }
  
  //==== Num/Den for SingleMuon Trigger
  vector<TString> var_1d_SingleMuon = {
  "Dijet_pt", "Dijet_eta", "Dijet_RelIso", "Dijet_HT_loose",
  "SingleMuon_HighdXY_pt", "SingleMuon_HighdXY_eta", "SingleMuon_HighdXY_RelIso"
  };
  vector<TString> x_title_1d_SingleMuon = {
  "p_{T} [GeV]", "|#eta|", "RelIso", "HT [GeV]",
  "p_{T} [GeV]", "|#eta|", "RelIso"};
  for(unsigned int i=0; i<var_1d_SingleMuon.size(); i++){
    
    TFile* file_data = new TFile("./rootfiles/"+dataclass+"/FakeRateCalculator_Mu_data_SKmuon_"+cmssw_version+".root");
    TH1F* num_data = (TH1F*)file_data->Get(var_1d_SingleMuon.at(i)+"_F"); num_data->SetMarkerStyle(8); num_data->SetMarkerColor(kBlack);
    TH1F* den_data = (TH1F*)file_data->Get(var_1d_SingleMuon.at(i)+"_F0"); den_data->SetMarkerStyle(8); den_data->SetMarkerColor(kBlack);
    THStack* num_MC_stack = new THStack("num_MC_stack", "");
    THStack* den_MC_stack = new THStack("den_MC_stack", "");
    
    if(var_1d_SingleMuon.at(i).Contains("pt")){
      num_data->Rebin(5);
      den_data->Rebin(5);
    }
    if(var_1d_SingleMuon.at(i).Contains("HT")){
      num_data->Rebin(10);
      den_data->Rebin(10);
    }
    
    vector<TH1F*> MChist_for_legend;
    MChist_for_legend.clear();
    
    for(unsigned int j=0; j<MC_sample_SingleMuon.size(); j++){
      TFile* file_MC = new TFile("./rootfiles/"+dataclass+"/FakeRateCalculator_Mu_SK"+MC_sample_SingleMuon.at(j)+"_"+cmssw_version+".root");
      TH1F* num_MC_temp = (TH1F*)file_MC->Get(var_1d_SingleMuon.at(i)+"_F");
      TH1F* den_MC_temp = (TH1F*)file_MC->Get(var_1d_SingleMuon.at(i)+"_F0");
      if( !num_MC_temp || !den_MC_temp ){
        cout << "No Histogram : " << MC_sample_SingleMuon.at(j) << endl;
        continue;
      }
      else{
        num_MC_temp->SetFillColor( MC_color_SingleMuon.at(j) );
        num_MC_temp->SetLineColor( MC_color_SingleMuon.at(j) );
        den_MC_temp->SetFillColor( MC_color_SingleMuon.at(j) );
        den_MC_temp->SetLineColor( MC_color_SingleMuon.at(j) );
      }
      if(var_1d_SingleMuon.at(i).Contains("pt")){
        num_MC_temp->Rebin(5);
        den_MC_temp->Rebin(5);
      }
      if(var_1d_SingleMuon.at(i).Contains("HT")){
        num_MC_temp->Rebin(10);
        den_MC_temp->Rebin(10);
      }
      
      num_MC_stack->Add(num_MC_temp);
      den_MC_stack->Add(den_MC_temp);
      MChist_for_legend.push_back( (TH1F*)num_MC_temp->Clone() );
      //file_MC->Close();
      //delete file_MC;
    }
    
    //==== legend
    TLegend* lg = new TLegend(0.6, 0.6, 0.9, 0.9);
    lg->SetFillStyle(0);
    lg->SetBorderSize(0);
    lg->AddEntry(num_data, "Data", "p");
    lg->AddEntry(MChist_for_legend.at(5), "Wjets", "f");
    lg->AddEntry(MChist_for_legend.at(4), "DY 50 > m(ll)", "f");
    lg->AddEntry(MChist_for_legend.at(3), "ttbar", "f");
    lg->AddEntry(MChist_for_legend.at(2), "DY 10 < m(ll) < 50","f");
    lg->AddEntry(MChist_for_legend.at(1), "singletop", "f");
    lg->AddEntry(MChist_for_legend.at(0), "W#gamma", "f");
    
    //==== draw numerator
    TCanvas* c_num = new TCanvas("c_num", "", 800, 600);
    canvas_margin(c_num);
    c_num->cd();
    if(var_1d_SingleMuon.at(i).Contains("_pt") || var_1d_SingleMuon.at(i).Contains("_eta") || var_1d_SingleMuon.at(i).Contains("_RelIso")) gPad->SetLogy();
    //==== MC
    num_MC_stack->Draw("hist");
    num_MC_stack->GetXaxis()->SetTitle(x_title_1d_SingleMuon.at(i));
    num_MC_stack->GetYaxis()->SetTitle("Events");
    num_MC_stack->SetTitle("Numerator, "+var_1d_SingleMuon.at(i));
    if(var_1d_SingleMuon.at(i)=="Dijet_pt"){
      num_MC_stack->SetMaximum(10000);
      num_MC_stack->SetMinimum(1);
    }
    if(var_1d_SingleMuon.at(i)=="Dijet_eta"){
      num_MC_stack->SetMaximum(6000);
      num_MC_stack->SetMinimum(1);
    }
    if(var_1d_SingleMuon.at(i)=="Dijet_RelIso"){
      num_MC_stack->SetMaximum(1000000);
      num_MC_stack->SetMinimum(10);
    }
    if(var_1d_SingleMuon.at(i)=="Dijet_HT_loose"){
      num_MC_stack->SetMaximum(3000);
      num_MC_stack->SetMinimum(0);
    }
    if(var_1d_SingleMuon.at(i)=="SingleMuon_HighdXY_pt"){
      num_MC_stack->SetMaximum(1000000);
      num_MC_stack->SetMinimum(1);
    }
    if(var_1d_SingleMuon.at(i)=="SingleMuon_HighdXY_eta"){
      num_MC_stack->SetMaximum(1000000);
      num_MC_stack->SetMinimum(1);
    }
    if(var_1d_SingleMuon.at(i)=="SingleMuon_HighdXY_RelIso"){
      num_MC_stack->SetMaximum(1000000);
      num_MC_stack->SetMinimum(1);
    }
    //==== data
    num_data->Draw("psame");
    lg->Draw();
    c_num->SaveAs(plotpath+"/num_"+var_1d_SingleMuon.at(i)+".png");
    c_num->Close();
    delete c_num;
    
    //==== draw denominator
    TCanvas* c_den = new TCanvas("c_den", "", 800, 600);
    canvas_margin(c_den);
    c_den->cd();
    if(var_1d_SingleMuon.at(i).Contains("pt") || var_1d_SingleMuon.at(i).Contains("_eta") || var_1d_SingleMuon.at(i).Contains("_RelIso")) gPad->SetLogy();
    //==== MC
    den_MC_stack->Draw("hist");
    den_MC_stack->GetXaxis()->SetTitle(x_title_1d_SingleMuon.at(i));
    den_MC_stack->GetYaxis()->SetTitle("Events");
    den_MC_stack->SetTitle("Denominator, "+var_1d_SingleMuon.at(i));
    if(var_1d_SingleMuon.at(i)=="Dijet_pt"){
      den_MC_stack->SetMaximum(10000);
      den_MC_stack->SetMinimum(1);
    }
    if(var_1d_SingleMuon.at(i)=="Dijet_eta"){
      den_MC_stack->SetMaximum(6000);
      den_MC_stack->SetMinimum(1);
    }
    if(var_1d_SingleMuon.at(i)=="Dijet_RelIso"){
      den_MC_stack->SetMaximum(1000000);
      den_MC_stack->SetMinimum(10);
    }
    if(var_1d_SingleMuon.at(i)=="Dijet_HT_loose"){
      den_MC_stack->SetMaximum(3000);
      den_MC_stack->SetMinimum(0);
    }
    if(var_1d_SingleMuon.at(i)=="SingleMuon_HighdXY_pt"){
      den_MC_stack->SetMaximum(1000000);
      den_MC_stack->SetMinimum(1);
    }
    if(var_1d_SingleMuon.at(i)=="SingleMuon_HighdXY_eta"){
      den_MC_stack->SetMaximum(1000000);
      den_MC_stack->SetMinimum(1);
    }
    if(var_1d_SingleMuon.at(i)=="SingleMuon_HighdXY_RelIso"){
      den_MC_stack->SetMaximum(1000000);
      den_MC_stack->SetMinimum(1);
    }
    //==== data
    den_data->Draw("psame");
    lg->Draw();
    c_den->SaveAs(plotpath+"/den_"+var_1d_SingleMuon.at(i)+".png");
    c_den->Close();
    delete c_den;
    
    file_data->Close();
    delete file_data;
    
  }
  
  //==== 2D FR for SingleMuon Trigger
  vector<TString> FR_2d_SingleMuon = {"Dijet", "SingleMuon_HighdXY"};
  for(unsigned int i=0; i<FR_2d_SingleMuon.size(); i++){
    TFile* file_data = new TFile("./rootfiles/"+dataclass+"/FakeRateCalculator_Mu_data_SKmuon_"+cmssw_version+".root");
    TH2F* num_data_raw = (TH2F*)file_data->Get(FR_2d_SingleMuon.at(i)+"_events_F");
    TH2F* den_data_raw = (TH2F*)file_data->Get(FR_2d_SingleMuon.at(i)+"_events_F0");
    TH2F* num_data = (TH2F*)num_data_raw->Clone();
    TH2F* den_data = (TH2F*)den_data_raw->Clone();
    
    for(unsigned int j=0; j<MC_sample_SingleMuon.size(); j++){
      TFile* file_MC = new TFile("./rootfiles/"+dataclass+"/FakeRateCalculator_Mu_SK"+MC_sample_SingleMuon.at(j)+"_"+cmssw_version+".root");
      TH2F* num_MC_temp = (TH2F*)file_MC->Get(FR_2d_SingleMuon.at(i)+"_events_F");
      TH2F* den_MC_temp = (TH2F*)file_MC->Get(FR_2d_SingleMuon.at(i)+"_events_F0");
      num_data->Add(num_MC_temp, -1.);
      den_data->Add(den_MC_temp, -1.);
      file_MC->Close();
      delete file_MC;
    }
    
    //==== 10-15 GeV bin
    int n_xbins = num_data->GetXaxis()->GetNbins();
    int n_ybins = num_data->GetYaxis()->GetNbins();
    TFile* file_low_pT = new TFile("./rootfiles/"+dataclass+"/FakeRateCalculator_Mu_periodD_SKmuon_lowpt_5_3_20.root");
    TH2F* num_data_low_pT = (TH2F*)file_low_pT->Get(FR_2d_SingleMuon.at(i)+"_events_F");
    TH2F* den_data_low_pT = (TH2F*)file_low_pT->Get(FR_2d_SingleMuon.at(i)+"_events_F0");
    for(int i_y=0; i_y<n_ybins; i_y++){
      //==== raw
      num_data_raw->SetBinContent(1, i_y+1, num_data_low_pT->GetBinContent(1, i_y+1) );
      den_data_raw->SetBinContent(1, i_y+1, den_data_low_pT->GetBinContent(1, i_y+1) );
      num_data_raw->SetBinError(1, i_y+1, num_data_low_pT->GetBinError(1, i_y+1) );
      den_data_raw->SetBinError(1, i_y+1, den_data_low_pT->GetBinError(1, i_y+1) );
      //==== same for Prompt-subtracted. We assume Prompt is negligible for pT 10-15 GeV bin
      num_data->SetBinContent(1, i_y+1, num_data_low_pT->GetBinContent(1, i_y+1) );
      den_data->SetBinContent(1, i_y+1, den_data_low_pT->GetBinContent(1, i_y+1) );
      num_data->SetBinError(1, i_y+1, num_data_low_pT->GetBinError(1, i_y+1) );
      den_data->SetBinError(1, i_y+1, den_data_low_pT->GetBinError(1, i_y+1) );
    }
    
    TCanvas* c_raw = new TCanvas("c_raw", "", 1600, 1100);
    canvas_margin(c_raw);
    c_raw->SetLeftMargin(0.07);
    c_raw->SetRightMargin( 0.1 );
    gStyle->SetPaintTextFormat("0.4f");
    num_data_raw->Divide(den_data_raw);
    num_data_raw->Draw("colztexte1");
    num_data_raw->GetXaxis()->SetRangeUser(10, 60);
    num_data_raw->SetXTitle("p_{T} [GeV]");
    num_data_raw->SetYTitle("|#eta|");
    num_data_raw->SetTitle("Fake Rate Matrix");
    c_raw->SaveAs(plotpath+"/fakerate_"+FR_2d_SingleMuon.at(i)+"_before_Prompt_subtraction.png");
    c_raw->Close();
    delete c_raw;
    
    TCanvas* c_FR = new TCanvas("c_FR", "", 1600, 1100);
    canvas_margin(c_FR);
    c_FR->SetLeftMargin(0.07);
    c_FR->SetRightMargin( 0.1 );
    gStyle->SetPaintTextFormat("0.4f");
    //==== check negative values
    for(int i_x=0; i_x<n_xbins; i_x++){
      for(int i_y=0; i_y<n_ybins; i_y++){
        if(num_data->GetBinContent(i_x+1, i_y+1) <= 0 || den_data->GetBinContent(i_x+1, i_y+1) <= 0 ) num_data->SetBinContent(i_x+1, i_y+1, 0);
      }
    }
    num_data->Divide(den_data);
    num_data->Draw("colztexte1");
    num_data->GetXaxis()->SetRangeUser(10, 60);
    num_data->SetXTitle("p_{T} [GeV]");
    num_data->SetYTitle("|#eta|");
    num_data->SetTitle("Fake Rate Matrix");
    c_FR->SaveAs(plotpath+"/fakerate_"+FR_2d_SingleMuon.at(i)+"_after_Prompt_subtraction.png");
    c_FR->Close();
    delete c_FR;
    //==== write rootfile
    TString filename = plotpath+"/8TeV_trimuon_FR_"+FR_2d_SingleMuon.at(i)+".root";
    TFile* file_FR = new TFile(filename, "RECREATE");
    file_FR->cd();
    num_data->Write();
    //==== Edge bin numbers
    TH1I* hist_bins = new TH1I("hist_bins", "", 2, 0, 2);
    hist_bins->SetBinContent(1, 7); // pt : 10-15-20-25-30-35-45-60
    hist_bins->SetBinContent(2, 4); // eta : 0.0-0.8-1.479-2.0-2.5
    hist_bins->Write();
    //==== FR curve
    TCanvas *c_FR_curve = new TCanvas("c_FR_curve", "", 800, 600);
    canvas_margin(c_FR_curve);
    c_FR_curve->cd();
    TLegend* lg_FR_curve = new TLegend(0.6, 0.6, 0.9, 0.9);
    lg_FR_curve->SetFillStyle(0);
    lg_FR_curve->SetBorderSize(0);
    TH1F* FR_curve[4];
    double x_bins[8] = {10, 15, 20, 25, 30, 35, 45, 60};
    double y_bins[5] = {0.0, 0.8, 1.479, 2.0, 2.5};
    Color_t colors[4] = {kBlack, kRed, kBlue, kViolet};
    for(int j=0; j<4; j++){
      FR_curve[j] = new TH1F("FR_eta_"+TString::Itoa(j,10), "", 7, x_bins);
      for(int k=0; k<7; k++){
        FR_curve[j]->SetBinContent(k+1, num_data->GetBinContent(k+1, j+1) );
      }
      FR_curve[j]->SetLineColor(colors[j]);
      FR_curve[j]->Draw("Lsame");
    }
    FR_curve[0]->GetYaxis()->SetRangeUser(0, 1.0);
    lg_FR_curve->AddEntry(FR_curve[0], "0 < |#eta| < 0.8", "l");
    lg_FR_curve->AddEntry(FR_curve[1], "0.8 < |#eta| < 1.479", "l");
    lg_FR_curve->AddEntry(FR_curve[2], "1.479 < |#eta| < 2.0", "l");
    lg_FR_curve->AddEntry(FR_curve[3], "2.0 < |#eta| < 2.5", "l");
    lg_FR_curve->Draw();
    c_FR_curve->SaveAs(plotpath+"/FR_curve_"+FR_2d_SingleMuon.at(i)+".png");
    c_FR_curve->Close();
    delete c_FR_curve;
    
    file_FR->Close();
    delete file_FR;
    file_data->Close();
    delete file_data;
    file_low_pT->Close();
    delete file_low_pT;
    
  }
  
  //=====================
  //==== DiMuon Trigger
  //=====================
  
  //==== DiMuon Trigger bkg MC list
  //====                                    0     1        2           3          4
  vector<TString> MC_sample_DiMuonTrig = {"VV", "Zbb", "ttbarMS", "DY10to50", "DY50plus"}; //FIXME add QCD here
  vector<Color_t> MC_color_DiMuonTrig = {kGray, kYellow, kBlue, kGreen, kGreen};
  
  //==== dXY cut optimization plots using DY, ttbar(QCD)
  vector<TString> MuonId = {"Loose", "Tight"};
  vector<TString> var_dXT_cut_study = {"dXY", "dXY_over_dXYErrPat", "dXY_over_D0Err", "dXY_over_dXYErrPat_dXYcut_10mm", "dXY_over_D0Err_dXYcut_10mm"};
  for(unsigned int i=0; i<MuonId.size(); i++){
    for(unsigned int j=0; j<var_dXT_cut_study.size(); j++){
      
      TFile* file_DY10to50 = new TFile("./rootfiles/"+dataclass+"/FakeRateCalculator_Mu_SKDY10to50_"+cmssw_version+".root");
      TFile* file_DY50plus = new TFile("./rootfiles/"+dataclass+"/FakeRateCalculator_Mu_SKDY50plus_"+cmssw_version+".root");
      TFile* file_ttbarMS = new TFile("./rootfiles/"+dataclass+"/FakeRateCalculator_Mu_SKttbarMS_"+cmssw_version+".root");
      TFile* file_QCD_mumu = new TFile("./rootfiles/"+dataclass+"/FakeRateCalculator_Mu_SKQCD_mumu_"+cmssw_version+".root");
      cout << MuonId.at(i)+"IsoMuon_prompt_"+var_dXT_cut_study.at(j) << endl;
      cout << MuonId.at(i)+"IsoMuon_fake_"+var_dXT_cut_study.at(j) << endl;
      TH1F* hist_DY10to50 = (TH1F*)file_DY10to50->Get(MuonId.at(i)+"IsoMuon_prompt_"+var_dXT_cut_study.at(j));
      TH1F* hist_DY50plus = (TH1F*)file_DY50plus->Get(MuonId.at(i)+"IsoMuon_prompt_"+var_dXT_cut_study.at(j));
      TH1F* hist_ttbarMS = (TH1F*)file_ttbarMS->Get(MuonId.at(i)+"IsoMuon_fake_"+var_dXT_cut_study.at(j));
      TH1F* hist_QCD_mumu = (TH1F*)file_QCD_mumu->Get(MuonId.at(i)+"IsoMuon_fake_"+var_dXT_cut_study.at(j));
      
      hist_DY10to50->Add(hist_DY50plus);
      hist_ttbarMS->Add(hist_QCD_mumu);
      
      hist_DY10to50->SetLineColor(kBlack);
      hist_ttbarMS->SetLineColor(kRed);
      
      TLegend* lg_dXY = new TLegend(0.6, 0.6, 0.9, 0.9);
      lg_dXY->SetFillStyle(0);
      lg_dXY->SetBorderSize(0);
      lg_dXY->AddEntry(hist_DY10to50, "Drell-Yan", "l");
      lg_dXY->AddEntry(hist_ttbarMS, "Fake (ttbar+QCD)", "l");
      
      TCanvas* c_dXY = new TCanvas("c_dXY", "", 800, 600);
      canvas_margin(c_dXY);
      c_dXY->cd();
      c_dXY->SetLogy(kTRUE);
      
      hist_DY10to50->DrawNormalized("histsame", 1);
      hist_ttbarMS->DrawNormalized("histsame", 1);
      lg_dXY->Draw();
      c_dXY->SaveAs(plotpath+"/"+MuonId.at(i)+"IsoMuon_"+var_dXT_cut_study.at(j)+".png");
      
      //==== dXY/sigma cut efficiecny
      if(var_dXT_cut_study.at(j).Contains("Err")){
      double dXY_cut[3] = {3., 4., 5.};
        for(int c=0; c<3; c++){
          double eff_prompt = hist_DY10to50->Integral( dXY_cut[c]/0.2 + 1 ,hist_DY10to50->GetXaxis()->GetNbins() ) / hist_DY10to50->Integral();
          double eff_fake   = hist_ttbarMS->Integral( dXY_cut[c]/0.2 + 1  ,hist_ttbarMS->GetXaxis()->GetNbins() ) / hist_ttbarMS->Integral();
          cout
          << "MuonID = " << MuonId.at(i) << endl
          << "Err Type = " << var_dXT_cut_study.at(j) << endl
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
      
      file_DY10to50->Close();
      file_DY50plus->Close();
      file_ttbarMS->Close();
    }
  }
  
  //==== HighdXY LooseMuon (Both Single and Di Muon triggers) study
  vector<TString> trigger = {"SingleMuon", "DiMuon"};
  vector<TString> var_HighdXY_Loose_study = {"RelIso", "Chi2"};
  for(unsigned int i=0; i<var_HighdXY_Loose_study.size(); i++){
    for(unsigned int j=0; j<trigger.size(); j++){
      TFile* file_data = new TFile("./rootfiles/"+dataclass+"/FakeRateCalculator_Mu_data_SKmuon_"+cmssw_version+".root");
      TH1F* hist_data = (TH1F*)file_data->Get(trigger.at(j)+"_HighdXY_LooseMuon_"+var_HighdXY_Loose_study.at(i));
      hist_data->SetMarkerStyle(8);
      hist_data->SetMarkerColor(kBlack);
      
      THStack* MC_stack = new THStack("MC_Stack", "");
      
      vector<TH1F*> MChist_for_legend;
      MChist_for_legend.clear();
      
      TLegend* lg;
      
      if(trigger.at(j) == "SingleMuon"){
        for(unsigned int k=0; k<MC_sample_SingleMuon.size(); k++){
          TFile* file_MC = new TFile("./rootfiles/"+dataclass+"/FakeRateCalculator_Mu_SK"+MC_sample_SingleMuon.at(k)+"_"+cmssw_version+".root");
          TH1F* MC_temp = (TH1F*)file_MC->Get(trigger.at(j)+"_HighdXY_LooseMuon_"+var_HighdXY_Loose_study.at(i));
          
          if( !MC_temp ){
            cout << "No Histogram : " << MC_sample_DiMuonTrig.at(k) << endl;
            continue;
          }
          else{
            //cout << " Numerator   : " << num_MC_temp->Integral() << endl;
            //cout << " Denominator : " << den_MC_temp->Integral() << endl;
            MC_temp->SetFillColor( MC_color_SingleMuon.at(k) );
            MC_temp->SetLineColor( MC_color_SingleMuon.at(k) );
          }
          
          MChist_for_legend.push_back( (TH1F*)MC_temp->Clone() );
          MC_stack->Add(MC_temp);
          
        }
        
        //==== legend
        lg = new TLegend(0.7, 0.6, 0.95, 0.9);
        lg->SetFillStyle(0);
        lg->SetBorderSize(0);
        lg->AddEntry(hist_data, "Data", "p");
        lg->AddEntry(MChist_for_legend.at(5), "Wjets", "f");
        lg->AddEntry(MChist_for_legend.at(4), "DY 50 > m(ll)", "f");
        lg->AddEntry(MChist_for_legend.at(3), "ttbar", "f");
        lg->AddEntry(MChist_for_legend.at(2), "DY 10 < m(ll) < 50","f");
        lg->AddEntry(MChist_for_legend.at(1), "singletop", "f");
        lg->AddEntry(MChist_for_legend.at(0), "W#gamma", "f");
      }
      
      if(trigger.at(j) == "DiMuon"){
        for(unsigned int k=0; k<MC_sample_DiMuonTrig.size(); k++){
          TFile* file_MC = new TFile("./rootfiles/"+dataclass+"/FakeRateCalculator_Mu_SK"+MC_sample_DiMuonTrig.at(k)+"_"+cmssw_version+".root");
          TH1F* MC_temp = (TH1F*)file_MC->Get(trigger.at(j)+"_HighdXY_LooseMuon_"+var_HighdXY_Loose_study.at(i));
          
          if( !MC_temp ){
            cout << "No Histogram : " << MC_sample_DiMuonTrig.at(k) << endl;
            continue;
          }
          else{
            //cout << " Numerator   : " << num_MC_temp->Integral() << endl;
            //cout << " Denominator : " << den_MC_temp->Integral() << endl;
            MC_temp->SetFillColor( MC_color_DiMuonTrig.at(k) );
            MC_temp->SetLineColor( MC_color_DiMuonTrig.at(k) );
          }
          
          MChist_for_legend.push_back( (TH1F*)MC_temp->Clone() );
          MC_stack->Add(MC_temp);
          
        }
        
        //==== legend
        lg = new TLegend(0.7, 0.6, 0.95, 0.9);
        lg->SetFillStyle(0);
        lg->SetBorderSize(0);
        lg->AddEntry(hist_data, "Data", "p");
        lg->AddEntry(MChist_for_legend.at(3), "DY", "f");
        lg->AddEntry(MChist_for_legend.at(2), "ttbar", "f");
        lg->AddEntry(MChist_for_legend.at(1), "Zbb", "f");
        lg->AddEntry(MChist_for_legend.at(0), "VV", "f");
      }
      
      TCanvas* c_HighdXY_Loose_study = new TCanvas("c_HighdXY_Loose_study", "", 800, 600);
      canvas_margin(c_HighdXY_Loose_study);
      c_HighdXY_Loose_study->cd();
      gPad->SetLogy();
      //==== MC
      MC_stack->Draw("hist");
      MC_stack->GetXaxis()->SetTitle(var_HighdXY_Loose_study.at(i));
      MC_stack->GetYaxis()->SetTitle("Events");
      MC_stack->SetTitle(trigger.at(j)+" Trigger, HighdXY LooseMuon : "+var_HighdXY_Loose_study.at(i));
      if(var_HighdXY_Loose_study.at(i) == "RelIso"){
        if(trigger.at(j) == "SingleMuon"){
          MC_stack->SetMaximum(1000000);
          MC_stack->SetMinimum(1);
        }
        else if(trigger.at(j) == "DiMuon"){
          MC_stack->SetMaximum(1000000);
          MC_stack->SetMinimum(1);
        }
      }
      if(var_HighdXY_Loose_study.at(i) == "Chi2"){
        if(trigger.at(j) == "SingleMuon"){
          MC_stack->SetMaximum(1000000);
          MC_stack->SetMinimum(1);
        }
        else if(trigger.at(j) == "DiMuon"){
          MC_stack->SetMaximum(1000000);
          MC_stack->SetMinimum(1);
        }
      }
      //==== data
      hist_data->Draw("psame");
      lg->Draw();
      c_HighdXY_Loose_study->SaveAs(plotpath+"/"+trigger.at(j)+"_HighdXY_LooseMuon_study_"+var_HighdXY_Loose_study.at(i)+".png");
      c_HighdXY_Loose_study->Close();
      delete c_HighdXY_Loose_study;
    }
  }
  
  
  //==== Num/Den for DiMuon Trigger
  vector<TString> var_1d_DiMuon ={
    "DiMuon_HighdXY_pt", "DiMuon_HighdXY_eta", "DiMuon_HighdXY_n_jets", "DiMuon_HighdXY_RelIso",
    "DiMuon_HighdXY_0jet_pt", "DiMuon_HighdXY_0jet_eta", "DiMuon_HighdXY_0jet_n_jets", "DiMuon_HighdXY_0jet_RelIso",
    "DiMuon_HighdXY_withjet_pt", "DiMuon_HighdXY_withjet_eta", "DiMuon_HighdXY_withjet_n_jets", "DiMuon_HighdXY_withjet_RelIso"
  };
  vector<TString> x_title_1d_DiMuon = {
    "p_{T} [GeV]", "|#eta|", "# of jets", "RelIso",
    "p_{T} [GeV]", "|#eta|", "# of jets", "RelIso",
    "p_{T} [GeV]", "|#eta|", "# of jets", "RelIso"
  };
  for(unsigned int i=0; i<var_1d_DiMuon.size(); i++){
    //cout << "./rootfiles/"+dataclass+"/FakeRateCalculator_Mu_data_SKmuon_"+cmssw_version+".root" << endl;
    TFile* file_data = new TFile("./rootfiles/"+dataclass+"/FakeRateCalculator_Mu_data_SKmuon_"+cmssw_version+".root");
    //cout << var_1d_DiMuon.at(i)+"_F" << endl;
    TH1F* num_data = (TH1F*)file_data->Get(var_1d_DiMuon.at(i)+"_F"); num_data->SetMarkerStyle(8); num_data->SetMarkerColor(kBlack);
    TH1F* den_data = (TH1F*)file_data->Get(var_1d_DiMuon.at(i)+"_F0"); den_data->SetMarkerStyle(8); den_data->SetMarkerColor(kBlack);
    //cout << "[Data]" << endl;
    //cout << " Numerator   : " << num_data->Integral() << endl;
    //cout << " Denominator : " << den_data->Integral() << endl;
    THStack* num_MC_stack = new THStack("num_MC_stack", "");
    THStack* den_MC_stack = new THStack("den_MC_stack", "");
    
    if(var_1d_DiMuon.at(i).Contains("pt")){
      num_data->Rebin(5);
      den_data->Rebin(5);
    }
    
    vector<TH1F*> MChist_for_legend;
    MChist_for_legend.clear();
    
    for(unsigned int j=0; j<MC_sample_DiMuonTrig.size(); j++){
      //cout << "[" << MC_sample_DiMuonTrig.at(j) << "]" << endl;
      TFile* file_MC = new TFile("./rootfiles/"+dataclass+"/FakeRateCalculator_Mu_SK"+MC_sample_DiMuonTrig.at(j)+"_"+cmssw_version+".root");
      TH1F* num_MC_temp = (TH1F*)file_MC->Get(var_1d_DiMuon.at(i)+"_F");
      TH1F* den_MC_temp = (TH1F*)file_MC->Get(var_1d_DiMuon.at(i)+"_F0");
      if( !num_MC_temp || !den_MC_temp ){
        cout << "No Histogram : " << MC_sample_DiMuonTrig.at(j) << endl;
        continue;
      }
      else{
        //cout << " Numerator   : " << num_MC_temp->Integral() << endl;
        //cout << " Denominator : " << den_MC_temp->Integral() << endl;
        num_MC_temp->SetFillColor( MC_color_DiMuonTrig.at(j) );
        num_MC_temp->SetLineColor( MC_color_DiMuonTrig.at(j) );
        den_MC_temp->SetFillColor( MC_color_DiMuonTrig.at(j) );
        den_MC_temp->SetLineColor( MC_color_DiMuonTrig.at(j) );
      }
      if(var_1d_DiMuon.at(i).Contains("pt")){
        num_MC_temp->Rebin(5);
        den_MC_temp->Rebin(5);
      }
      
      num_MC_stack->Add(num_MC_temp);
      den_MC_stack->Add(den_MC_temp);
      MChist_for_legend.push_back( (TH1F*)num_MC_temp->Clone() );
      //file_MC->Close();
      //delete file_MC;
    }
    
    //==== legend
    TLegend* lg = new TLegend(0.7, 0.6, 0.95, 0.9);
    lg->SetFillStyle(0);
    lg->SetBorderSize(0);
    lg->AddEntry(num_data, "Data", "p");
    lg->AddEntry(MChist_for_legend.at(3), "DY", "f");
    lg->AddEntry(MChist_for_legend.at(2), "ttbar", "f");
    lg->AddEntry(MChist_for_legend.at(1), "Zbb", "f");
    lg->AddEntry(MChist_for_legend.at(0), "VV", "f");
    
    //==== draw numerator
    TCanvas* c_num = new TCanvas("c_num", "", 800, 600);
    canvas_margin(c_num);
    c_num->cd();
    gPad->SetLogy();
    //==== MC
    num_MC_stack->Draw("hist");
    num_MC_stack->GetXaxis()->SetTitle(x_title_1d_DiMuon.at(i));
    num_MC_stack->GetYaxis()->SetTitle("Events");
    num_MC_stack->SetTitle("Numerator, "+var_1d_DiMuon.at(i));
    if(var_1d_DiMuon.at(i).Contains("_pt")){
      num_MC_stack->SetMaximum(1000000);
      num_MC_stack->SetMinimum(0.1);
    }
    if(var_1d_DiMuon.at(i).Contains("_eta")){
      num_MC_stack->SetMaximum(1000000);
      num_MC_stack->SetMinimum(0.1);
    }
    if(var_1d_DiMuon.at(i).Contains("_RelIso")){
      num_MC_stack->SetMaximum(1000000);
      num_MC_stack->SetMinimum(0.1);
    }
    //==== data
    num_data->Draw("psame");
    lg->Draw();
    c_num->SaveAs(plotpath+"/num_"+var_1d_DiMuon.at(i)+".png");
    c_num->Close();
    delete c_num;
    
    //==== draw denominator
    TCanvas* c_den = new TCanvas("c_den", "", 800, 600);
    canvas_margin(c_den);
    c_den->cd();
    gPad->SetLogy();
    //==== MC
    den_MC_stack->Draw("hist");
    den_MC_stack->GetXaxis()->SetTitle(x_title_1d_DiMuon.at(i));
    den_MC_stack->GetYaxis()->SetTitle("Events");
    den_MC_stack->SetTitle("Denominator, "+var_1d_DiMuon.at(i));
    if(var_1d_DiMuon.at(i).Contains("_pt")){
      den_MC_stack->SetMaximum(1000000);
      den_MC_stack->SetMinimum(1);
    }
    if(var_1d_DiMuon.at(i).Contains("_eta")){
      den_MC_stack->SetMaximum(1000000);
      den_MC_stack->SetMinimum(0.1);
    }
    if(var_1d_DiMuon.at(i).Contains("_RelIso")){
      den_MC_stack->SetMaximum(1000000);
      den_MC_stack->SetMinimum(0.1);
    }
    //==== data
    den_data->Draw("psame");
    lg->Draw();
    c_den->SaveAs(plotpath+"/den_"+var_1d_DiMuon.at(i)+".png");
    c_den->Close();
    delete c_den;
    
    //==== 1D FR
    TCanvas* c_1d_FR = new TCanvas("c_1d_FR", "", 800, 600);
    canvas_margin(c_1d_FR);
    c_1d_FR->cd();
    num_data->Add((TH1F*)num_MC_stack->GetStack()->Last(), -1.);
    den_data->Add((TH1F*)den_MC_stack->GetStack()->Last(), -1.);
    num_data->Divide(den_data);
    num_data->Draw("histe1");
    num_data->GetYaxis()->SetRangeUser(0, 1.2);
    c_1d_FR->SaveAs(plotpath+"/1D_FR_"+var_1d_DiMuon.at(i)+".png");
    c_1d_FR->Close();
    delete c_1d_FR;
    
    file_data->Close();
    delete file_data;
    
  }

  //==== 2D FR for DiMuon Trigger
  vector<TString> FR_2d_DiMuon = {"DiMuon_HighdXY", "DiMuon_HighdXY_0jet", "DiMuon_HighdXY_withjet"};
  for(unsigned int i=0; i<FR_2d_DiMuon.size(); i++){
    TFile* file_data = new TFile("./rootfiles/"+dataclass+"/FakeRateCalculator_Mu_data_SKmuon_"+cmssw_version+".root");
    TH2F* num_data_raw = (TH2F*)file_data->Get(FR_2d_DiMuon.at(i)+"_events_F");
    TH2F* den_data_raw = (TH2F*)file_data->Get(FR_2d_DiMuon.at(i)+"_events_F0");
    TH2F* num_data = (TH2F*)num_data_raw->Clone();
    TH2F* den_data = (TH2F*)den_data_raw->Clone();
    
    for(unsigned int j=0; j<MC_sample_DiMuonTrig.size(); j++){
      TFile* file_MC = new TFile("./rootfiles/"+dataclass+"/FakeRateCalculator_Mu_SK"+MC_sample_DiMuonTrig.at(j)+"_"+cmssw_version+".root");
      TH2F* num_MC_temp = (TH2F*)file_MC->Get(FR_2d_DiMuon.at(i)+"_events_F");
      TH2F* den_MC_temp = (TH2F*)file_MC->Get(FR_2d_DiMuon.at(i)+"_events_F0");
      if( !num_MC_temp || !den_MC_temp ){
        cout << "No histogram : " << MC_sample_DiMuonTrig.at(j) << endl;
        continue;
      }
      num_data->Add(num_MC_temp, -1.);
      den_data->Add(den_MC_temp, -1.);
      file_MC->Close();
      delete file_MC;
    }
    
    //==== 10-15 GeV bin
    int n_xbins = num_data->GetXaxis()->GetNbins();
    int n_ybins = num_data->GetYaxis()->GetNbins();
    TFile* file_low_pT = new TFile("./rootfiles/"+dataclass+"/FakeRateCalculator_Mu_periodD_SKmuon_lowpt_5_3_20.root");
    TH2F* num_data_low_pT = (TH2F*)file_low_pT->Get(FR_2d_DiMuon.at(i)+"_events_F");
    TH2F* den_data_low_pT = (TH2F*)file_low_pT->Get(FR_2d_DiMuon.at(i)+"_events_F0");
    /*
    for(int i_y=0; i_y<n_ybins; i_y++){
      //==== raw
      num_data_raw->SetBinContent(1, i_y+1, num_data_low_pT->GetBinContent(1, i_y+1) );
      den_data_raw->SetBinContent(1, i_y+1, den_data_low_pT->GetBinContent(1, i_y+1) );
      num_data_raw->SetBinError(1, i_y+1, num_data_low_pT->GetBinError(1, i_y+1) );
      den_data_raw->SetBinError(1, i_y+1, den_data_low_pT->GetBinError(1, i_y+1) );
      //==== same for Prompt-subtracted. We assume Prompt is negligible for pT 10-15 GeV bin
      num_data->SetBinContent(1, i_y+1, num_data_low_pT->GetBinContent(1, i_y+1) );
      den_data->SetBinContent(1, i_y+1, den_data_low_pT->GetBinContent(1, i_y+1) );
      num_data->SetBinError(1, i_y+1, num_data_low_pT->GetBinError(1, i_y+1) );
      den_data->SetBinError(1, i_y+1, den_data_low_pT->GetBinError(1, i_y+1) );
    }
    */
    TCanvas* c_raw = new TCanvas("c_raw", "", 1600, 1100);
    canvas_margin(c_raw);
    c_raw->SetLeftMargin(0.07);
    c_raw->SetRightMargin( 0.1 );
    gStyle->SetPaintTextFormat("0.4f");
    num_data_raw->Divide(den_data_raw);
    num_data_raw->Draw("colztexte1");
    num_data_raw->GetXaxis()->SetRangeUser(10, 60);
    num_data_raw->SetXTitle("p_{T} [GeV]");
    num_data_raw->SetYTitle("|#eta|");
    num_data_raw->SetTitle("Fake Rate Matrix");
    c_raw->SaveAs(plotpath+"/fakerate_"+FR_2d_DiMuon.at(i)+"_before_Prompt_subtraction.png");
    c_raw->Close();
    delete c_raw;
    
    TCanvas* c_FR = new TCanvas("c_FR", "", 1600, 1100);
    canvas_margin(c_FR);
    c_FR->SetLeftMargin(0.07);
    c_FR->SetRightMargin( 0.1 );
    gStyle->SetPaintTextFormat("0.4f");
    //==== check negative values
    for(int i_x=0; i_x<n_xbins; i_x++){
      for(int i_y=0; i_y<n_ybins; i_y++){
        if(num_data->GetBinContent(i_x+1, i_y+1) <= 0 || den_data->GetBinContent(i_x+1, i_y+1) <= 0 ) num_data->SetBinContent(i_x+1, i_y+1, 0);
      }
    }
    num_data->Divide(den_data);
    num_data->Draw("colztexte1");
    num_data->GetXaxis()->SetRangeUser(10, 60);
    num_data->SetXTitle("p_{T} [GeV]");
    num_data->SetYTitle("|#eta|");
    num_data->SetTitle("Fake Rate Matrix");
    //==== hot fix
    //num_data->SetBinContent(6, 3, num_data_raw->GetBinContent(6, 3) );
    //num_data->SetBinError(6, 3, num_data_raw->GetBinError(6, 3) );
    //num_data->SetBinContent(7, 3, num_data_raw->GetBinContent(7, 3) );
    //num_data->SetBinError(7, 3, num_data_raw->GetBinError(7, 3) );

    c_FR->SaveAs(plotpath+"/fakerate_"+FR_2d_DiMuon.at(i)+"_after_Prompt_subtraction.png");
    c_FR->Close();
    delete c_FR;
    //==== write rootfile
    TString filename = plotpath+"/8TeV_trimuon_FR_"+FR_2d_DiMuon.at(i)+".root";
    TFile* file_FR = new TFile(filename, "RECREATE");
    file_FR->cd();
    num_data->Write();
    //==== Edge bin numbers
    TH1I* hist_bins = new TH1I("hist_bins", "", 2, 0, 2);
    hist_bins->SetBinContent(1, 7); // pt : 10-15-20-25-30-35-45-60
    hist_bins->SetBinContent(2, 4); // eta : 0.0-0.8-1.479-2.0-2.5
    hist_bins->Write();
    //==== FR curve
    TCanvas *c_FR_curve = new TCanvas("c_FR_curve", "", 800, 600);
    canvas_margin(c_FR_curve);
    c_FR_curve->cd();
    TLegend* lg_FR_curve = new TLegend(0.6, 0.6, 0.9, 0.9);
    lg_FR_curve->SetFillStyle(0);
    lg_FR_curve->SetBorderSize(0);
    TH1F* FR_curve[4];
    double x_bins[8] = {10, 15, 20, 25, 30, 35, 45, 60};
    double y_bins[5] = {0.0, 0.8, 1.479, 2.0, 2.5};;
    Color_t colors[4] = {kBlack, kRed, kBlue, kViolet};
    for(int j=0; j<4; j++){
      FR_curve[j] = new TH1F("FR_eta_"+TString::Itoa(j,10), "", 7, x_bins);
      for(int k=0; k<7; k++){
        FR_curve[j]->SetBinContent(k+1, num_data->GetBinContent(k+1, j+1) );
      }
      FR_curve[j]->SetLineColor(colors[j]);
      FR_curve[j]->Draw("Lsame");
    }
    FR_curve[0]->GetYaxis()->SetRangeUser(0, 1.0);
    lg_FR_curve->AddEntry(FR_curve[0], "0 < |#eta| < 0.8", "l");
    lg_FR_curve->AddEntry(FR_curve[1], "0.8 < |#eta| < 1.479", "l");
    lg_FR_curve->AddEntry(FR_curve[2], "1.479 < |#eta| < 2.0", "l");
    lg_FR_curve->AddEntry(FR_curve[3], "2.0 < |#eta| < 2.5", "l");
    lg_FR_curve->Draw();
    c_FR_curve->SaveAs(plotpath+"/FR_curve_"+FR_2d_DiMuon.at(i)+".png");
    c_FR_curve->Close();
    delete c_FR_curve;
    
    file_FR->Close();
    delete file_FR;
    file_data->Close();
    delete file_data;
    file_low_pT->Close();
    delete file_low_pT;
    
  }
  
  //==============
  //==== MCTruth
  //==============
  
  //==== MC truth to see FR depency of |dXY|/err
  vector<TString> MC_sample_MCTruth = {"QCD_mumu", "ttbarMS"};
  vector<TString> sig_region = {"no_sigcut", "large_sig", "small_sig"};
  
  for(unsigned int i=0; i<MC_sample_MCTruth.size(); i++){
    TFile* file = new TFile("./rootfiles/"+dataclass+"/FakeRateCalculator_Mu_SK"+MC_sample_MCTruth.at(i)+"_"+cmssw_version+".root");
    TH2F *large, *small;
    for(unsigned int j=0; j<sig_region.size(); j++){
      TH2F* hist_num = (TH2F*)file->Get("MCTruth_HighdXY_"+sig_region.at(j)+"_events_F");
      TH2F* hist_den = (TH2F*)file->Get("MCTruth_HighdXY_"+sig_region.at(j)+"_events_F0");
      if( !hist_num || !hist_den ) continue;
      hist_num->Divide(hist_den);
      if(sig_region.at(j)=="large_sig") large = (TH2F*)hist_num->Clone();
      if(sig_region.at(j)=="small_sig") small = (TH2F*)hist_num->Clone();
      TCanvas* c_MCTruth = new TCanvas("c_MCTruth", "", 1600, 1100);
      canvas_margin(c_MCTruth);
      c_MCTruth->SetLeftMargin(0.07);
      c_MCTruth->SetRightMargin( 0.1 );
      gStyle->SetPaintTextFormat("0.4f");
      c_MCTruth->cd();
      hist_num->Draw("coltexte1");
      hist_num->GetXaxis()->SetRangeUser(10, 60);
      hist_num->SetXTitle("p_{T} [GeV]");
      hist_num->SetYTitle("|#eta|");
      hist_num->SetTitle("Fake Rate Matrix");
      c_MCTruth->SaveAs(plotpath+"/fakerate_MCTruth_"+MC_sample_MCTruth.at(i)+"_"+sig_region.at(j)+".png");
      c_MCTruth->Close();
      delete c_MCTruth;
    }
    TCanvas* c_FR_SF = new TCanvas("c_FR_SF", "", 1600, 1100);
    canvas_margin(c_FR_SF);
    c_FR_SF->SetLeftMargin(0.07);
    c_FR_SF->SetRightMargin( 0.1 );
    gStyle->SetPaintTextFormat("0.4f");
    c_FR_SF->cd();
    small->Divide(large);
    small->Draw("coltexte1");
    small->GetXaxis()->SetRangeUser(10, 60);
    small->SetXTitle("p_{T} [GeV]");
    small->SetYTitle("|#eta|");
    small->SetTitle("|dXY|/#sigma < 3 / |dXY|/#sigma > 4");
    c_FR_SF->SaveAs(plotpath+"/fakerate_MCTruth_"+MC_sample_MCTruth.at(i)+"_SF.png");
    c_FR_SF->Close();
    delete c_FR_SF;
  }
  

}
