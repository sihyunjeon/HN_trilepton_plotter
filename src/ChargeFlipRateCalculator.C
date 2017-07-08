#include "canvas_margin.h"
#include <TPaveStats.h>
#define n_xbins 9
#define n_ybins 4

void ChargeFlipRateCalculator(int XXX, TString YYY){

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

  TH2D *h_numerator_2D[3][3];
  TH2D *h_denominator_2D[3][3];
  TString JETsuffix[3] = {"", "_JETS0", "_JETS"};
  TString HALFsuffix[3] = {"", "_sampleA", "_sampleB"};
  int rebin_size=1;

  for(int bbb=0; bbb<1; bbb++){
    for(int aaa=0; aaa<3; aaa++){
      h_numerator_2D[aaa][bbb] = (TH2D*)(file_tmp->Get("Pt_eta_global"+JETsuffix[aaa]+"_CF"+IDsuffix+HALFsuffix[bbb])->Clone());
      h_denominator_2D[aaa][bbb] = (TH2D*)(file_tmp->Get("Pt_eta_global"+JETsuffix[aaa]+IDsuffix+HALFsuffix[bbb])->Clone());

      for(int ii=0; ii<4; ii++){
        if(ii==2) continue;
        for(int jj=0; jj<6; jj++){
          if((h_numerator_2D[aaa][bbb]->GetBinContent(ii+1,jj+1)) == 0){
  	    h_numerator_2D[aaa][bbb]->SetBinContent(ii+1,jj+1,1.8);
            h_numerator_2D[aaa][bbb]->SetBinError(ii+1,jj+1,1.8);
          }
        }
      }

      h_numerator_2D[aaa][bbb] -> Divide(h_denominator_2D[aaa][bbb]);
      h_numerator_2D[aaa][bbb] -> GetXaxis() -> SetTitle("#eta");
      h_numerator_2D[aaa][bbb] -> GetXaxis() -> SetTitleSize(0.04); 
      h_numerator_2D[aaa][bbb] -> GetYaxis() -> SetTitle("P_{T} [GeV]");
      h_numerator_2D[aaa][bbb] -> GetYaxis() -> SetTitleSize(0.04);

      TCanvas *canvas_2D = new TCanvas("canvas_2D", "", 1600, 900);
      h_numerator_2D[aaa][bbb] -> Draw("colztext");
      canvas_2D->SaveAs(plotpath+"CFrate_2D"+JETsuffix[aaa]+IDsuffix+HALFsuffix[bbb]+".pdf");
      delete canvas_2D;
    }
  }
/*
  TH2D *h_HALFTEST_numerator[2][2];  TH2D *h_HALFTEST_denominator[2][2];  TH2D *h_s_HALFTEST_numerator[2][2]; 
  TH2D *h_REFERENCE_numerator[2][2];  TH2D *h_REFERENCE_denominator[2][2];
  TH1D *h_HALF_comp;  TH1D *h_s_HALF_comp;
  TString s_parameter[2] = {"MET", "HT"};
  TString REFERENCEsuffix[2] = {"_sampleA", "_sampleB"};
  TString HALFTESTsuffix[2] = {"_sampleBTOsampleA", "_sampleATOsampleB"};
  TString s_HALFTESTsuffix[2] = {"_sampleATOsampleA", "_sampleBTOsampleB"};

  for(int bbb=0; bbb<2; bbb++){
    for(int aaa=0; aaa<2; aaa++){
      h_HALFTEST_numerator[aaa][bbb] = (TH2D*)(file_tmp->Get("HALFTEST_"+s_parameter[aaa]+"_global_CF"+IDsuffix+HALFTESTsuffix[bbb])->Clone());
      h_s_HALFTEST_numerator[aaa][bbb] = (TH2D*)(file_tmp->Get("HALFTEST_"+s_parameter[aaa]+"_global_CF"+IDsuffix+s_HALFTESTsuffix[bbb])->Clone());
      h_REFERENCE_numerator[aaa][bbb] = (TH2D*)(file_tmp->Get("HALFTEST_"+s_parameter[aaa]+"_global_CF"+IDsuffix+REFERENCEsuffix[bbb])->Clone());
      h_REFERENCE_denominator[aaa][bbb] = (TH2D*)(file_tmp->Get("HALFTEST_"+s_parameter[aaa]+"_global"+IDsuffix+REFERENCEsuffix[bbb])->Clone());

      for(int ii=0; ii<10; ii++){
        if((h_HALFTEST_numerator[aaa][bbb]->GetBinContent(ii+1)) == 0){
          h_HALFTEST_numerator[aaa][bbb]->SetBinContent(ii+1,1.8);
          h_s_HALFTEST_numerator[aaa][bbb]->SetBinContent(ii+1,1.8);
        }
        if((h_REFERENCE_numerator[aaa][bbb]->GetBinContent(ii+1)) == 0){
          h_REFERENCE_numerator[aaa][bbb]->SetBinError(ii+1,1.8);
        }
      }

      h_s_HALFTEST_numerator[aaa][bbb] -> Rebin(2);
      h_HALFTEST_numerator[aaa][bbb] -> Rebin(2);
      h_REFERENCE_numerator[aaa][bbb] -> Rebin(2);
      h_REFERENCE_denominator[aaa][bbb] -> Rebin(2);
      h_s_HALFTEST_numerator[aaa][bbb] -> Divide(h_REFERENCE_denominator[aaa][bbb]);
      h_HALFTEST_numerator[aaa][bbb] -> Divide(h_REFERENCE_denominator[aaa][bbb]);
      h_REFERENCE_numerator[aaa][bbb] -> Divide(h_REFERENCE_denominator[aaa][bbb]);

      h_s_HALFTEST_numerator[aaa][bbb] -> GetXaxis() -> SetTitle(s_parameter[aaa]);
      h_s_HALFTEST_numerator[aaa][bbb] -> GetXaxis() -> SetTitleSize(0.04);
      h_s_HALFTEST_numerator[aaa][bbb] -> SetLineColor(kGreen);
      h_s_HALFTEST_numerator[aaa][bbb] -> SetLineWidth(2);
      h_HALFTEST_numerator[aaa][bbb] -> GetXaxis() -> SetTitle(s_parameter[aaa]);
      h_HALFTEST_numerator[aaa][bbb] -> GetXaxis() -> SetTitleSize(0.04);
      h_HALFTEST_numerator[aaa][bbb] -> SetLineColor(kBlue);
      h_HALFTEST_numerator[aaa][bbb] -> SetLineWidth(2);
      h_REFERENCE_numerator[aaa][bbb] -> GetXaxis() -> SetTitle(s_parameter[aaa]);
      h_REFERENCE_numerator[aaa][bbb] -> GetXaxis() -> SetTitleSize(0.04);
      h_REFERENCE_numerator[aaa][bbb] -> SetLineColor(kBlack);
      h_REFERENCE_numerator[aaa][bbb] -> SetLineWidth(2);

      TCanvas *canvas_HALF = new TCanvas("canvas", "", 800, 600);
      canvas_HALF->Draw();
      TPad *canvas_HALF_up, *canvas_HALF_down;
      canvas_HALF_up = new TPad("canvas_up", "", 0, 0.25, 1, 1);
      canvas_HALF_down = new TPad("canvas_down", "", 0, 0, 1, 0.32);

      canvas_HALF_down->SetGridx();
      canvas_HALF_down->SetGridy();
      canvas_HALF_up->Draw();
      canvas_HALF_down->Draw();

      canvas_HALF_up->cd();
      h_REFERENCE_numerator[aaa][bbb]->Draw("hist");
      h_REFERENCE_numerator[aaa][bbb]->SetMaximum(0.001);
      h_REFERENCE_numerator[aaa][bbb]->SetMinimum(0.0001);
      h_HALFTEST_numerator[aaa][bbb]->Draw("histsame");
      h_s_HALFTEST_numerator[aaa][bbb]->Draw("histsame");

      canvas_HALF_down->cd();
      h_HALF_comp=(TH1D*)h_HALFTEST_numerator[aaa][bbb]->Clone();
      h_HALF_comp->Divide(h_REFERENCE_numerator[aaa][bbb]);
      h_HALF_comp->SetMarkerStyle(20);

      h_HALF_comp->Draw("");
      h_HALF_comp->SetTitle("");
      line_mid->SetLineColor(kRed);
      line_mid->Draw("same");

      h_HALF_comp->SetMaximum(1.5);
      h_HALF_comp->SetMinimum(0.5);
      h_HALF_comp->GetXaxis()->SetLabelFont(63);
      h_HALF_comp->GetXaxis()->SetLabelSize(14);
      h_HALF_comp->GetYaxis()->SetLabelFont(63);
      h_HALF_comp->GetYaxis()->SetLabelSize(12);

      h_HALF_comp->Draw("same");

      canvas_HALF_up->cd();
      TLegend *lg;
      lg = new TLegend(0.70, 0.7, 0.92, 0.92);
      lg->AddEntry(h_HALFTEST_numerator[aaa][bbb], HALFTESTsuffix[bbb], "l");
      lg->AddEntry(h_REFERENCE_numerator[aaa][bbb], REFERENCEsuffix[bbb], "l");
      lg->Draw();

      canvas_HALF->SaveAs(plotpath+s_parameter[aaa]+"_CFrate"+IDsuffix+REFERENCEsuffix[bbb]+".pdf");
      delete canvas_HALF;
    }
  }
*/
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
  
  TFile* new_file = new TFile(plotpath+"ChargeFlip"+IDsuffix+"_"+YYY+"_v807.root", "RECREATE");
  new_file->cd();
  for(int bbb=0; bbb<1; bbb++){
    for(int aaa=0; aaa<3; aaa++){
      h_numerator_2D[aaa][bbb] -> Write();
    }
  }
  new_file->Close();

//  TFile *file = new TFile(plotpath+"CFRateHist.root");
/*
  TH1D *h_raw[3][3], *h_raw_modified[2][2];
  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++){
      h_raw[i][j] = (TH1D*)(file->Get("invPt_"+s_region[i]+"_CF")->Clone());
    }
  }

  TF1 *lin_fit[3][3], *lin_fit_modified[2][2];
  TString s_pt[3] = {"highpt", "midpt", "lowpt"};
  double mid_xxx1[3] = {0.,}, mid_xxx2[3] = {0.,};
  mid_xxx1[0] = 0.00;  mid_xxx1[1] = 0.01;  mid_xxx1[2] = 0.01;
  mid_xxx2[0] = 0.00;  mid_xxx2[1] = 0.02;  mid_xxx2[2] = 0.02;

  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++){
      TString name_temp = s_region[i]+"_invPt_vs_CF_"+s_pt[j];
      if(j==0){
	lin_fit[i][j] = new TF1(name_temp, "pol1", 0.00, mid_xxx1[i]);
	lin_fit[i][j]->SetLineColor(kRed);
      }
      if(j==1){
	lin_fit[i][j] = new TF1(name_temp, "pol1", mid_xxx1[i], mid_xxx2[i]);
	lin_fit[i][j]->SetLineColor(kBlue);
      }
      if(j==2){
        lin_fit[i][j] = new TF1(name_temp, "pol1", mid_xxx2[i], 0.05);
        lin_fit[i][j]->SetLineColor(kGreen);
      }

      lin_fit[i][j] ->SetParNames("offset","slope");
      lin_fit[i][j] ->SetParameters(-0.1,0.1);

      if(j==0) h_raw[i][j]->Fit(name_temp,"","N",0.00,mid_xxx1[i]);
      if(j==1) h_raw[i][j]->Fit(name_temp,"","N",mid_xxx1[i],mid_xxx2[i]);
      if(j==2) h_raw[i][j]->Fit(name_temp,"","N",mid_xxx2[i],0.05);
    }
  }
  gStyle->SetOptFit();
  TPaveStats *pave[3][3];

  for(int i=0; i<3; i++){
    TCanvas *canvas = new TCanvas("canvas", "", 800, 600);

    h_raw[i][0]->Draw("EP");
    h_raw[i][0]->GetXaxis()->SetRangeUser(0.00,0.05);
    h_raw[i][1]->SetLineColor(kGray+1);
    h_raw[i][1]->SetMarkerStyle(10);
    h_raw[i][1]->Draw("EPsames");
    h_raw[i][2]->SetLineColor(kGray+1);
    h_raw[i][2]->SetMarkerStyle(10);
    h_raw[i][2]->Draw("EPsames");

    canvas->Update();
    pave[i][0] = (TPaveStats*)h_raw[i][0]->FindObject("stats");
    pave[i][0]->SetX1NDC(.70);
    pave[i][0]->SetX2NDC(.95);
    pave[i][0]->SetY1NDC(.75);
    pave[i][0]->SetY2NDC(.92);
    pave[i][0]->SetTextColor(kRed);
    pave[i][0]->SetFillColor(kGray+1);

    pave[i][1] = (TPaveStats*)h_raw[i][1]->FindObject("stats");
    pave[i][1]->SetX1NDC(.70);
    pave[i][1]->SetX2NDC(.95);
    pave[i][1]->SetY1NDC(.58);
    pave[i][1]->SetY2NDC(.75);
    pave[i][1]->SetTextColor(kBlue);
    pave[i][1]->SetFillColor(kGray+1);

    pave[i][2] = (TPaveStats*)h_raw[i][2]->FindObject("stats");
    pave[i][2]->SetX1NDC(.70);
    pave[i][2]->SetX2NDC(.95);
    pave[i][2]->SetY1NDC(.41);
    pave[i][2]->SetY2NDC(.58);
    pave[i][2]->SetTextColor(kGreen);
    pave[i][2]->SetFillColor(kGray+1);

    canvas->SaveAs(plotpath+"CFrate_"+s_region[i]+"_linear_fit.pdf");
    delete canvas;
  }


  TFile* new_new_file = new TFile(plotpath+"CFRateHistFit.root", "RECREATE");
  new_new_file->cd();
  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++){//FIXME
      h_raw[i][j]->Write();
    }
  }
  new_new_file->Close();*/
}

