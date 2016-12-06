#include "canvas_margin.h"
#define n_xbins 9
#define n_ybins 4

void syst_fake_calculator_2016(){
  
  gStyle->SetOptStat(0);
  
  TString filepath = "./plots/v8-0-2.8/FakeRateCalculator/";
  TString plotpath = "./plots/v8-0-2.8/FR_syst/";
  
  if( !gSystem->mkdir(plotpath, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }
  
  vector<double> dXYMins = {0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0};
  //vector<double> dXYMins = {4.0};
  
  TH1D *hist_n_muons = new TH1D("hist_n_muons", "", 12, 0, 6);
  
  double FR_max[n_xbins*n_ybins], FR_min[n_xbins*n_ybins];
  for(int ix=1; ix<=n_xbins; ix++){
    for(int iy=1; iy<=n_ybins; iy++){
      int this_index = ix+(iy-1)*n_xbins;
      FR_max[this_index] = 0.;
      FR_min[this_index] = 999;
    }
  }
  
  for(int aaa=0; aaa<dXYMins.size(); aaa++){
    
    int Digit1 = int(dXYMins.at(aaa));
    int Digit0p1 = 10*dXYMins.at(aaa)-10*Digit1;
    TString str_dXYCut = "dXYSigMin_"+TString::Itoa(Digit1,10)+"p"+TString::Itoa(Digit0p1,10);
    TString str_dXYnum = TString::Itoa(Digit1,10)+"."+TString::Itoa(Digit0p1,10);
    //cout << str_dXYCut << endl;
    
    TFile *file = new TFile(filepath+str_dXYCut+"/13TeV_trimuon_FR_SingleMuonTrigger_HighdXY.root");
    
    TH1D *hist_n_data_prompt_subtraction = (TH1D*)file->Get("hist_n_data_prompt_subtraction_num");
    hist_n_muons->SetBinContent(aaa+2, hist_n_data_prompt_subtraction->GetBinContent(1));
    
    TH2F *hist_FR = (TH2F*)file->Get(str_dXYCut+"_SingleMuonTrigger_HighdXY_events_F");
    //int n_xbins = hist_FR->GetXaxis()->GetNbins();
    //int n_ybins = hist_FR->GetYaxis()->GetNbins();
    //cout << "n_xbins = " << n_xbins << endl;
    //cout << "n_ybins = " << n_ybins << endl;
    
    for(int ix=1; ix<=n_xbins; ix++){
      for(int iy=1; iy<=n_ybins; iy++){
        int this_index = ix+(iy-1)*n_xbins;
        
        double this_FR = hist_FR->GetBinContent(ix,iy);
        if( this_FR > FR_max[this_index] ) FR_max[this_index] = this_FR;
        if( this_FR < FR_min[this_index] ) FR_min[this_index] = this_FR;
      }
    }
    
  }
  
  //==== n_muons
  TCanvas *c_n_muons = new TCanvas("c_n_muons", "", 800, 800);
  canvas_margin(c_n_muons);
  c_n_muons->cd();
  hist_n_muons->Draw("hist");
  hist_n_muons->GetYaxis()->SetTitle("# of muons");
  hist_n_muons->GetXaxis()->SetTitle("Minimum |dXYSig|");
  hist_axis(hist_n_muons);
  TGaxis::SetMaxDigits(2);
  c_n_muons->SaveAs(plotpath+"n_muons.png");


  //==== FR 
  float etaarray [] = {0.0, 0.8, 1.479, 2.0, 2.5};
  float ptarray [] = {10.,15.,20.,25.,30.,35.,45.,60.,80.,100.};

  TFile *file_central = new TFile(filepath+"/dXYSigMin_4p0/13TeV_trimuon_FR_SingleMuonTrigger_HighdXY.root");
  TH2F *hist_FR_central = (TH2F*)file_central->Get("dXYSigMin_4p0_SingleMuonTrigger_HighdXY_events_F");

  double FR_syst_error_up[n_xbins*n_ybins], FR_syst_error_down[n_xbins*n_ybins];
  TH2D *hist_FR_max = new TH2D("hist_FR_max", "", 9, ptarray, 4, etaarray);
  TH2D *hist_FR_min = new TH2D("hist_FR_min", "", 9, ptarray, 4, etaarray);
  for(int ix=1; ix<=n_xbins; ix++){
    for(int iy=1; iy<=n_ybins; iy++){
      int this_index = ix+(iy-1)*n_xbins;
      hist_FR_max->SetBinContent(ix, iy, FR_max[this_index]);
      hist_FR_min->SetBinContent(ix, iy, FR_min[this_index]);
      FR_syst_error_up[this_index] = FR_max[this_index] - hist_FR_central->GetBinContent(ix, iy);
      FR_syst_error_down[this_index] = hist_FR_central->GetBinContent(ix, iy) - FR_min[this_index];
    }
  }

  TCanvas *c_FR_central = new TCanvas("c_FR_central", "", 1600, 1100);
  c_FR_central->SetLeftMargin(0.07);
  c_FR_central->SetRightMargin( 0.1 );
  gStyle->SetPaintTextFormat("0.4f");
  hist_FR_central->Draw("colztexte1");
  hist_FR_central->GetXaxis()->SetRangeUser(10, 60);
  hist_FR_central->SetXTitle("p_{T} [GeV]");
  hist_FR_central->SetYTitle("|#eta|");
  hist_FR_central->SetTitle("");
  c_FR_central->SaveAs(plotpath+"FR_central.png");
  c_FR_central->Close();

  TCanvas *c_FR_max = new TCanvas("c_FR_max", "", 1600, 1100);
  c_FR_max->SetLeftMargin(0.07);
  c_FR_max->SetRightMargin( 0.1 );
  gStyle->SetPaintTextFormat("0.4f");
  hist_FR_max->Draw("colztexte1");
  hist_FR_max->GetXaxis()->SetRangeUser(10, 60);
  hist_FR_max->SetXTitle("p_{T} [GeV]");
  hist_FR_max->SetYTitle("|#eta|");
  hist_FR_max->SetTitle("");
  c_FR_max->SaveAs(plotpath+"FR_max.png");
  c_FR_max->Close();

  TCanvas *c_FR_min = new TCanvas("c_FR_min", "", 1600, 1100);
  c_FR_min->SetLeftMargin(0.07);
  c_FR_min->SetRightMargin( 0.1 );
  gStyle->SetPaintTextFormat("0.4f");
  hist_FR_min->Draw("colztexte1");
  hist_FR_min->GetXaxis()->SetRangeUser(10, 60);
  hist_FR_min->SetXTitle("p_{T} [GeV]");
  hist_FR_min->SetYTitle("|#eta|");
  hist_FR_min->SetTitle("");
  c_FR_min->SaveAs(plotpath+"FR_min.png");
  c_FR_min->Close();

  TFile *file_output = new TFile(plotpath+"/13TeV_trimuon_FR_SingleMuonTrigger_HighdXY.root", "RECREATE");
  file_output->cd();
  hist_FR_central->SetName("FR_central");
  hist_FR_max->SetName("FR_max");
  hist_FR_min->SetName("FR_min");
  hist_FR_central->Write();
  hist_FR_max->Write();
  hist_FR_min->Write();
  file_output->Close();


}


