#include "canvas_margin.h"
#include "TSystem.h"

void fake_calculator(){

  TH1::SetDefaultSumw2(true);
  TH1::AddDirectory(kFALSE);
  gStyle->SetOptStat(0);

  //=========================
  //==== use dijet topology
  //=========================

  TString dataclass = "dXY_0p01_dZ_0p5/FakeRateCalculator_Prompt_Matching_wider_bin";
  TString cmssw_version = "5_3_20";

  TString plotpath = "./plots/"+dataclass;
  if( !gSystem->mkdir(plotpath, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }

  //==== SingleMuon Trigger bkg MC list
  //====                                          0           1           2          3           4         5
  vector<TString> MC_sample_SingleMuonTrig = {"Wgamma", "singletop", "DY10to50", "ttbarMS", "DY50plus", "Wjets"}; //FIXME add QCD here
  vector<Color_t> MC_color_SingleMuonTrig = {kOrange, kViolet, kYellow, kBlue, kGreen, kRed-6};
  
  //==== Impact Parameter distributions //FIXME I think MC should be added more
  vector<TString> var = {"LooseIsoMuon_dXY", "TightIsoMuon_dXY"};
  for(unsigned int i=0; i<var.size(); i++){
    
    TFile* file_data = new TFile("./rootfiles/"+dataclass+"/FakeRateCalculator_Mu_data_SKmuon_"+cmssw_version+".root");
    TH1F* data = (TH1F*)file_data->Get(var.at(i)); data->SetMarkerStyle(2); data->SetMarkerColor(kBlue);
    THStack* MC_stack = new THStack("MC_stack", "");
    
    vector<TH1F*> MChist_for_legend;
    MChist_for_legend.clear();
    
    for(unsigned int j=0; j<MC_sample_SingleMuonTrig.size(); j++){
      TFile* file_MC = new TFile("./rootfiles/"+dataclass+"/FakeRateCalculator_Mu_SK"+MC_sample_SingleMuonTrig.at(j)+"_"+cmssw_version+".root");
      TH1F* MC_temp = (TH1F*)file_MC->Get(var.at(i)); MC_temp->SetFillColor( MC_color_SingleMuonTrig.at(j) ); MC_temp->SetLineColor( MC_color_SingleMuonTrig.at(j) );
      MC_stack->Add(MC_temp);
      MChist_for_legend.push_back( (TH1F*)MC_temp->Clone() );
      //file_MC->Close();
      //delete file_MC;
    }
    
    //==== legend
    TLegend* lg = new TLegend(0.6, 0.6, 0.9, 0.9);
    lg->SetFillStyle(0);
    lg->SetBorderSize(0);
    lg->AddEntry(data, "Data", "p");
    lg->AddEntry(MChist_for_legend.at(5), "Wjets", "f");
    lg->AddEntry(MChist_for_legend.at(4), "DY 50 > m(ll)", "f");
    lg->AddEntry(MChist_for_legend.at(3), "ttbar", "f");
    lg->AddEntry(MChist_for_legend.at(2), "DY 10 < m(ll) < 50","f");
    lg->AddEntry(MChist_for_legend.at(1), "singletop", "f");
    lg->AddEntry(MChist_for_legend.at(0), "W#gamma", "f");
    
    //==== draw
    TCanvas* c1 = new TCanvas("c1", "", 800, 600);
    canvas_margin(c1);
    c1->cd();
    gPad->SetLogy();
    //==== MC
    MC_stack->Draw("hist");
    MC_stack->GetXaxis()->SetTitle("dXY [cm]");
    MC_stack->GetYaxis()->SetTitle("Events");
    MC_stack->SetTitle(var.at(i));
    MC_stack->SetMaximum(1000000);
    MC_stack->SetMinimum(0.1);
    //==== data
    data->Draw("psame");
    lg->Draw();
    c1->SaveAs(plotpath+"/"+var.at(i)+".png");
    c1->Close();
    delete c1;
    
    file_data->Close();
    delete file_data;
    
  }
  
  //==== Num/Den for SingleMuon Trigger
  vector<TString> var_1d_SingleMuon = {"pt", "eta", "HT_loose", "HighdXY_pt", "HighdXY_eta"};
  vector<TString> x_title_1d_SingleMuon = {"p_{T} [GeV]", "|#eta|", "HT [GeV]", "p_{T} [GeV]", "|#eta|"};
  for(unsigned int i=0; i<var_1d_SingleMuon.size(); i++){
    
    TFile* file_data = new TFile("./rootfiles/"+dataclass+"/FakeRateCalculator_Mu_data_SKmuon_"+cmssw_version+".root");
    TH1F* num_data = (TH1F*)file_data->Get(var_1d_SingleMuon.at(i)+"_F"); num_data->SetMarkerStyle(2); num_data->SetMarkerColor(kBlue);
    TH1F* den_data = (TH1F*)file_data->Get(var_1d_SingleMuon.at(i)+"_F0"); den_data->SetMarkerStyle(2); den_data->SetMarkerColor(kBlue);
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
    
    for(unsigned int j=0; j<MC_sample_SingleMuonTrig.size(); j++){
      TFile* file_MC = new TFile("./rootfiles/"+dataclass+"/FakeRateCalculator_Mu_SK"+MC_sample_SingleMuonTrig.at(j)+"_"+cmssw_version+".root");
      TH1F* num_MC_temp = (TH1F*)file_MC->Get(var_1d_SingleMuon.at(i)+"_F");
      TH1F* den_MC_temp = (TH1F*)file_MC->Get(var_1d_SingleMuon.at(i)+"_F0");
      if( !num_MC_temp || !den_MC_temp ){
        cout << "No Histogram : " << MC_sample_SingleMuonTrig.at(j) << endl;
        continue;
      }
      else{
        num_MC_temp->SetFillColor( MC_color_SingleMuonTrig.at(j) );
        num_MC_temp->SetLineColor( MC_color_SingleMuonTrig.at(j) );
        den_MC_temp->SetFillColor( MC_color_SingleMuonTrig.at(j) );
        den_MC_temp->SetLineColor( MC_color_SingleMuonTrig.at(j) );
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
    if(var_1d_SingleMuon.at(i).Contains("pt") || var_1d_SingleMuon.at(i)=="HighdXY_eta") gPad->SetLogy();
    //==== MC
    num_MC_stack->Draw("hist");
    num_MC_stack->GetXaxis()->SetTitle(x_title_1d_SingleMuon.at(i));
    num_MC_stack->GetYaxis()->SetTitle("Events");
    num_MC_stack->SetTitle("Numerator, "+var_1d_SingleMuon.at(i));
    if(var_1d_SingleMuon.at(i)=="pt"){
      num_MC_stack->SetMaximum(10000);
      num_MC_stack->SetMinimum(1);
    }
    if(var_1d_SingleMuon.at(i)=="eta"){
      num_MC_stack->SetMaximum(6000);
      num_MC_stack->SetMinimum(0);
    }
    if(var_1d_SingleMuon.at(i)=="HighdXY_pt"){
      num_MC_stack->SetMaximum(10000);
      num_MC_stack->SetMinimum(0.1);
    }
    if(var_1d_SingleMuon.at(i)=="HighdXY_eta"){
      num_MC_stack->SetMaximum(100000);
      num_MC_stack->SetMinimum(0.1);
    }
    if(var_1d_SingleMuon.at(i)=="HT_loose"){
      num_MC_stack->SetMaximum(3000);
      num_MC_stack->SetMinimum(0);
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
    if(var_1d_SingleMuon.at(i).Contains("pt") || var_1d_SingleMuon.at(i)=="HighdXY_eta") gPad->SetLogy();
    //==== MC
    den_MC_stack->Draw("hist");
    den_MC_stack->GetXaxis()->SetTitle(x_title_1d_SingleMuon.at(i));
    den_MC_stack->GetYaxis()->SetTitle("Events");
    den_MC_stack->SetTitle("Denominator, "+var_1d_SingleMuon.at(i));
    if(var_1d_SingleMuon.at(i)=="pt"){
      den_MC_stack->SetMaximum(10000);
      den_MC_stack->SetMinimum(1);
    }
    if(var_1d_SingleMuon.at(i)=="eta"){
      den_MC_stack->SetMaximum(6000);
      den_MC_stack->SetMinimum(0);
    }
    if(var_1d_SingleMuon.at(i)=="HighdXY_pt"){
      den_MC_stack->SetMaximum(10000);
      den_MC_stack->SetMinimum(0.1);
    }
    if(var_1d_SingleMuon.at(i)=="HighdXY_eta"){
      den_MC_stack->SetMaximum(100000);
      den_MC_stack->SetMinimum(0.1);
    }
    if(var_1d_SingleMuon.at(i)=="HT_loose"){
      den_MC_stack->SetMaximum(3000);
      den_MC_stack->SetMinimum(0);
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
  vector<TString> FR_2d_SingleMuon = {"", "HighdXY_"};
  for(unsigned int i=0; i<FR_2d_SingleMuon.size(); i++){
    TFile* file_data = new TFile("./rootfiles/"+dataclass+"/FakeRateCalculator_Mu_data_SKmuon_"+cmssw_version+".root");
    TH2F* num_data_raw = (TH2F*)file_data->Get(FR_2d_SingleMuon.at(i)+"events_F");
    TH2F* den_data_raw = (TH2F*)file_data->Get(FR_2d_SingleMuon.at(i)+"events_F0");
    TH2F* num_data = (TH2F*)num_data_raw->Clone();
    TH2F* den_data = (TH2F*)den_data_raw->Clone();
    
    for(unsigned int j=0; j<MC_sample_SingleMuonTrig.size(); j++){
      TFile* file_MC = new TFile("./rootfiles/"+dataclass+"/FakeRateCalculator_Mu_SK"+MC_sample_SingleMuonTrig.at(j)+"_"+cmssw_version+".root");
      TH2F* num_MC_temp = (TH2F*)file_MC->Get(FR_2d_SingleMuon.at(i)+"events_F");
      TH2F* den_MC_temp = (TH2F*)file_MC->Get(FR_2d_SingleMuon.at(i)+"events_F0");
      num_data->Add(num_MC_temp, -1.);
      den_data->Add(den_MC_temp, -1.);
      file_MC->Close();
      delete file_MC;
    }
    
    //==== 10-15 GeV bin
    int n_xbins = num_data->GetXaxis()->GetNbins();
    int n_ybins = num_data->GetYaxis()->GetNbins();
    TFile* file_low_pT = new TFile("./rootfiles/"+dataclass+"/FakeRateCalculator_Mu_periodD_SKmuon_lowpt_5_3_20.root");
    TH2F* num_data_low_pT = (TH2F*)file_low_pT->Get(FR_2d_SingleMuon.at(i)+"events_F");
    TH2F* den_data_low_pT = (TH2F*)file_low_pT->Get(FR_2d_SingleMuon.at(i)+"events_F0");
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
    c_raw->SaveAs(plotpath+"/fakerate_"+FR_2d_SingleMuon.at(i)+"before_Prompt_subtraction.png");
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
    c_FR->SaveAs(plotpath+"/fakerate_"+FR_2d_SingleMuon.at(i)+"after_Prompt_subtraction.png");
    c_FR->Close();
    delete c_FR;
    //==== write rootfile
    TString filename = plotpath+"/8TeV_trimuon_FR_dijet_topology.root";
    if(FR_2d_SingleMuon.at(i) == "HighdXY_") filename = plotpath+"/8TeV_trimuon_FR_HighdXY.root";
    TFile* file_FR = new TFile(filename, "RECREATE");
    file_FR->cd();
    num_data->Write();
    //==== Edge bin numbers
    TH1I* hist_bins = new TH1I("hist_bins", "", 2, 0, 2);
    hist_bins->SetBinContent(1, 7); // pt : 10-15-20-25-30-35-45-60
    hist_bins->SetBinContent(2, 4); // eta : 0.0-0.8-1.479-2.0-2.5
    hist_bins->Write();
    
    file_FR->Close();
    delete file_FR;
    file_data->Close();
    delete file_data;
    file_low_pT->Close();
    delete file_low_pT;
    
  }
  
  //==== DiMuon Trigger bkg MC list
  //====                                    0     1        2           3          4
  vector<TString> MC_sample_DiMuonTrig = {"VV", "Zbb", "ttbarMS", "DY10to50", "DY50plus"}; //FIXME add QCD here
  vector<Color_t> MC_color_DiMuonTrig = {kGray, kYellow, kBlue, kGreen, kGreen};
  
  //==== Num/Den for DiMuon Trigger
  vector<TString> var_1d_DiMuon = {"DiMuon_HighdXY_pt", "DiMuon_HighdXY_eta"};
  vector<TString> x_title_1d_DiMuon = {"p_{T} [GeV]", "|#eta|"};
  for(unsigned int i=0; i<var_1d_DiMuon.size(); i++){
    
    TFile* file_data = new TFile("./rootfiles/"+dataclass+"/FakeRateCalculator_Mu_data_SKmuon_"+cmssw_version+".root");
    TH1F* num_data = (TH1F*)file_data->Get(var_1d_DiMuon.at(i)+"_F"); num_data->SetMarkerStyle(2); num_data->SetMarkerColor(kBlue);
    TH1F* den_data = (TH1F*)file_data->Get(var_1d_DiMuon.at(i)+"_F0"); den_data->SetMarkerStyle(2); den_data->SetMarkerColor(kBlue);
    cout << "[Data]" << endl;
    cout << " Numerator   : " << num_data->Integral() << endl;
    cout << " Denominator : " << den_data->Integral() << endl;
    THStack* num_MC_stack = new THStack("num_MC_stack", "");
    THStack* den_MC_stack = new THStack("den_MC_stack", "");
    
    if(var_1d_DiMuon.at(i).Contains("pt")){
      num_data->Rebin(5);
      den_data->Rebin(5);
    }
    if(var_1d_DiMuon.at(i).Contains("HT")){
      num_data->Rebin(10);
      den_data->Rebin(10);
    }
    
    vector<TH1F*> MChist_for_legend;
    MChist_for_legend.clear();
    
    for(unsigned int j=0; j<MC_sample_DiMuonTrig.size(); j++){
      cout << "[" << MC_sample_DiMuonTrig.at(j) << "]" << endl;
      TFile* file_MC = new TFile("./rootfiles/"+dataclass+"/FakeRateCalculator_Mu_SK"+MC_sample_DiMuonTrig.at(j)+"_"+cmssw_version+".root");
      TH1F* num_MC_temp = (TH1F*)file_MC->Get(var_1d_DiMuon.at(i)+"_F");
      TH1F* den_MC_temp = (TH1F*)file_MC->Get(var_1d_DiMuon.at(i)+"_F0");
      cout << " Numerator   : " << num_MC_temp->Integral() << endl;
      cout << " Denominator : " << den_MC_temp->Integral() << endl;
      if( !num_MC_temp || !den_MC_temp ){
        cout << "No Histogram : " << MC_sample_DiMuonTrig.at(j) << endl;
        continue;
      }
      else{
        num_MC_temp->SetFillColor( MC_color_DiMuonTrig.at(j) );
        num_MC_temp->SetLineColor( MC_color_DiMuonTrig.at(j) );
        den_MC_temp->SetFillColor( MC_color_DiMuonTrig.at(j) );
        den_MC_temp->SetLineColor( MC_color_DiMuonTrig.at(j) );
      }
      if(var_1d_DiMuon.at(i).Contains("pt")){
        num_MC_temp->Rebin(5);
        den_MC_temp->Rebin(5);
      }
      if(var_1d_DiMuon.at(i).Contains("HT")){
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
    if(var_1d_DiMuon.at(i)=="DiMuon_HighdXY_pt"){
      num_MC_stack->SetMaximum(1000000);
      num_MC_stack->SetMinimum(0.1);
    }
    if(var_1d_DiMuon.at(i)=="DiMuon_HighdXY_eta"){
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
    if(var_1d_DiMuon.at(i)=="DiMuon_HighdXY_pt"){
      den_MC_stack->SetMaximum(1000000);
      den_MC_stack->SetMinimum(1);
    }
    if(var_1d_DiMuon.at(i)=="DiMuon_HighdXY_eta"){
      den_MC_stack->SetMaximum(1000000);
      den_MC_stack->SetMinimum(0.1);
    }
    //==== data
    den_data->Draw("psame");
    lg->Draw();
    c_den->SaveAs(plotpath+"/den_"+var_1d_DiMuon.at(i)+".png");
    c_den->Close();
    delete c_den;
    
    file_data->Close();
    delete file_data;
    
  }

  //==== 2D FR for DiMuon Trigger
  vector<TString> FR_2d_DiMuon = {"DiMuon_HighdXY_"};
  for(unsigned int i=0; i<FR_2d_DiMuon.size(); i++){
    TFile* file_data = new TFile("./rootfiles/"+dataclass+"/FakeRateCalculator_Mu_data_SKmuon_"+cmssw_version+".root");
    TH2F* num_data_raw = (TH2F*)file_data->Get(FR_2d_DiMuon.at(i)+"events_F");
    TH2F* den_data_raw = (TH2F*)file_data->Get(FR_2d_DiMuon.at(i)+"events_F0");
    TH2F* num_data = (TH2F*)num_data_raw->Clone();
    TH2F* den_data = (TH2F*)den_data_raw->Clone();
    
    for(unsigned int j=0; j<MC_sample_DiMuonTrig.size(); j++){
      TFile* file_MC = new TFile("./rootfiles/"+dataclass+"/FakeRateCalculator_Mu_SK"+MC_sample_DiMuonTrig.at(j)+"_"+cmssw_version+".root");
      TH2F* num_MC_temp = (TH2F*)file_MC->Get(FR_2d_DiMuon.at(i)+"events_F");
      TH2F* den_MC_temp = (TH2F*)file_MC->Get(FR_2d_DiMuon.at(i)+"events_F0");
      num_data->Add(num_MC_temp, -1.);
      den_data->Add(den_MC_temp, -1.);
      file_MC->Close();
      delete file_MC;
    }
    
    //==== 10-15 GeV bin
    int n_xbins = num_data->GetXaxis()->GetNbins();
    int n_ybins = num_data->GetYaxis()->GetNbins();
    TFile* file_low_pT = new TFile("./rootfiles/"+dataclass+"/FakeRateCalculator_Mu_periodD_SKmuon_lowpt_5_3_20.root");
    TH2F* num_data_low_pT = (TH2F*)file_low_pT->Get(FR_2d_DiMuon.at(i)+"events_F");
    TH2F* den_data_low_pT = (TH2F*)file_low_pT->Get(FR_2d_DiMuon.at(i)+"events_F0");
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
    c_raw->SaveAs(plotpath+"/fakerate_"+FR_2d_DiMuon.at(i)+"before_Prompt_subtraction.png");
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
    num_data->SetBinContent(6, 3, num_data_raw->GetBinContent(6, 3) );
    num_data->SetBinError(6, 3, num_data_raw->GetBinError(6, 3) );
    num_data->SetBinContent(7, 3, num_data_raw->GetBinContent(7, 3) );
    num_data->SetBinError(7, 3, num_data_raw->GetBinError(7, 3) );
    
    c_FR->SaveAs(plotpath+"/fakerate_"+FR_2d_DiMuon.at(i)+"after_Prompt_subtraction.png");
    c_FR->Close();
    delete c_FR;
    //==== write rootfile
    TString filename = plotpath+"/8TeV_trimuon_FR_DiMuon_HighdXY.root";
    TFile* file_FR = new TFile(filename, "RECREATE");
    file_FR->cd();
    num_data->Write();
    //==== Edge bin numbers
    TH1I* hist_bins = new TH1I("hist_bins", "", 2, 0, 2);
    hist_bins->SetBinContent(1, 7); // pt : 10-15-20-25-30-35-45-60
    hist_bins->SetBinContent(2, 3); // eta : 0.0-0.8-1.479-2.5
    hist_bins->Write();
    
    file_FR->Close();
    delete file_FR;
    file_data->Close();
    delete file_data;
    file_low_pT->Close();
    delete file_low_pT;
    
  }
  
/*
  /////////////////
  // use MCTruth //
  /////////////////

  TFile* file = new TFile("./rootfiles/FakeRateCalculator/MCTruth/FakeRateCalculator_Mu_SKttbar_central_"+cmssw_version+".root");

  vector<TString> var = {"HT", "eta", "pt", "n_jets"};

  for(unsigned int i=0; i<var.size(); i++){

    TH1F* hist_num = (TH1F*)file->Get(var.at(i)+"_num");
    TH1F* hist_den = (TH1F*)file->Get(var.at(i)+"_den");
 
    TCanvas* c1 = new TCanvas("c1_"+var.at(i), "", 800, 600);
    c1->cd();
    canvas_margin(c1);
    hist_den->Draw();
    hist_num->SetLineColor(kRed);
    hist_num->Draw("same");
    c1->SaveAs("./plots/FakeRateCalculator/MCTruth/"+var.at(i)+".png");
    c1->Close();

    TCanvas* c2 = new TCanvas("c2_"+var.at(i), "", 800, 600);
    c2->cd();
    canvas_margin(c2);
    hist_num->Divide(hist_den);
    hist_num->Draw();
    hist_num->SetYTitle("FR");
    hist_num->GetYaxis()->SetRangeUser(0, 1.2);
    c2->SaveAs("./plots/FakeRateCalculator/MCTruth/FR_"+var.at(i)+".png");
    c2->Close();

    delete c1;
    delete c2;
    delete hist_num;
    delete hist_den;
  }

  TCanvas* c_2d = new TCanvas("c_2d", "", 1600, 1100);
  canvas_margin(c_2d);
  c_2d->SetLeftMargin(0.07);
  c_2d->SetRightMargin( 0.1 );
  gStyle->SetPaintTextFormat("0.4f");

  TH2F* hist_2d_num = (TH2F*)file->Get("events_num");
  TH2F* hist_2d_den = (TH2F*)file->Get("events_den");

  hist_2d_num->Divide(hist_2d_den);
  hist_2d_num->GetXaxis()->SetRangeUser(10, 60);
  hist_2d_num->Draw("colztexte1");
  c_2d->SaveAs("./plots/FakeRateCalculator/MCTruth/fakerate.png");
  TFile* file_FR = new TFile("./plots/FakeRateCalculator/MCTruth/8TeV_trimuon_FR_MCTruth_ttbar.root", "RECREATE");
  file_FR->cd();
  hist_2d_num->Write();
  file_FR->Close();
*/  
  



}
