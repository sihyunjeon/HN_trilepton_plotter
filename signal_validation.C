#define n_all 12
#define n_high 9

#include "canvas_margin.h"

void signal_validation(){

  double x_all[n_all] = {40, 50, 60, 90, 100, 150, 200, 300, 400, 500, 700, 1000};
  double x_high[n_high] = {90, 100, 150, 200, 300, 400, 500, 700, 1000};
  double y_gen_pri_lep_pt_greater[n_all], y_reco_leading_SS_match_gen_l_1[n_all], y_reco_subleading_SS_match_gen_l_1[n_all];
  double y_highmass_mlmet_Wmass_match_gen_l_3[n_high];
  double y_pt_order_first[n_high], y_pt_order_first_mlmet_next[n_high], y_pt_order_first_mlmet_next_total[n_high];
  double y_mlmet_first[n_high], y_mlmet_first_pt_order_next[n_high], y_mlmet_first_pt_order_next_total[n_high];



  int j = 0;
  for(unsigned int i = 0; i < n_all; i++){
    TFile* file = new TFile("./rootfiles/trilepton_mumumu_SKHN"+TString::Itoa(x_all[i], 10)+"_mumumu_new_5_3_14.root");

    TH1F* hist_gen_pri_lep_pt_greater = (TH1F*)file->Get("gen_pri_lep_pt_greater");
    TH1F* hist_reco_leading_SS_match_gen_l_1 = (TH1F*)file->Get("reco_leading_SS_match_gen_l_1");
    TH1F* hist_reco_subleading_SS_match_gen_l_1 = (TH1F*)file->Get("reco_subleading_SS_match_gen_l_1");

    y_gen_pri_lep_pt_greater[i] = hist_gen_pri_lep_pt_greater->GetMean();
    y_reco_leading_SS_match_gen_l_1[i] = hist_reco_leading_SS_match_gen_l_1->GetMean();
    y_reco_subleading_SS_match_gen_l_1[i] = hist_reco_subleading_SS_match_gen_l_1->GetMean();

    if(x_all[i] > 80){
      TH1F* hist_highmass_mlmet_Wmass_match_gen_l_3 = (TH1F*)file->Get("highmass_mlmet_Wmass_match_gen_l_3");
      y_highmass_mlmet_Wmass_match_gen_l_3[j] = hist_highmass_mlmet_Wmass_match_gen_l_3->GetMean();

      TH1F* hist_pt_order_first = (TH1F*)file->Get("pt_order_first");
      TH1F* hist_pt_order_first_mlmet_next = (TH1F*)file->Get("pt_order_first_mlmet_next");
      y_pt_order_first[j] = hist_pt_order_first->GetMean();
      y_pt_order_first_mlmet_next[j] = hist_pt_order_first_mlmet_next->GetMean();
      y_pt_order_first_mlmet_next_total[j] = y_pt_order_first[j] * y_pt_order_first_mlmet_next[j];

      TH1F* hist_mlmet_first = (TH1F*)file->Get("mlmet_first"); 
      TH1F* hist_mlmet_first_pt_order_next = (TH1F*)file->Get("mlmet_first_pt_order_next");
      y_mlmet_first[j] = hist_mlmet_first->GetMean();
      y_mlmet_first_pt_order_next[j] = hist_mlmet_first_pt_order_next->GetMean();
      y_mlmet_first_pt_order_next_total[j] = y_mlmet_first[j] * y_mlmet_first_pt_order_next[j];

      j++;
    }
  }

  double xx[2] = {0, 2000}, yy[2] = {0.5, 0.5};
  TGraph* gr_05 = new TGraph(2, xx, yy);

  // pt_order
  TCanvas* c1 = new TCanvas("c1", "", 1000, 1000);
  canvas_margin(c1);
  c1->cd();
  // leading is matched to gen_l_1
  TGraph* gr_reco_leading_SS_match_gen_l_1 = new TGraph(n_all, x_all, y_reco_leading_SS_match_gen_l_1);
  gr_reco_leading_SS_match_gen_l_1->Draw("ap");
  gr_reco_leading_SS_match_gen_l_1->SetMarkerStyle(3);
  //gPad->SetLogx();
  gr_reco_leading_SS_match_gen_l_1->GetYaxis()->SetRangeUser(0, 1);
  gr_reco_leading_SS_match_gen_l_1->GetXaxis()->SetRangeUser(1, 2000);
  gr_reco_leading_SS_match_gen_l_1->SetTitle("Prob. of leading SS matched to true primary lepton");
  gr_reco_leading_SS_match_gen_l_1->GetXaxis()->SetTitle("m(HN) [GeV]");
  // subleading is matched to gen_l_1
  TGraph* gr_reco_subleading_SS_match_gen_l_1 = new TGraph(n_all, x_all, y_reco_subleading_SS_match_gen_l_1);
  gr_reco_subleading_SS_match_gen_l_1->SetMarkerStyle(2);
  gr_reco_subleading_SS_match_gen_l_1->SetMarkerColor(kRed);
  gr_reco_subleading_SS_match_gen_l_1->Draw("psame");
  // 0.5 line
  gr_05->Draw("same");
  // print values
  cout << "====== pt order ======" << endl;
  cout << "1) leading it matched to gen_l_1" << endl;
  gr_reco_leading_SS_match_gen_l_1->Print();
  cout << "2) subleading is matched to gen_l_1" << endl;
  gr_reco_subleading_SS_match_gen_l_1->Print();
  // save canvas
  c1->SaveAs("plots/signal_validation/pt_order.png");
  c1->Close();

  // mlmet
  TCanvas* c2 = new TCanvas("c2", "", 1000, 1000);
  canvas_margin(c2);
  c2->cd();
  TGraph* gr_highmass_mlmet_Wmass_match_gen_l_3 = new TGraph(n_high, x_high, y_highmass_mlmet_Wmass_match_gen_l_3);
  gr_highmass_mlmet_Wmass_match_gen_l_3->Draw("ap");
  gr_highmass_mlmet_Wmass_match_gen_l_3->SetMarkerStyle(3);
  gr_highmass_mlmet_Wmass_match_gen_l_3->GetYaxis()->SetRangeUser(0, 1);
  gr_highmass_mlmet_Wmass_match_gen_l_3->GetXaxis()->SetRangeUser(1, 2000);
  gr_highmass_mlmet_Wmass_match_gen_l_3->SetTitle("Prob. of m(#mu#slash{E}_{T}) closest matched true lepton from second W");
  gr_highmass_mlmet_Wmass_match_gen_l_3->GetXaxis()->SetTitle("m(HN) [GeV]");
  // 0.5 line
  gr_05->Draw("same");
  // print values
  cout << "===== mlmet =====" << endl;
  gr_highmass_mlmet_Wmass_match_gen_l_3->Print();
  // save canvas
  c2->SaveAs("plots/signal_validation/mlmet.png");
  c2->Close();
 
  // pt first
  TCanvas* c3 = new TCanvas("c3", "", 1000, 1000);
  canvas_margin(c3);
  c3->cd();
  TGraph* gr_pt_order_first_mlmet_next = new TGraph(n_high, x_high, y_pt_order_first_mlmet_next);
  gr_pt_order_first_mlmet_next->Draw("ap");
  gr_pt_order_first_mlmet_next->SetMarkerStyle(3);
  gr_pt_order_first_mlmet_next->GetYaxis()->SetRangeUser(0, 1);
  gr_pt_order_first_mlmet_next->SetTitle("p_{T} ordering first");
  gStyle->SetTitleFontSize(0.04);
  // total
  TGraph* gr_pt_order_first_mlmet_next_total = new TGraph(n_high, x_high, y_pt_order_first_mlmet_next_total);
  gr_pt_order_first_mlmet_next_total->SetMarkerStyle(3);
  gr_pt_order_first_mlmet_next_total->SetMarkerColor(kRed);
  gr_pt_order_first_mlmet_next_total->Draw("psametext");
  // print values
  cout << "===== pt first (after pt order assigning) =====" << endl;
  cout << "1) mlmet only" << endl;
  gr_pt_order_first_mlmet_next->Print();
  cout << "2) total" << endl;
  gr_pt_order_first_mlmet_next_total->Print();
  // save canvas
  c3->SaveAs("plots/signal_validation/pt_first.png");
  c3->Close();

  // mlmet first
  TCanvas* c4 = new TCanvas("c4", "", 1000, 1000);
  canvas_margin(c4);
  c4->cd();
  TGraph* gr_mlmet_first_pt_order_next = new TGraph(n_high, x_high, y_mlmet_first_pt_order_next);
  gr_mlmet_first_pt_order_next->Draw("ap");
  gr_mlmet_first_pt_order_next->SetMarkerStyle(3);
  gr_mlmet_first_pt_order_next->GetYaxis()->SetRangeUser(0, 1);
  gr_mlmet_first_pt_order_next->SetTitle("m(#mu#slash{E}_{T}) first");
  gStyle->SetTitleFontSize(0.03);
  // total
  TGraph* gr_mlmet_first_pt_order_next_total = new TGraph(n_high, x_high, y_mlmet_first_pt_order_next_total);
  gr_mlmet_first_pt_order_next_total->SetMarkerStyle(3);
  gr_mlmet_first_pt_order_next_total->SetMarkerColor(kRed);
  gr_mlmet_first_pt_order_next_total->Draw("psametext");
  // print values
  cout << "===== mlmet first (after mlmet assigning) =====" << endl;
  cout << "1) pt order only" << endl;
  gr_mlmet_first_pt_order_next->Print();
  cout << "2) total" << endl;
  gr_mlmet_first_pt_order_next_total->Print();
  // save canvas
  c4->SaveAs("plots/signal_validation/mlmet_first.png");
  c4->Close();



}
