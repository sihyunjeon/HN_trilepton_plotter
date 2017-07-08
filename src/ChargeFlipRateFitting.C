#include "canvas_margin.h"
#include <TPaveStats.h>
#define n_xbins 9
#define n_ybins 4

void ChargeFlipRateFitting(int XXX, TString YYY){

  gStyle->SetOptStat(0);
  gStyle->SetPaintTextFormat("1.6f");
  TH1::AddDirectory(kFALSE);

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");  
  TString filepath = WORKING_DIR+"/rootfiles/v8-0-7.18/CFRateCalculator/";
  TString plotpath = WORKING_DIR+"/plots/v8-0-7.18/CFRateCalculator/";

  TString IDsuffix = "", samplesuffix = "", samplename;
  if(XXX == 0) IDsuffix = "_MVATIGHT_PU";
  if(XXX == 1) IDsuffix = "_HNTIGHT_PU";
  if(YYY == "madgraph"){ samplesuffix = "MadGraph/"; samplename = "DYJets_MG"; IDsuffix += "_madgraph";}
  if(YYY == "powheg"){ samplesuffix = "Powheg/"; samplename = "DYtoEE"; IDsuffix += "_powheg";}

  plotpath += samplesuffix + IDsuffix+"/";
  
  if( !gSystem->mkdir(plotpath, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }

  TF1 *line_mid = new TF1("line_mid","1", 0., 200.);
  TFile *file_tmp = new TFile(filepath+"/CFRateCalculator_SK"+samplename+"_cat_v8-0-7.root");

  TH1D *MCc_observed_SS, *MCc_observed_SS_err;
  TH1D *MCc_predicted_SS, *MCc_predicted_SS_err;
  TH1D *MCc_comp;
  TString closure_suffix[3] = {"Z_mass", "leading_lep_Pt", "subleading_lep_Pt"};
  TString Z_suffix[3] = {"", "_wideZ", "_verywideZ"};

  for(int z=0; z<3; z++){
    for(int i=0; i<3; i++){
      MCc_observed_SS = (TH1D*)(file_tmp->Get("MCClosure_"+closure_suffix[i]+"_obs"+Z_suffix[z])->Clone());
      MCc_predicted_SS = (TH1D*)(file_tmp->Get("MCClosure_"+closure_suffix[i]+"_pre"+Z_suffix[z])->Clone());

      //MCc_observed_SS->GetXaxis()->SetRangeUser(0.,100.);

      if(i!=0){MCc_observed_SS->Rebin(5);MCc_predicted_SS->Rebin(5);}
      MCc_observed_SS_err = (TH1D*)(MCc_observed_SS->Clone());
      MCc_predicted_SS_err = (TH1D*)(MCc_predicted_SS->Clone());


      MCc_comp = (TH1D*)(MCc_predicted_SS->Clone());
      MCc_comp->Divide(MCc_observed_SS);

      TCanvas *canvas_closure = new TCanvas("canvas_closure", "", 600, 600);
      canvas_closure->Draw();
      TPad *c1_up;
      TPad *c1_down;
      c1_up = new TPad("c1_up", "", 0, 0.25, 1, 1);
      c1_down = new TPad("c1_down", "", 0, 0, 1, 0.32);

      c1_down->SetGridx();
      c1_down->SetGridy();
      c1_up->Draw();
      c1_down->Draw();

      c1_up->cd();
      MCc_observed_SS->SetFillColor(kYellow);
      MCc_observed_SS->SetLineColor(kYellow);
      MCc_observed_SS_err->SetFillColor(kYellow-6);
      MCc_observed_SS_err->SetFillStyle(3144);
      MCc_observed_SS_err->SetLineColor(kYellow-6);
      if(i!=0)MCc_observed_SS->GetXaxis()->SetRangeUser(0.,100.);

      MCc_observed_SS->Draw("hist");
      MCc_observed_SS_err->Draw("sameE2");
      MCc_predicted_SS->SetMarkerStyle(20);
      MCc_predicted_SS->SetMarkerSize(0.5);
      MCc_predicted_SS->Draw("same");

      if(i==0)MCc_observed_SS->SetMaximum(200);
      else MCc_observed_SS->SetMaximum(400);

      TLegend *lg;
      lg = new TLegend(0.75, 0.7, 0.90, 0.90);
      lg->AddEntry(MCc_observed_SS, "Observed", "f");
      lg->AddEntry(MCc_predicted_SS, "Predicted", "p");
      lg->Draw();

      c1_down->cd();
      MCc_comp->GetXaxis()->SetLabelFont(63);
      MCc_comp->GetXaxis()->SetLabelSize(15);
      MCc_comp->GetYaxis()->SetLabelFont(63);
      MCc_comp->GetYaxis()->SetLabelSize(15);
      MCc_comp->SetMinimum(0.5);
      MCc_comp->SetMaximum(1.5);
      if(i!=0)MCc_comp->GetXaxis()->SetRangeUser(0.,100.);

      MCc_comp->Draw("");
      line_mid->Draw("same");
      MCc_comp->Draw("same");
      MCc_comp->SetTitle("");
      canvas_closure->SaveAs(plotpath+"MCClosure_"+closure_suffix[i]+Z_suffix[z]+".pdf");
      delete canvas_closure;
    }
  }

  file_tmp->cd();
  TH1D *h_observed_SS, *h_observed_SS_error;
  h_observed_SS = (TH1D*)(file_tmp->Get("RECO_Z_mass_SS"+IDsuffix)->Clone());
  h_observed_SS_error = (TH1D*)(file_tmp->Get("RECO_Z_mass_SS"+IDsuffix)->Clone());
//  h_observed_SS_CFToCF = (TH1D*)(file_tmp->Get("RECO_Z_mass_SS_CFrateToCFEl"+IDsuffix)->Clone());
  Double_t scale_SS = 100./(h_observed_SS->Integral());
//  Double_t scale_SS_CFToCF = 100./(h_observed_SS_CFToCF->Integral());
  h_observed_SS->Scale(scale_SS);
  h_observed_SS_error->Scale(scale_SS);
//  h_observed_SS_CFToCF->Scale(scale_SS_CFToCF);
  double content_SS[40] = {0.};
  for(int i_bin = 1; i_bin<41 ; i_bin++){
    content_SS[i_bin-1] = h_observed_SS->GetBinContent(i_bin);
  }
  double sum_ratio[50] = {0.};
  for(int i=0; i<51; i++){
    TString s_shift = TString::Itoa(i, 10);

    TH1D *h_predicted_SHIFT_OS;
    h_predicted_SHIFT_OS = (TH1D*)(file_tmp->Get("RECO_Z_mass_OS"+IDsuffix+"_SHIFT_"+s_shift+"div1000")->Clone());

    Double_t scale_SHIFT_OS = 100./(h_predicted_SHIFT_OS->Integral());
    h_predicted_SHIFT_OS->Scale(scale_SHIFT_OS);

    double content_SHIFT_OS[40] = {0.};
    double ratio[40] = {0.};
    for(int i_bin = 1; i_bin<41; i_bin++){
     content_SHIFT_OS[i_bin-1] = h_predicted_SHIFT_OS->GetBinContent(i_bin);
     if(content_SS[i_bin-1]!=0) ratio[i_bin-1] = fabs((content_SHIFT_OS[i_bin-1]-content_SS[i_bin-1])*(content_SHIFT_OS[i_bin-1]-content_SS[i_bin-1])/content_SS[i_bin-1]);
     else{
       double temp_content_SS = 1.8;
       ratio[i_bin-1] = fabs((content_SHIFT_OS[i_bin-1]-temp_content_SS)*(content_SHIFT_OS[i_bin-1]-temp_content_SS)/temp_content_SS);
     }
    }

    for(int i_bin = 11; i_bin<31; i_bin++){
      sum_ratio[i] += ratio[i_bin-1];
    }

    TCanvas *canvas_shift = new TCanvas("canvas", "", 800, 600);

    h_observed_SS->SetFillColor(kOrange-4);
    h_observed_SS->SetLineColor(kOrange-4);
    h_observed_SS_error->SetFillStyle(3144);
    h_observed_SS_error->SetFillColor(kOrange-5);
//    h_observed_SS_CFToCF->SetLineColor(kRed);
//    h_observed_SS_CFToCF->SetLineWidth(3.);
    h_predicted_SHIFT_OS->SetMarkerStyle(20);

    h_observed_SS->Draw("hist");
//    h_observed_SS_error->Draw("sameE2");
//    h_observed_SS_CFToCF->Draw("samehist");
    h_predicted_SHIFT_OS->Draw("samePE1");
    
    h_observed_SS->SetTitle("RECO_Z_mass_OS"+IDsuffix+"_SHIFT_"+s_shift+"div1000");
    h_observed_SS->SetMaximum(20);

    TLegend *lg;
    lg = new TLegend(0.70, 0.6, 0.92, 0.92);
    lg->AddEntry(h_observed_SS, "Observed", "f");
    lg->AddEntry(h_predicted_SHIFT_OS, "Predicted", "p");
//    lg->AddEntry(h_observed_SS_CFToCF, "CFrateToCFel", "l");
    lg->Draw();

    canvas_shift->SaveAs(plotpath+"RECO_Z_mass_OS_SHIFT_"+s_shift+"div1000"+IDsuffix+".pdf");
    delete canvas_shift;
  }

  double min_sum_ratio = 999.;
  int min_sum_ratio_E_shift = 999;
  for(int i=0; i<51; i++){
//    cout << "E shift = " << i << "/1000   sum of ratio : " << sum_ratio[i] << endl;
    if(sum_ratio[i]<min_sum_ratio){
      min_sum_ratio_E_shift = i;
      min_sum_ratio = sum_ratio[i];
    }
  }
  cout << "minimum sum of ratio : " << min_sum_ratio_E_shift << "/1000  :: " << min_sum_ratio<<endl;
  
  TFile *file_tmp_2 = new TFile(filepath+"/CFRateCalculator_SK"+samplename+"_cat_v8-0-7.root");

  TString region_suffix[3] = {"_region1","_region2","_region3"};
  int bin_size = 1;
  TH1D *h_fit_numerator[3];  TH1D *h_fit_denominator[3];  TH1D *h_fit_chargeflip[3][3];
  for(int i=0; i<3; i++){
    h_fit_numerator[i] = (TH1D*)(file_tmp_2->Get("invPt"+region_suffix[i]+"_CF"+IDsuffix)->Clone());
    h_fit_numerator[i] ->Rebin(bin_size);
    TCanvas *canvas_num = new TCanvas("canvas", "", 800, 600);
    h_fit_numerator[i]->Draw();
    canvas_num->SaveAs(plotpath+"invPt"+region_suffix[i]+"_CFelectrons"+IDsuffix+".pdf");
    delete canvas_num;

    h_fit_denominator[i] = (TH1D*)(file_tmp_2->Get("invPt"+region_suffix[i]+IDsuffix)->Clone());
    h_fit_denominator[i] ->Rebin(bin_size);
    h_fit_numerator[i]-> Divide(h_fit_numerator[i],h_fit_denominator[i], 1, 1, "b");
    for(int j=0; j<3; j++){
      h_fit_chargeflip[i][j]=((TH1D*)h_fit_numerator[i]->Clone());
    }
    TCanvas *canvas_fit = new TCanvas("canvas", "", 800, 600);
    h_fit_chargeflip[i][0]->Draw();
    canvas_fit->SaveAs(plotpath+"invPt"+region_suffix[i]+"_CF"+IDsuffix+".pdf");
    delete canvas_fit;
  }

  TF1 *lin_fit[3][3];
  TString s_pt[3] = {"_highpt", "_midpt", "_lowpt"};
  double mid_xxx1[3] = {0.,}, mid_xxx2[3] = {0.,}, mid_xxx3[3] = {0.,};
  mid_xxx1[0] = 0.023;  mid_xxx1[1] = 0.016; mid_xxx1[2] = 0.012;
  mid_xxx2[0] = 0.040;  mid_xxx2[1] = 0.024; mid_xxx2[2] = 0.020;
  mid_xxx3[0] = 0.040;  mid_xxx3[1] = 0.040; mid_xxx3[2] = 0.040;

  double maxs[3] = {0.0001, 0.002, 0.01};

  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++){
      TString name_temp = "invPt_vs_CF_"+region_suffix[i]+s_pt[j];
      if(j==0){
	lin_fit[i][j] = new TF1(name_temp, "pol1", 0.00, mid_xxx1[i]);
	lin_fit[i][j]->SetLineColor(kRed);
      }
      if(j==1){
	lin_fit[i][j] = new TF1(name_temp, "pol1", mid_xxx1[i], mid_xxx2[i]);
	lin_fit[i][j]->SetLineColor(kBlue);
      }
      if(j==2){
        lin_fit[i][j] = new TF1(name_temp, "pol1", mid_xxx2[i], mid_xxx3[i]);
        lin_fit[i][j]->SetLineColor(kGreen);
      }

      lin_fit[i][j] ->SetParNames("offset","slope");
      lin_fit[i][j] ->SetParameters(-0.1,0.1);

      if(j==0) h_fit_chargeflip[i][j]->Fit(name_temp,"","N",0.00,mid_xxx1[i]);
      if(j==1) h_fit_chargeflip[i][j]->Fit(name_temp,"","N",mid_xxx1[i],mid_xxx2[i]);
      if(j==2) h_fit_chargeflip[i][j]->Fit(name_temp,"","N",mid_xxx2[i],mid_xxx3[i]);
    }
  }
  gStyle->SetOptFit();
  TPaveStats *pave[3][3];

  for(int i=0; i<3; i++){
    TCanvas *canvas = new TCanvas("canvas", "", 800, 600);

    h_fit_chargeflip[i][0]->Draw("EP");
    h_fit_chargeflip[i][0]->GetXaxis()->SetRangeUser(0.00,0.05);
    h_fit_chargeflip[i][1]->SetLineColor(kGray+1);
    h_fit_chargeflip[i][1]->SetMarkerStyle(10);
    h_fit_chargeflip[i][1]->Draw("EPsames");
    if(i==1 || i==2){
      h_fit_chargeflip[i][2]->SetLineColor(kGray+1);
      h_fit_chargeflip[i][2]->SetMarkerStyle(10);
      h_fit_chargeflip[i][2]->Draw("EPsames");
    }
    h_fit_chargeflip[i][0]->SetMaximum(maxs[i]);
    
    canvas->Update();
    pave[i][0] = (TPaveStats*)h_fit_chargeflip[i][0]->FindObject("stats");
    pave[i][0]->SetX1NDC(.70);
    pave[i][0]->SetX2NDC(.95);
    pave[i][0]->SetY1NDC(.75);
    pave[i][0]->SetY2NDC(.92);
    pave[i][0]->SetTextColor(kRed);
    pave[i][0]->SetFillColor(kGray+1);

    pave[i][1] = (TPaveStats*)h_fit_chargeflip[i][1]->FindObject("stats");
    pave[i][1]->SetX1NDC(.70);
    pave[i][1]->SetX2NDC(.95);
    pave[i][1]->SetY1NDC(.58);
    pave[i][1]->SetY2NDC(.75);
    pave[i][1]->SetTextColor(kBlue);
    pave[i][1]->SetFillColor(kGray+1);

    if(i==1 || i==2){
      pave[i][2] = (TPaveStats*)h_fit_chargeflip[i][2]->FindObject("stats");
      pave[i][2]->SetX1NDC(.70);
      pave[i][2]->SetX2NDC(.95);
      pave[i][2]->SetY1NDC(.41);
      pave[i][2]->SetY2NDC(.58);
      pave[i][2]->SetTextColor(kGreen);
      pave[i][2]->SetFillColor(kGray+1);
    }
    canvas->SaveAs(plotpath+"invPt"+region_suffix[i]+"_CF"+IDsuffix+"_linear_fit.pdf");
    delete canvas;
  }


  TFile* new_new_file = new TFile(plotpath+"CFRateHistFit.root", "RECREATE");
  new_new_file->cd();
  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++){//FIXME
      h_fit_chargeflip[i][j]->Write();
    }
  }
  new_new_file->Close();




}

