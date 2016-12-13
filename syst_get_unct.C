#include "canvas_margin.h"
#define n_xbins 9
#define n_ybins 4

double sumw2ratioerror(double A, double dA, double B, double dB);

void syst_get_unct(){
  
  gStyle->SetOptStat(0);
  TH1::AddDirectory(kFALSE);
  
  TString filepath = "./rootfiles/v8-0-2.9/FR_syst/";
  TString plotpath = "./plots/v8-0-2.9/FR_syst/";

  TString channel = "Preselection";
  
  if( !gSystem->mkdir(plotpath, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }
  
  vector<double> dXYMins = {3.0, 4.0, 5.0};
  double bins_dXYMins[] =  {3.0, 4.0, 5.0, 6.0};
  vector<double> RelIsoMaxs = {0.2, 0.3, 0.4, 0.6, 0.8, 1.0};
  double bins_RelIsoMaxs[] =  {0.2, 0.3, 0.4, 0.6, 0.8, 1.0, 1.2};
  
  double dXYMin_cent = 4.0;
  double RelIsoMax_cent = 0.6;
  double n_events_cent, error_cent;
 
  TH2D *hist_yield = new TH2D("hist_yield", "", dXYMins.size(), bins_dXYMins, RelIsoMaxs.size(), bins_RelIsoMaxs);
  TH2D *hist_n_events = new TH2D("hist_n_events", "", dXYMins.size(), bins_dXYMins, RelIsoMaxs.size(), bins_RelIsoMaxs);
  TH2D *hist_n_TTL = new TH2D("hist_n_TTL", "", dXYMins.size(), bins_dXYMins, RelIsoMaxs.size(), bins_RelIsoMaxs);
  TH2D *hist_n_TLL = new TH2D("hist_n_TLL", "", dXYMins.size(), bins_dXYMins, RelIsoMaxs.size(), bins_RelIsoMaxs);
  TH2D *hist_n_LLL = new TH2D("hist_n_LLL", "", dXYMins.size(), bins_dXYMins, RelIsoMaxs.size(), bins_RelIsoMaxs);
  
  TFile *file_tmp = new TFile(filepath+"/trilepton_mumumu_syst_FR_data_DoubleMuon_cat_v8-0-2.root");
  
  for(int aaa=0; aaa<dXYMins.size(); aaa++){
    for(int bbb=0; bbb<RelIsoMaxs.size(); bbb++){
      
      int Digit1 = int(dXYMins.at(aaa));
      int Digit0p1 = 10*dXYMins.at(aaa)-10*Digit1;
      TString str_dXYCut = "dXYSigMin_"+TString::Itoa(Digit1,10)+"p"+TString::Itoa(Digit0p1,10);
      //cout << str_dXYCut << endl;
      
      int iso_Digit1 = int(RelIsoMaxs.at(bbb));
      int iso_Digit0p1 = 10*RelIsoMaxs.at(bbb)-10*iso_Digit1;
      TString str_iso = "LooseRelIsoMax_"+TString::Itoa(iso_Digit1,10)+"p"+TString::Itoa(iso_Digit0p1,10);
      
      str_dXYCut = str_dXYCut+"_"+str_iso;
      
      //cout << "["<<str_dXYCut<<"]"<< endl;
      
      TH1D *hist_tmp = (TH1D*)file_tmp->Get(str_dXYCut+"_n_events_"+channel)->Clone();
      TH1D *hist_Loose = (TH1D*)file_tmp->Get(str_dXYCut+"_n_OnlyLoose_"+channel)->Clone();

      hist_yield->SetBinContent(aaa+1, bbb+1, hist_tmp->GetBinContent(1));
      hist_yield->SetBinError(aaa+1, bbb+1, hist_tmp->GetBinError(1));

      hist_n_events->SetBinContent(aaa+1, bbb+1, hist_tmp->GetEntries());
      hist_n_TTL->SetBinContent(aaa+1, bbb+1, hist_Loose->GetBinContent(2));
      hist_n_TLL->SetBinContent(aaa+1, bbb+1, hist_Loose->GetBinContent(3));
      hist_n_LLL->SetBinContent(aaa+1, bbb+1, hist_Loose->GetBinContent(4));

      if(dXYMins.at(aaa)==dXYMin_cent && RelIsoMaxs.at(bbb)==RelIsoMax_cent){
        n_events_cent = hist_tmp->GetBinContent(1);
        error_cent = hist_tmp->GetBinError(1);
      }
      
    }
  }
  
  //==== n events
  TCanvas *c_n_events = new TCanvas("c_n_events", "", 800, 800);
  canvas_margin(c_n_events);
  c_n_events->cd();
  hist_n_events->SetMarkerSize(2);
  hist_n_events->Draw("coltext");
  hist_n_events->GetYaxis()->SetTitle("Maximum Loose Isolation");
  hist_n_events->GetXaxis()->SetTitle("Minimum |dXYSig|");
  hist_axis(hist_n_events);
  //TGaxis::SetMaxDigits(2);
  c_n_events->SaveAs(plotpath+"/n_events.png");
  c_n_events->Close();

  //==== TTL
  TCanvas *c_TTL = new TCanvas("c_TTL", "", 800, 800);
  canvas_margin(c_TTL);
  c_TTL->cd();
  hist_n_TTL->SetMarkerSize(2);
  hist_n_TTL->Draw("coltext");
  hist_n_TTL->GetYaxis()->SetTitle("Maximum Loose Isolation");
  hist_n_TTL->GetXaxis()->SetTitle("Minimum |dXYSig|");
  hist_axis(hist_n_TTL);
  //TGaxis::SetMaxDigits(2);
  c_TTL->SaveAs(plotpath+"/n_TTL.png");
  c_TTL->Close();

  //==== TLL
  TCanvas *c_TLL = new TCanvas("c_TLL", "", 800, 800);
  canvas_margin(c_TLL);
  c_TLL->cd();
  hist_n_TLL->SetMarkerSize(2);
  hist_n_TLL->Draw("coltext");
  hist_n_TLL->GetYaxis()->SetTitle("Maximum Loose Isolation");
  hist_n_TLL->GetXaxis()->SetTitle("Minimum |dXYSig|");
  hist_axis(hist_n_TLL);
  //TGaxis::SetMaxDigits(2);
  c_TLL->SaveAs(plotpath+"/n_TLL.png");
  c_TLL->Close();

  //==== LLL
  TCanvas *c_LLL = new TCanvas("c_LLL", "", 800, 800);
  canvas_margin(c_LLL);
  c_LLL->cd();
  hist_n_LLL->SetMarkerSize(2);
  hist_n_LLL->Draw("coltext");
  hist_n_LLL->GetYaxis()->SetTitle("Maximum Loose Isolation");
  hist_n_LLL->GetXaxis()->SetTitle("Minimum |dXYSig|");
  hist_axis(hist_n_LLL);
  //TGaxis::SetMaxDigits(2);
  c_LLL->SaveAs(plotpath+"/n_LLL.png");
  c_LLL->Close();

  //==== yield
  TCanvas *c_yield = new TCanvas("c_yield", "", 800, 800);
  canvas_margin(c_yield);
  c_yield->cd();
  hist_yield->SetMarkerSize(2);
  hist_yield->Draw("coltexte1");
  hist_yield->GetYaxis()->SetTitle("Maximum Loose Isolation");
  hist_yield->GetXaxis()->SetTitle("Minimum |dXYSig|");
  hist_axis(hist_yield);
  //TGaxis::SetMaxDigits(2);
  c_yield->SaveAs(plotpath+"/yield.png");
  c_yield->Close();

  //==== syst
  TCanvas *c_syst = new TCanvas("c_syst", "", 800, 800);
  canvas_margin(c_syst);
  c_syst->cd();
  for(int aaa=0; aaa<dXYMins.size(); aaa++){
    for(int bbb=0; bbb<RelIsoMaxs.size(); bbb++){

      //==== A : original - central
      //==== B : central
      //==== Error(A/B) = (A/B) * sqrt[ (Error(A)/A)^2 + (Error(B)/B)^2 ]

      double A_num = hist_yield->GetBinContent(aaa+1, bbb+1) - n_events_cent;
      double dA_num = hist_yield->GetBinError(aaa+1, bbb+1)+error_cent;

      double B_den = n_events_cent;
      double dB_den = error_cent;

      hist_yield->SetBinContent( aaa+1, bbb+1, 100.*A_num/B_den);
      hist_yield->SetBinError( aaa+1, bbb+1, sumw2ratioerror(A_num, dA_num, B_den, dB_den) );
    }
  }
  hist_yield->SetMarkerSize(2);
  hist_yield->Draw("coltext");
  hist_yield->GetYaxis()->SetTitle("Maximum Loose Isolation");
  hist_yield->GetXaxis()->SetTitle("Minimum |dXYSig|");
  c_syst->SaveAs(plotpath+"/syst.png");
  
  
}

double sumw2ratioerror(double A, double dA, double B, double dB){

  //==== return error of A/B by sumw2 method

  return (A/B)*sqrt( (dA/A)*(dA/A) + (dB/B)*(dB/B) );


}

