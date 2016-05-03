#include "canvas_margin.h"
#include "TSystem.h"

void fake_calculator(){

  TH1::SetDefaultSumw2(true);
  gStyle->SetOptStat(0);
  

  ////////////////////////
  // use dijet topology //
  ////////////////////////


  TString jetsel = "loose";
  TString dataclass = "dXY_0p01_dZ_0p5";
  TString cmssw_version = "5_3_20";

  TFile* file_data = new TFile("./rootfiles/"+dataclass+"/FakeRateCalculator/dijet_topology/FakeRateCalculator_Mu_data_SKmuon_"+cmssw_version+".root");
  TString plotpath = "./plots/"+dataclass+"/fake_calculator/dijet_topology";
  if( !gSystem->mkdir(plotpath, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }



  TH1F* num_data_pt = (TH1F*)file_data->Get("pt_F"); num_data_pt->SetMarkerStyle(2); num_data_pt->SetMarkerColor(kBlue);
  TH1F* num_data_eta = (TH1F*)file_data->Get("eta_F"); num_data_eta->SetMarkerStyle(2); num_data_eta->SetMarkerColor(kBlue);
  TH1F* num_data_HT = (TH1F*)file_data->Get("HT_"+jetsel+"_F"); num_data_HT->SetMarkerStyle(2); num_data_HT->SetMarkerColor(kBlue);
  TH2F* num_data_2d = (TH2F*)file_data->Get("events_F");
  TH1F* num_HighdXY_data_pt = (TH1F*)file_data->Get("HighdXY_pt_F"); num_HighdXY_data_pt->SetMarkerStyle(2); num_HighdXY_data_pt->SetMarkerColor(kBlue);
  TH1F* num_HighdXY_data_eta = (TH1F*)file_data->Get("HighdXY_eta_F"); num_HighdXY_data_eta->SetMarkerStyle(2); num_HighdXY_data_eta->SetMarkerColor(kBlue);
  TH2F* num_HighdXY_data_2d = (TH2F*)file_data->Get("HighdXY_events_F");
  
  TH1F* den_data_pt = (TH1F*)file_data->Get("pt_F0"); den_data_pt->SetMarkerStyle(2); den_data_pt->SetMarkerColor(kBlue);
  TH1F* den_data_eta = (TH1F*)file_data->Get("eta_F0"); den_data_eta->SetMarkerStyle(2); den_data_eta->SetMarkerColor(kBlue);
  TH1F* den_data_HT = (TH1F*)file_data->Get("HT_"+jetsel+"_F0"); den_data_HT->SetMarkerStyle(2); den_data_HT->SetMarkerColor(kBlue);
  TH2F* den_data_2d = (TH2F*)file_data->Get("events_F0");
  TH1F* den_HighdXY_data_pt = (TH1F*)file_data->Get("HighdXY_pt_F0"); den_HighdXY_data_pt->SetMarkerStyle(2); den_HighdXY_data_pt->SetMarkerColor(kBlue);
  TH1F* den_HighdXY_data_eta = (TH1F*)file_data->Get("HighdXY_eta_F0"); den_HighdXY_data_eta->SetMarkerStyle(2); den_HighdXY_data_eta->SetMarkerColor(kBlue);
  TH2F* den_HighdXY_data_2d = (TH2F*)file_data->Get("HighdXY_events_F0");
  
  //vector<TString> MC_sample = {"DY10to50", "DY50plus", "ttbar", "Wjets", "Wgamma", "singletop"};
  //                              0           1           2             3               4         5
  vector<TString> MC_sample = {"Wgamma", "singletop", "DY10to50", "ttbarMS", "DY50plus", "Wjets"}; //FIXME add QCD here
  //vector<Color_t> MC_color = {kYellow, kGreen, kBlue, kRed-6, kOrange, kViolet};
  vector<Color_t> MC_color = {kOrange, kViolet, kYellow, kBlue, kGreen, kRed-6};
  
  const int n_MC = MC_sample.size();
  const int n_MC_prompt = MC_sample.size() - 0; //FIXME
  
  TH1F* num_MC_pt[n_MC];
  TH1F* num_MC_eta[n_MC];
  TH1F* num_MC_HT[n_MC];
  TH2F* num_MC_2d[n_MC];
  TH1F* num_HighdXY_MC_pt[n_MC];
  TH1F* num_HighdXY_MC_eta[n_MC];
  TH2F* num_HighdXY_MC_2d[n_MC];
  THStack* num_MC_stack_pt = new THStack("num_MC_stack_pt", "");
  THStack* num_MC_stack_eta = new THStack("num_MC_stack_eta", "");
  THStack* num_MC_stack_HT = new THStack("num_MC_stack_HT", "");
  THStack* num_HighdXY_MC_stack_pt = new THStack("num_HighdXY_MC_stack_pt", "");
  THStack* num_HighdXY_MC_stack_eta = new THStack("num_HighdXY_MC_stack_eta", "");
  
  TH1F* den_MC_pt[n_MC];
  TH1F* den_MC_eta[n_MC];
  TH1F* den_MC_HT[n_MC];
  TH2F* den_MC_2d[n_MC];
  TH1F* den_HighdXY_MC_pt[n_MC];
  TH1F* den_HighdXY_MC_eta[n_MC];
  TH2F* den_HighdXY_MC_2d[n_MC];
  THStack* den_MC_stack_pt = new THStack("den_MC_stack_pt", "");
  THStack* den_MC_stack_eta = new THStack("den_MC_stack_eta", "");
  THStack* den_MC_stack_HT = new THStack("den_MC_stack_HT", "");
  THStack* den_HighdXY_MC_stack_pt = new THStack("den_HighdXY_MC_stack_pt", "");
  THStack* den_HighdXY_MC_stack_eta = new THStack("den_HighdXY_MC_stack_eta", "");

  for(int i=0; i<n_MC; i++){
    TFile* file = new TFile("./rootfiles/"+dataclass+"/FakeRateCalculator/dijet_topology/FakeRateCalculator_Mu_SK"+MC_sample[i]+"_"+cmssw_version+".root");
    
    num_MC_pt[i] = (TH1F*)file->Get("pt_F"); num_MC_pt[i]->SetFillColor(MC_color[i]); num_MC_pt[i]->SetLineColor(MC_color[i]);
    num_MC_eta[i] = (TH1F*)file->Get("eta_F"); num_MC_eta[i]->SetFillColor(MC_color[i]); num_MC_eta[i]->SetLineColor(MC_color[i]);
    num_MC_HT[i] = (TH1F*)file->Get("HT_"+jetsel+"_F"); num_MC_HT[i]->SetFillColor(MC_color[i]); num_MC_HT[i]->SetLineColor(MC_color[i]);
    num_MC_2d[i] = (TH2F*)file->Get("events_F");
    num_HighdXY_MC_pt[i] = (TH1F*)file->Get("HighdXY_pt_F"); num_HighdXY_MC_pt[i]->SetFillColor(MC_color[i]); num_HighdXY_MC_pt[i]->SetLineColor(MC_color[i]);
    num_HighdXY_MC_eta[i] = (TH1F*)file->Get("HighdXY_eta_F"); num_HighdXY_MC_eta[i]->SetFillColor(MC_color[i]); num_HighdXY_MC_eta[i]->SetLineColor(MC_color[i]);
    num_HighdXY_MC_2d[i] = (TH2F*)file->Get("HighdXY_events_F");
    
    den_MC_pt[i] = (TH1F*)file->Get("pt_F0"); den_MC_pt[i]->SetFillColor(MC_color[i]); den_MC_pt[i]->SetLineColor(MC_color[i]);
    den_MC_eta[i] = (TH1F*)file->Get("eta_F0"); den_MC_eta[i]->SetFillColor(MC_color[i]); den_MC_eta[i]->SetLineColor(MC_color[i]);
    den_MC_HT[i] = (TH1F*)file->Get("HT_"+jetsel+"_F0"); den_MC_HT[i]->SetFillColor(MC_color[i]); den_MC_HT[i]->SetLineColor(MC_color[i]);
    den_MC_2d[i] = (TH2F*)file->Get("events_F0");
    den_HighdXY_MC_pt[i] = (TH1F*)file->Get("HighdXY_pt_F0"); den_HighdXY_MC_pt[i]->SetFillColor(MC_color[i]); den_HighdXY_MC_pt[i]->SetLineColor(MC_color[i]);
    den_HighdXY_MC_eta[i] = (TH1F*)file->Get("HighdXY_eta_F0"); den_HighdXY_MC_eta[i]->SetFillColor(MC_color[i]); den_HighdXY_MC_eta[i]->SetLineColor(MC_color[i]);
    den_HighdXY_MC_2d[i] = (TH2F*)file->Get("HighdXY_events_F0");

    num_MC_stack_pt->Add(num_MC_pt[i]);
    num_MC_stack_eta->Add(num_MC_eta[i]);
    num_MC_stack_HT->Add(num_MC_HT[i]);
    num_HighdXY_MC_stack_pt->Add(num_HighdXY_MC_pt[i]);
    num_HighdXY_MC_stack_eta->Add(num_HighdXY_MC_eta[i]);
    
    den_MC_stack_pt->Add(den_MC_pt[i]);
    den_MC_stack_eta->Add(den_MC_eta[i]);
    den_MC_stack_HT->Add(den_MC_HT[i]);
    den_HighdXY_MC_stack_pt->Add(den_HighdXY_MC_pt[i]);
    den_HighdXY_MC_stack_eta->Add(den_HighdXY_MC_eta[i]);

  }
 
  TLegend* lg = new TLegend(0.6, 0.6, 0.9, 0.9);
  lg->SetFillStyle(0);
  lg->SetBorderSize(0);
  lg->AddEntry(num_data_pt,"Data",  "p");
  lg->AddEntry(num_MC_pt[5], "Wjets", "f");
  lg->AddEntry(num_MC_pt[4], "DY 50 > m(ll)", "f");
  lg->AddEntry(num_MC_pt[3], "ttbar", "f");
  lg->AddEntry(num_MC_pt[2], "DY 10 < m(ll) < 50","f");
  lg->AddEntry(num_MC_pt[1], "singletop", "f");
  lg->AddEntry(num_MC_pt[0], "W#gamma", "f");


  // example of drawing DATA/MC //
  //TCanvas* c_num_pt = new TCanvas("c_num_pt", "", 800, 800);
  //TPad *c_num_pt_up = new TPad("c_num_pt_up", "", 0, 0.25, 1, 1);
  //c_num_pt_up->SetTopMargin( 0.05 ); c_num_pt_up->SetBottomMargin( 0.02 ); c_num_pt_up->SetRightMargin( 0.02 ); c_num_pt_up->SetLeftMargin( 0.1 );
  //TPad *c_num_pt_down = new TPad("c_num_pt_down", "", 0, 0, 1, 0.25);
  //c_num_pt_down->SetTopMargin( 0.03 ); c_num_pt_down->SetBottomMargin( 0.25 ); c_num_pt_down->SetRightMargin( 0.02 ); c_num_pt_down->SetLeftMargin( 0.1 ); c_num_pt_down->SetGridx(); c_num_pt_down->SetGridy();
  //c_num_pt_up->Draw();
  //c_num_pt_down->Draw();
  //c_num_pt_up->cd();
  //c_num_pt_up->SetLogy();
  //up//
  //num_data_pt->GetXaxis()->SetLabelSize(0);
  //num_data_pt->GetYaxis()->SetLabelSize(0.05);
  //num_data_pt->GetYaxis()->SetTitleSize(0.05);
  //num_data_pt->GetYaxis()->SetTitleOffset(1.03);
  //num_data_pt->GetYaxis()->SetTitle("Events"); //FIXME
  //num_data_pt->GetYaxis()->SetTitle("Events / "+TString::Itoa(7,10)+" GeV"); //FIXME
  //num_data_pt->GetYaxis()->SetTitleOffset(1.03);
  //num_data_pt->Rebin(5);
  //num_data_pt->Draw("psame");
  //num_MC_stack_pt->Draw("histsame");
  //lg->Draw();
  //c_num_pt_down->cd();
  //down//
  //TH1F* hist_num_MC_stack_pt = (TH1F*)num_MC_stack_pt->GetStack()->Last()->Clone();
  //TH1F* clone_num_data_pt = (TH1F*)num_data_pt->Clone();
  //clone_num_data_pt->Divide(hist_num_MC_stack_pt);
  //clone_num_data_pt->Draw("PE1same");
  //save//
  //c_num_pt->SaveAs("./plots/fake_calculator/dijet_topology/num_pt.png");
  //c_num_pt->Close();

  TCanvas* c_num_pt = new TCanvas("c_num_pt", "", 800, 600);
  canvas_margin(c_num_pt);
  c_num_pt->cd();
  gPad->SetLogy();
  num_data_pt->Rebin(5);
  num_data_pt->Draw("psame");
  num_data_pt->SetXTitle("p_{T} [GeV]");
  num_data_pt->SetYTitle("Events");
  num_data_pt->SetTitle("Numerator, p_{T}");
  num_MC_stack_pt->Draw("histsame");
  lg->Draw();
  c_num_pt->SaveAs(plotpath+"/num_pt.png");
  c_num_pt->Close();

  TCanvas* c_num_eta = new TCanvas("c_num_eta", "", 800, 600);
  canvas_margin(c_num_eta);
  c_num_eta->cd();
  num_data_eta->Draw("psame");
  num_data_eta->SetXTitle("#eta");
  num_data_eta->SetYTitle("Events");
  num_data_eta->GetYaxis()->SetRangeUser(0, 3000);
  num_data_eta->SetTitle("Numerator, #eta");
  num_MC_stack_eta->Draw("histsame");
  lg->Draw();
  c_num_eta->SaveAs(plotpath+"/num_eta.png");
  c_num_eta->Close();

  TCanvas* c_num_HT = new TCanvas("c_num_HT", "", 800, 600);
  canvas_margin(c_num_HT);
  c_num_HT->cd();
  num_data_HT->Draw("psame");
  num_data_HT->SetXTitle("HT [GeV]");
  num_data_HT->SetYTitle("Events");
  num_data_HT->GetYaxis()->SetRangeUser(0, 5000);
  num_data_HT->SetTitle("Numerator, HT");
  num_MC_stack_HT->Draw("histsame");
  lg->Draw();
  c_num_HT->SaveAs(plotpath+"/num_HT_"+jetsel+".png");
  c_num_HT->Close();

  TCanvas* c_den_pt = new TCanvas("c_den_pt", "", 800, 600);
  canvas_margin(c_den_pt);
  c_den_pt->cd();
  gPad->SetLogy();
  den_data_pt->Rebin(5);
  den_data_pt->Draw("psame");
  den_data_pt->SetXTitle("p_{T} [GeV]");
  den_data_pt->SetYTitle("Events");
  den_data_pt->SetTitle("Denominator, p_{T}");
  den_MC_stack_pt->Draw("histsame");
  lg->Draw();
  c_den_pt->SaveAs(plotpath+"/den_pt.png");
  c_den_pt->Close();

  TCanvas* c_den_eta = new TCanvas("c_den_eta", "", 800, 600);
  c_den_eta->cd();
  canvas_margin(c_den_eta);
  den_data_eta->Draw("psame");
  den_data_eta->SetXTitle("#eta");
  den_data_eta->SetYTitle("Events");
  den_data_eta->GetYaxis()->SetRangeUser(0, 9000);
  den_data_eta->SetTitle("Demominator, #eta");
  den_MC_stack_eta->Draw("histsame");
  lg->Draw();
  c_den_eta->SaveAs(plotpath+"/den_eta.png");
  c_den_eta->Close();

  TCanvas* c_den_HT = new TCanvas("c_den_HT", "", 800, 600);
  canvas_margin(c_den_HT);
  c_den_HT->cd();
  den_data_HT->Draw("psame");
  den_data_HT->SetXTitle("HT [GeV]");
  den_data_HT->SetYTitle("Events");
  den_data_HT->GetYaxis()->SetRangeUser(0, 5000);
  den_data_HT->SetTitle("denerator, HT");
  den_MC_stack_HT->Draw("histsame");
  lg->Draw();
  c_den_HT->SaveAs(plotpath+"/den_HT_"+jetsel+".png");
  c_den_HT->Close();

  TCanvas* c_2d = new TCanvas("c_2d", "", 1600, 1100);
  canvas_margin(c_2d);
  c_2d->SetLeftMargin(0.07);
  c_2d->SetRightMargin( 0.1 );
  gStyle->SetPaintTextFormat("0.4f");
  TH2F* num_2d = (TH2F*)num_data_2d->Clone(); // clone data, and then subtract prompt
  TH2F* den_2d = (TH2F*)den_data_2d->Clone(); // clone data, and then subtract prompt
  // subtract prompt
  for(int i=0; i<n_MC_prompt; i++){
    num_2d->Add(num_MC_2d[i], -1.0);
    den_2d->Add(den_MC_2d[i], -1.0);
  }
  // check negative values
  int n_xbins = num_2d->GetXaxis()->GetNbins();
  int n_ybins = num_2d->GetYaxis()->GetNbins();
  for(int i_x=0; i_x<n_xbins; i_x++){
    for(int i_y=0; i_y<n_ybins; i_y++){
      if(num_2d->GetBinContent(i_x+1, i_y+1) <= 0 || den_2d->GetBinContent(i_x+1, i_y+1) <= 0 ) num_2d->SetBinContent(i_x+1, i_y+1, 0);
    }
  }
  // 10-15 GeV bin
  TFile* file_low_pT = new TFile("./rootfiles/"+dataclass+"/FakeRateCalculator/dijet_topology/FakeRateCalculator_Mu_periodD_SKmuon_lowpt_5_3_20.root");
  TH2F* num_2d_low_pT = (TH2F*)file_low_pT->Get("events_F");
  TH2F* den_2d_low_pT = (TH2F*)file_low_pT->Get("events_F0");
  for(int i_y=0; i_y<n_ybins; i_y++){
    num_2d->SetBinContent(1, i_y+1, num_2d_low_pT->GetBinContent(1, i_y+1) );
    den_2d->SetBinContent(1, i_y+1, den_2d_low_pT->GetBinContent(1, i_y+1) );
    num_2d->SetBinError(1, i_y+1, num_2d_low_pT->GetBinError(1, i_y+1) );
    den_2d->SetBinError(1, i_y+1, den_2d_low_pT->GetBinError(1, i_y+1) );
  }
  // draw
  TH2F* fake_2d = (TH2F*)num_2d->Clone();
  fake_2d->GetXaxis()->SetRangeUser(10, 60);
  fake_2d->Divide(den_2d);
  fake_2d->Draw("colztexte1");
  fake_2d->SetXTitle("p_{T} [GeV]");
  fake_2d->SetYTitle("|#eta|");
  fake_2d->SetTitle("Fake Rate Matrix");
  //c_2d->SaveAs("./plots/fake_calculator/dijet_topology/fakerate_without_subtraction.png");
  c_2d->SaveAs(plotpath+"/fakerate.png");
  TFile* file_FR = new TFile(plotpath+"/8TeV_trimuon_FR_dijet_topology.root", "RECREATE");
  file_FR->cd();
  fake_2d->Write();
  file_FR->Close();
  c_2d->Close();

  TCanvas* c_FR_HT = new TCanvas("c_FR_HT", "", 800, 600);
  c_FR_HT->cd();
  canvas_margin(c_FR_HT);
  //num_data_HT
  //den_data_HT
  TH1F* num_FR_HT = (TH1F*)num_data_HT->Clone();
  TH1F* den_FR_HT = (TH1F*)den_data_HT->Clone();
  for(int i=0; i<n_MC_prompt; i++){
    num_FR_HT->Add(num_MC_HT[i], -1.0);
    den_FR_HT->Add(den_MC_HT[i], -1.0);
  }
  for(int i=0; i<num_FR_HT->GetXaxis()->GetNbins(); i++){
    if( num_FR_HT->GetBinContent(i+1) <= 0 || den_FR_HT->GetBinContent(i+1) <= 0 ) num_FR_HT->SetBinContent(i+1, 0);
  }
  num_FR_HT->Rebin(10);
  den_FR_HT->Rebin(10);
  num_FR_HT->Divide(den_FR_HT);
  num_FR_HT->Draw("hist");
  num_FR_HT->GetYaxis()->SetRangeUser(0, 1.2);
  c_FR_HT->SaveAs(plotpath+"/fakerate_HT_"+jetsel+".png");
  c_FR_HT->Close();
  
  /* HighdXY */
  
  TCanvas* c_num_HighdXY_pt = new TCanvas("c_num_HighdXY_pt", "", 800, 600);
  canvas_margin(c_num_HighdXY_pt);
  c_num_HighdXY_pt->cd();
  gPad->SetLogy();
  num_HighdXY_data_pt->Rebin(5);
  num_HighdXY_data_pt->Draw("psame");
  num_HighdXY_data_pt->SetXTitle("p_{T} [GeV]");
  num_HighdXY_data_pt->SetYTitle("Events");
  num_HighdXY_data_pt->SetTitle("Numerator, p_{T}");
  num_HighdXY_MC_stack_pt->Draw("histsame");
  lg->Draw();
  c_num_HighdXY_pt->SaveAs(plotpath+"/num_HighdXY_pt.png");
  c_num_HighdXY_pt->Close();
  
  TCanvas* c_num_HighdXY_eta = new TCanvas("c_num_HighdXY_eta", "", 800, 600);
  canvas_margin(c_num_HighdXY_eta);
  c_num_HighdXY_eta->cd();
  num_HighdXY_data_eta->Draw("psame");
  num_HighdXY_data_eta->SetXTitle("#eta");
  num_HighdXY_data_eta->SetYTitle("Events");
  num_HighdXY_data_eta->GetYaxis()->SetRangeUser(0.1, 10000);
  gPad->SetLogy();
  num_HighdXY_data_eta->SetTitle("Numerator, #eta");
  num_HighdXY_MC_stack_eta->Draw("histsame");
  lg->Draw();
  c_num_HighdXY_eta->SaveAs(plotpath+"/num_HighdXY_eta.png");
  c_num_HighdXY_eta->Close();
  
  TCanvas* c_den_HighdXY_pt = new TCanvas("c_den_HighdXY_pt", "", 800, 600);
  canvas_margin(c_den_HighdXY_pt);
  c_den_HighdXY_pt->cd();
  gPad->SetLogy();
  den_HighdXY_data_pt->Rebin(5);
  den_HighdXY_data_pt->Draw("psame");
  den_HighdXY_data_pt->SetXTitle("p_{T} [GeV]");
  den_HighdXY_data_pt->SetYTitle("Events");
  den_HighdXY_data_pt->SetTitle("denerator, p_{T}");
  den_HighdXY_MC_stack_pt->Draw("histsame");
  lg->Draw();
  c_den_HighdXY_pt->SaveAs(plotpath+"/den_HighdXY_pt.png");
  c_den_HighdXY_pt->Close();
  
  TCanvas* c_den_HighdXY_eta = new TCanvas("c_den_HighdXY_eta", "", 800, 600);
  canvas_margin(c_den_HighdXY_eta);
  c_den_HighdXY_eta->cd();
  den_HighdXY_data_eta->Draw("psame");
  den_HighdXY_data_eta->SetXTitle("#eta");
  den_HighdXY_data_eta->SetYTitle("Events");
  den_HighdXY_data_eta->GetYaxis()->SetRangeUser(0.1, 10000);
  gPad->SetLogy();
  den_HighdXY_data_eta->SetTitle("denerator, #eta");
  den_HighdXY_MC_stack_eta->Draw("histsame");
  lg->Draw();
  c_den_HighdXY_eta->SaveAs(plotpath+"/den_HighdXY_eta.png");
  c_den_HighdXY_eta->Close();
  
  TCanvas* c_HighdXY_2d = new TCanvas("c_HighdXY_2d", "", 1600, 1100);
  canvas_margin(c_HighdXY_2d);
  c_HighdXY_2d->SetLeftMargin(0.07);
  c_HighdXY_2d->SetRightMargin( 0.1 );
  gStyle->SetPaintTextFormat("0.4f");
  TH2F* num_HighdXY_2d = (TH2F*)num_HighdXY_data_2d->Clone(); // clone data, and then subtract prompt
  TH2F* den_HighdXY_2d = (TH2F*)den_HighdXY_data_2d->Clone(); // clone data, and then subtract prompt
  // subtract prompt
  for(int i=0; i<n_MC_prompt; i++){
    num_HighdXY_2d->Add(num_HighdXY_MC_2d[i], -1.0);
    den_HighdXY_2d->Add(den_HighdXY_MC_2d[i], -1.0);
  }
  // check negative values
  //int n_xbins = num_HighdXY_2d->GetXaxis()->GetNbins();
  //int n_ybins = num_HighdXY_2d->GetYaxis()->GetNbins();
  for(int i_x=0; i_x<n_xbins; i_x++){
    for(int i_y=0; i_y<n_ybins; i_y++){
      if(num_HighdXY_2d->GetBinContent(i_x+1, i_y+1) <= 0 || den_HighdXY_2d->GetBinContent(i_x+1, i_y+1) <= 0 ) num_HighdXY_2d->SetBinContent(i_x+1, i_y+1, 0);
    }
  }
  // 10-15 GeV bin
  //TFile* file_low_pT = new TFile("./rootfiles/"+dataclass+"/FakeRateCalculator/dijet_topology/FakeRateCalculator_Mu_periodD_SKmuon_lowpt_5_3_20.root");
  TH2F* num_HighdXY_2d_low_pT = (TH2F*)file_low_pT->Get("HighdXY_events_F");
  TH2F* den_HighdXY_2d_low_pT = (TH2F*)file_low_pT->Get("HighdXY_events_F0");
  for(int i_y=0; i_y<n_ybins; i_y++){
    num_HighdXY_2d->SetBinContent(1, i_y+1, num_HighdXY_2d_low_pT->GetBinContent(1, i_y+1) );
    den_HighdXY_2d->SetBinContent(1, i_y+1, den_HighdXY_2d_low_pT->GetBinContent(1, i_y+1) );
    num_HighdXY_2d->SetBinError(1, i_y+1, num_HighdXY_2d_low_pT->GetBinError(1, i_y+1) );
    den_HighdXY_2d->SetBinError(1, i_y+1, den_HighdXY_2d_low_pT->GetBinError(1, i_y+1) );
  }
  // draw
  TH2F* fake_HighdXY_2d = (TH2F*)num_HighdXY_2d->Clone();
  fake_HighdXY_2d->GetXaxis()->SetRangeUser(10, 60);
  fake_HighdXY_2d->Divide(den_HighdXY_2d);
  fake_HighdXY_2d->Draw("colztexte1");
  fake_HighdXY_2d->SetXTitle("p_{T} [GeV]");
  fake_HighdXY_2d->SetYTitle("|#eta|");
  fake_HighdXY_2d->SetTitle("Fake Rate Matrix");
  //c_HighdXY_2d->SaveAs("./plots/fake_calculator/dijet_topology/fakerate_without_subtraction.png");
  c_HighdXY_2d->SaveAs(plotpath+"/HighdXY_fakerate.png");
  TFile* file_HighdXY_FR = new TFile(plotpath+"/8TeV_trimuon_HighdXY_FR.root", "RECREATE");
  file_HighdXY_FR->cd();
  fake_HighdXY_2d->Write();
  file_HighdXY_FR->Close();
  c_HighdXY_2d->Close();
  

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
    c1->SaveAs("./plots/fake_calculator/MCTruth/"+var.at(i)+".png");
    c1->Close();

    TCanvas* c2 = new TCanvas("c2_"+var.at(i), "", 800, 600);
    c2->cd();
    canvas_margin(c2);
    hist_num->Divide(hist_den);
    hist_num->Draw();
    hist_num->SetYTitle("FR");
    hist_num->GetYaxis()->SetRangeUser(0, 1.2);
    c2->SaveAs("./plots/fake_calculator/MCTruth/FR_"+var.at(i)+".png");
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
  c_2d->SaveAs("./plots/fake_calculator/MCTruth/fakerate.png");
  TFile* file_FR = new TFile("./plots/fake_calculator/MCTruth/8TeV_trimuon_FR_MCTruth_ttbar.root", "RECREATE");
  file_FR->cd();
  hist_2d_num->Write();
  file_FR->Close();
*/  
  



}
