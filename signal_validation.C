#define n_all 11
#define n_high 8

#include "canvas_margin.h"

void signal_validation(){

  double x_all[n_all] = {40, 50, 60, 100, 150, 200, 300, 400, 500, 700, 1000};
  double x_high[n_high] = {100, 150, 200, 300, 400, 500, 700, 1000};
  double y_gen_pt_order[n_all];
  double y_reco_pt_order[n_all];
  double y_reco_pt_order_rev[n_all];
  double y_mlmet[n_high];

  int j = 0;
  for(unsigned int i = 0; i < n_all; i++){
    TFile* file = new TFile("./rootfiles/trilepton_mumumu_SKHN"+TString::Itoa(x_all[i], 10)+"_mumumu_new_5_3_14.root");
    TH1F* hist_gen_pt_order = (TH1F*)file->Get("gen_pri_lep_pt_greater_check");
    TH1F* hist_reco_pt_order = (TH1F*)file->Get("reco_leading_SS_matching_check");
    TH1F* hist_reco_pt_order_rev = (TH1F*)file->Get("reco_subleading_SS_matching_check");
    y_gen_pt_order[i] = hist_gen_pt_order->GetMean();
    y_reco_pt_order[i] = hist_reco_pt_order->GetMean();
    y_reco_pt_order_rev[i] = hist_reco_pt_order_rev->GetMean();
    if(x_all[i] > 80){
      TH1F* hist_mlmet = (TH1F*)file->Get("highmass_mlmet_Wmass_check");
      y_mlmet[j] = hist_mlmet->GetMean();
      j++;
    }
  }

  double xx[2] = {0, 2000}, yy[2] = {0.5, 0.5};
  TGraph* gr_05 = new TGraph(2, xx, yy);

  TCanvas* c1 = new TCanvas("c1", "", 1000, 1000);
  canvas_margin(c1);
  c1->cd();
  TGraph* gr_gen_pt_order = new TGraph(n_all, x_all, y_gen_pt_order);
  gr_gen_pt_order->Draw("ap");
  gr_gen_pt_order->SetMarkerStyle(3);
  gPad->SetLogx();
  gr_gen_pt_order->GetYaxis()->SetRangeUser(0, 1);
  gr_gen_pt_order->GetXaxis()->SetRangeUser(0.01, 5000);
  gr_gen_pt_order->SetTitle("Prob. of leading SS matched to true primary lepton");
  gr_gen_pt_order->GetXaxis()->SetTitle("m(HN) [GeV]");

  TGraph* gr_reco_pt_order = new TGraph(n_all, x_all, y_reco_pt_order);
  gr_reco_pt_order->SetMarkerStyle(2);
  gr_reco_pt_order->SetMarkerColor(kRed);
  gr_reco_pt_order->Draw("psame");

//  TGraph* gr_reco_pt_order_rev = new TGraph(n_all, x_all, y_reco_pt_order_rev);
//  gr_reco_pt_order_rev->SetMarkerStyle(2);
//  gr_reco_pt_order_rev->SetMarkerColor(kBlue);
//  gr_reco_pt_order_rev->Draw("psame");

  gr_05->Draw("same");

  c1->SaveAs("plots/signal_validation/pt_order.png");
  c1->Close();

  TCanvas* c2 = new TCanvas("c2", "", 1000, 1000);
  canvas_margin(c2);
  c2->cd();
  TGraph* gr_mlmet = new TGraph(n_high, x_high, y_mlmet);
  gr_mlmet->Draw("ap");
  gr_mlmet->SetMarkerStyle(3);
  gPad->SetLogx(0);
  gr_mlmet->GetYaxis()->SetRangeUser(0, 1);
  gr_mlmet->SetTitle("Prob. of m(l#MET) closest matched true lepton from second W");
  gr_mlmet->GetXaxis()->SetTitle("m(HN) [GeV]");


  gr_05->Draw("same");
  
  c2->SaveAs("plots/signal_validation/mlmet.png");
  c2->Close();

}
