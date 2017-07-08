#include "canvas_margin.h"
#include <TPaveStats.h>
#define n_xbins 9
#define n_ybins 4

void ChargeFlipDrawSFCompares(int XXX, int YYY){

  TF1 *line_mid = new TF1("line_mid","1", 60., 120.);

  gStyle->SetOptStat(0);
  gStyle->SetPaintTextFormat("1.6f");
  TH1::AddDirectory(kFALSE);

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");  
  TString filepath = WORKING_DIR+"/rootfiles/v8-0-7.18/CFRateCalculator/";
  TString plotpath = WORKING_DIR+"/plots/v8-0-7.18/CFRateCalculator/Fitting/";

  if( !gSystem->mkdir(plotpath, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }
  TString region = "";
  if(XXX==0) region = "global";
  if(XXX==1) region = "BB";
  if(XXX==2) region = "EE";
  if(XXX==3) region = "BE";
  if(XXX==4) region = "JETS1_global";
  TString scalefactor = "";
  if(YYY==0) scalefactor ="";
  if(YYY==1) scalefactor ="_SF";

  TFile *file_tmp = new TFile(filepath+"/CFRateCalculator_data_DoubleEG_cat_v8-0-7.root");
  TString hist_pre_name = "predicted_Z_mass_"+region+"_HNTIGHT_powheg"+scalefactor+"_wideZ";
  TString hist_obs_name = "observed_Z_mass_"+region+"_HNTIGHT_powheg_wideZ";  

  TH1D *hist_pre, *hist_obs;
  hist_pre = (TH1D*)(file_tmp->Get(hist_pre_name)->Clone());
  hist_obs = (TH1D*)(file_tmp->Get(hist_obs_name)->Clone());
  
  double bkg_const[5] = {6.755975,4.01829,0.86417,1.873515,2.1419975};
  const int n_bins = 60;
  TH1D *hist_bkg = new TH1D("", "", n_bins, 60., 120.);
  TH1D *hist_den = new TH1D("", "", n_bins, 60., 120.);
  for(int i=1+16; i<n_bins+1-14; i++){
    hist_bkg->SetBinContent(i,bkg_const[XXX]);
  }
  hist_bkg->SetLineColor(kAzure+8);
  hist_bkg->SetFillColor(kAzure+8);
  hist_pre->SetLineColor(kYellow);
  hist_pre->SetFillColor(kYellow);

  THStack *hist_stack = new THStack("","");
  hist_stack->Add(hist_bkg);
  hist_stack->Add(hist_pre);
  hist_den->Add(hist_bkg);
  hist_den->Add(hist_pre);

  TH1D* hist_compare = (TH1D*)hist_obs->Clone();

  hist_obs->SetMarkerStyle(20);
  hist_obs->SetMarkerSize(0.75);

  hist_compare->Divide(hist_den);
  TCanvas* c1 = new TCanvas("canvas", "canvas", 800, 600);
  c1->Draw();
  TPad *c1_up;
  TPad *c1_down;
  c1_up = new TPad("c1_up", "", 0, 0.25, 1, 1);
  c1_down = new TPad("c1_down", "", 0, 0, 1, 0.32);
 
  c1_down->SetGridx();
  c1_down->SetGridy();  
  c1_up->Draw();
  c1_down->Draw();

  c1_up->cd();
  hist_stack->Draw("hist");
  hist_obs->Draw("same");
  double maxs[5]={150.,60.,60.,90., 35.};
  hist_stack->SetMaximum(maxs[XXX]);

  TLegend *lg;
  lg = new TLegend(0.70, 0.6, 0.90, 0.90);
  lg->AddEntry(hist_obs, "Observed", "p");
  lg->AddEntry(hist_pre, "Predicted", "f");
  lg->AddEntry(hist_bkg, "Background", "f");
  lg->Draw();

  c1_down->cd();
  hist_compare->GetXaxis()->SetLabelFont(63);
  hist_compare->GetXaxis()->SetLabelSize(14);
  hist_compare->GetYaxis()->SetLabelFont(63);
  hist_compare->GetYaxis()->SetLabelSize(12);

  line_mid->SetTitle("");
  line_mid->SetLineColor(kRed);
  line_mid->Draw();

  line_mid->SetMaximum(1.5);
  line_mid->SetMinimum(0.5);
  line_mid->GetXaxis()->SetLabelFont(63);
  line_mid->GetXaxis()->SetLabelSize(14);
  line_mid->GetYaxis()->SetLabelFont(63);
  line_mid->GetYaxis()->SetLabelSize(12);
  hist_compare->Draw("same");

  c1->SaveAs(plotpath+"/"+region+scalefactor+"_Z_mass_fit.png");
} 
