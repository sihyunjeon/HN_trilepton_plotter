#include "canvas_margin.h"

void fake_calculator(){

  TH1::SetDefaultSumw2(true);

  TFile* file_data = new TFile("./rootfiles/FakeRateCalculator_Mu_data_SKmuon_5_3_14.root");

  TH1F* num_data_pt = (TH1F*)file_data->Get("pt_F"); num_data_pt->SetMarkerStyle(2); num_data_pt->SetMarkerColor(kBlue);
  TH1F* num_data_eta = (TH1F*)file_data->Get("eta_F"); num_data_eta->SetMarkerStyle(2); num_data_eta->SetMarkerColor(kBlue);
  TH2F* num_data_2d = (TH2F*)file_data->Get("events_F");
  TH1F* den_data_pt = (TH1F*)file_data->Get("pt_F0"); den_data_pt->SetMarkerStyle(2); den_data_pt->SetMarkerColor(kBlue);
  TH1F* den_data_eta = (TH1F*)file_data->Get("eta_F0"); den_data_eta->SetMarkerStyle(2); den_data_eta->SetMarkerColor(kBlue);
  TH2F* den_data_2d = (TH2F*)file_data->Get("events_F0");

  //vector<TString> MC_sample = {"DY10to50", "DY50plus", "ttbar", "Wjets", "Wgamma", "singletop"};
  //                              0           1           2             3               4         5
  vector<TString> MC_sample = {"Wgamma", "singletop", "DY10to50", "ttbar_central", "DY50plus", "Wjets"}; //FIXME add QCD here
  //vector<Color_t> MC_color = {kYellow, kGreen, kBlue, kRed-6, kOrange, kViolet};
  vector<Color_t> MC_color = {kOrange, kViolet, kYellow, kBlue, kGreen, kRed-6};
  const int n_MC = MC_sample.size();
  const int n_MC_prompt = MC_sample.size() - 0; //FIXME
  TH1F* num_MC_pt[n_MC];
  TH1F* num_MC_eta[n_MC];
  TH2F* num_MC_2d[n_MC];
  TH1F* den_MC_pt[n_MC];
  TH1F* den_MC_eta[n_MC];
  TH2F* den_MC_2d[n_MC];
  THStack* num_MC_stack_pt = new THStack("num_MC_stack_pt", "");
  THStack* num_MC_stack_eta = new THStack("num_MC_stack_eta", "");
  THStack* den_MC_stack_pt = new THStack("den_MC_stack_pt", "");
  THStack* den_MC_stack_eta = new THStack("den_MC_stack_eta", "");

  for(int i=0; i<n_MC; i++){
    TFile* file = new TFile("./rootfiles/FakeRateCalculator_Mu_SK"+MC_sample[i]+"_5_3_14.root");
    num_MC_pt[i] = (TH1F*)file->Get("pt_F"); num_MC_pt[i]->SetFillColor(MC_color[i]); num_MC_pt[i]->SetLineColor(MC_color[i]);
    num_MC_eta[i] = (TH1F*)file->Get("eta_F"); num_MC_eta[i]->SetFillColor(MC_color[i]); num_MC_eta[i]->SetLineColor(MC_color[i]);
    num_MC_2d[i] = (TH2F*)file->Get("events_F");
    den_MC_pt[i] = (TH1F*)file->Get("pt_F0"); den_MC_pt[i]->SetFillColor(MC_color[i]); den_MC_pt[i]->SetLineColor(MC_color[i]);
    den_MC_eta[i] = (TH1F*)file->Get("eta_F0"); den_MC_eta[i]->SetFillColor(MC_color[i]); den_MC_eta[i]->SetLineColor(MC_color[i]);
    den_MC_2d[i] = (TH2F*)file->Get("events_F0");

    num_MC_stack_pt->Add(num_MC_pt[i]);
    num_MC_stack_eta->Add(num_MC_eta[i]);
    den_MC_stack_pt->Add(den_MC_pt[i]);
    den_MC_stack_eta->Add(den_MC_eta[i]);

  }
 
  gStyle->SetOptStat(0); 
  TLegend* lg = new TLegend(0.6, 0.6, 0.9, 0.9);
  lg->SetFillStyle(0);
  lg->SetBorderSize(0);
  lg->AddEntry(num_data_pt,"Data",  "p");
  lg->AddEntry(num_MC_pt[5], "Wjets", "f");
  lg->AddEntry(num_MC_pt[4], "DY 10 < m(ll) < 50", "f");
  lg->AddEntry(num_MC_pt[3], "ttbar", "f");
  lg->AddEntry(num_MC_pt[2], "DY 50 > m(ll)","f");
  lg->AddEntry(num_MC_pt[1], "singletop", "f");
  lg->AddEntry(num_MC_pt[0], "W#gamma", "f");

/*
  // example of drawing DATA/MC //
  TCanvas* c_num_pt = new TCanvas("c_num_pt", "", 800, 800);
  TPad *c_num_pt_up = new TPad("c_num_pt_up", "", 0, 0.25, 1, 1);
  c_num_pt_up->SetTopMargin( 0.05 ); c_num_pt_up->SetBottomMargin( 0.02 ); c_num_pt_up->SetRightMargin( 0.02 ); c_num_pt_up->SetLeftMargin( 0.1 );
  TPad *c_num_pt_down = new TPad("c_num_pt_down", "", 0, 0, 1, 0.25);
  c_num_pt_down->SetTopMargin( 0.03 ); c_num_pt_down->SetBottomMargin( 0.25 ); c_num_pt_down->SetRightMargin( 0.02 ); c_num_pt_down->SetLeftMargin( 0.1 ); c_num_pt_down->SetGridx(); c_num_pt_down->SetGridy();
  c_num_pt_up->Draw();
  c_num_pt_down->Draw();
  c_num_pt_up->cd();
  c_num_pt_up->SetLogy();
  //up//
  num_data_pt->GetXaxis()->SetLabelSize(0);
  num_data_pt->GetYaxis()->SetLabelSize(0.05);
  num_data_pt->GetYaxis()->SetTitleSize(0.05);
  num_data_pt->GetYaxis()->SetTitleOffset(1.03);
  num_data_pt->GetYaxis()->SetTitle("Events"); //FIXME
  //num_data_pt->GetYaxis()->SetTitle("Events / "+TString::Itoa(7,10)+" GeV"); //FIXME
  num_data_pt->GetYaxis()->SetTitleOffset(1.03);
  num_data_pt->Rebin(5);
  num_data_pt->Draw("psame");
  num_MC_stack_pt->Draw("histsame");
  lg->Draw();
  c_num_pt_down->cd();
  //down//
  TH1F* hist_num_MC_stack_pt = (TH1F*)num_MC_stack_pt->GetStack()->Last()->Clone();
  TH1F* clone_num_data_pt = (TH1F*)num_data_pt->Clone();
  clone_num_data_pt->Divide(hist_num_MC_stack_pt);
  clone_num_data_pt->Draw("PE1same");
  //save//
  c_num_pt->SaveAs("./plots/fake_calculator/num_pt.png");
  c_num_pt->Close();
*/

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
  c_num_pt->SaveAs("./plots/fake_calculator/num_pt.png");
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
  c_num_eta->SaveAs("./plots/fake_calculator/num_eta.png");
  c_num_eta->Close();

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
  c_den_pt->SaveAs("./plots/fake_calculator/den_pt.png");
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
  c_den_eta->SaveAs("./plots/fake_calculator/den_eta.png");
  c_den_eta->Close();

  TCanvas* c_2d = new TCanvas("c_2d", "", 1600, 1100);
  canvas_margin(c_2d);
  c_2d->SetLeftMargin(0.07);
  c_2d->SetRightMargin( 0.1 );
  gStyle->SetPaintTextFormat("0.4f");
  TH2F* num_2d = (TH2F*)num_data_2d->Clone(); // clone data, and then subtract prompt
  TH2F* den_2d = (TH2F*)den_data_2d->Clone(); // clone data, and then subtract prompt
  for(int i=0; i<n_MC_prompt; i++){
    num_2d->Add(num_MC_2d[i], -1.0);
    den_2d->Add(den_MC_2d[i], -1.0);
  }
  // check negative values
  int n_xbins = num_2d->GetXaxis()->GetNbins();
  int n_ybins = num_2d->GetYaxis()->GetNbins();
  for(int i_x=0; i_x<n_xbins; i_x++){
    for(int i_y=0; i_y<n_ybins; i_y++){
      if(num_2d->GetBinContent(i_x+1, i_y+1) < 0 || den_2d->GetBinContent(i_x+1, i_y+1) < 0 ) num_2d->SetBinContent(i_x+1, i_y+1, 0);
    }
  }
  TH2F* fake_2d = (TH2F*)num_2d->Clone();
  fake_2d->GetXaxis()->SetRangeUser(10, 60);
  fake_2d->Divide(den_2d);
  fake_2d->Draw("colztexte1");
  fake_2d->SetXTitle("p_{T} [GeV]");
  fake_2d->SetYTitle("|#eta|");
  fake_2d->SetTitle("Fake Rate Matrix");
  //c_2d->SaveAs("./plots/fake_calculator/fakerate_without_subtraction.png");
  //c_2d->SaveAs("./plots/fake_calculator/fakerate.png");
  c_2d->Close();

}
