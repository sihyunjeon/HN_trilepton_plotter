#include "canvas_margin.h"
#include <TPaveStats.h>
#define n_xbins 9
#define n_ybins 4

void ChargeFlipSFCalculator( int XXX, TString YYY ){

  gStyle->SetOptStat(0);
  gStyle->SetPaintTextFormat("1.6f");
  TH1::AddDirectory(kFALSE);

  TString IDsuffix = "";
  if(XXX == 0) IDsuffix = "_MVATIGHT";
  if(XXX == 1) IDsuffix = "_HNTIGHT";
  TString SAMPLEsuffix = "";
  if(YYY == "powheg") SAMPLEsuffix = "_powheg";
  if(YYY == "madgraph") SAMPLEsuffix = "_madgraph";

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");  
  TString filepath = WORKING_DIR+"/rootfiles/v8-0-7.9/CFRateCalculator/";
  TString plotpath = WORKING_DIR+"/plots/v8-0-7.9/CFRateCalculator/ScaleFactor/"+IDsuffix+"/";
  TString catversion = "v8-0-7";

  if( !gSystem->mkdir(plotpath, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }

  TF1 *line_mid = new TF1("line_mid","1", 70., 110.);

  TFile *file_data = new TFile(filepath+"/CFRateCalculator_data_DoubleEG_cat_"+catversion+".root");
  TFile *file_fake_bkg = new TFile(filepath+"/CFRateCalculator_FR_DoubleEG_SKnonprompt_dilep_cat_"+catversion+".root");

  const int n_region = 4;
  const int n_SFsuffix = 2;
  const int n_JETsuffix = 4;
  const int n_Zsuffix = 4;

  TString s_region[n_region] = {"BB",  "EE", "BE", "global"};
  TString s_region_title[n_region] = {"Barrel_Barrel", "Endcap_Endcap", "Barrel_Endcap", "Global"};
  TString SFsuffix[n_SFsuffix] = {"", "_SF"};
  TString JETsuffix[n_JETsuffix] = {"_", "_JETS0_", "_JETS_", "_JETS1_"};
  TString Zsuffix[n_Zsuffix] = {"", "_narrowZ", "_wideZ", "_verywideZ"}; 

  TH1D *h_wide_obs[n_region], *h_wide_bkg[n_region];
  
  for(int i=0; i<4; i++){
    h_wide_obs[i] = (TH1D*)(file_data->Get("FIT_observed_Z_mass_"+s_region[i]+"_HNTIGHT")->Clone());
    h_wide_bkg[i] = (TH1D*)(file_fake_bkg->Get("FIT_observed_Z_mass_"+s_region[i]+"_HNTIGHT")->Clone());

    TCanvas *canvas_temp_Z_mass_wide = new TCanvas("canvas", "", 800, 600);

    h_wide_obs[i] -> Draw();
    h_wide_bkg[i] -> SetFillColor(kAzure+8);
    h_wide_bkg[i] -> SetLineColor(kAzure+8);
    h_wide_bkg[i] -> Draw("samehist");
    h_wide_obs[i] -> Draw("same");

    canvas_temp_Z_mass_wide->SaveAs(plotpath+"FIT_observed_Z_mass_"+s_region[i]+"_HNTIGHT.pdf");
    delete canvas_temp_Z_mass_wide;
  }

  THStack *h_stack[n_region][n_SFsuffix][n_JETsuffix][n_Zsuffix];
  for(int i=0; i<n_region;i ++){
    for(int j=0; j<n_SFsuffix; j++){
      for(int k=0; k<n_JETsuffix; k++){
        for(int l=0; l<n_Zsuffix; l++){
          h_stack[i][j][k][l] = new THStack("stack_"+s_region[i], s_region_title[i]+"_Z_mass"+JETsuffix[k]+Zsuffix[l]+SFsuffix[j]);
        }
      }
    }
  }

  TH1D *h_data_Z_mass_obs[n_region][n_SFsuffix][n_JETsuffix][n_Zsuffix], *h_fake_bkg_Z_mass_obs[n_region][n_SFsuffix][n_JETsuffix][n_Zsuffix], *h_data_Z_mass_pre[n_region][n_SFsuffix][n_JETsuffix][n_Zsuffix];
  TH1D *h_data_n_events_obs[n_region][n_SFsuffix][n_JETsuffix][n_Zsuffix], *h_fake_bkg_n_events_obs[n_region][n_SFsuffix][n_JETsuffix][n_Zsuffix], *h_data_n_events_pre[n_region][n_SFsuffix][n_JETsuffix][n_Zsuffix];
  TH1D *h_Z_mass_comp;
  double n_events_data_obs[n_region][n_SFsuffix][n_JETsuffix][n_Zsuffix], n_events_fake_bkg_obs[n_region][n_SFsuffix][n_JETsuffix][n_Zsuffix], n_events_data_pre[n_region][n_SFsuffix][n_JETsuffix][n_Zsuffix];
  double error_data_obs[n_region][n_SFsuffix][n_JETsuffix][n_Zsuffix], error_fake_bkg_obs[n_region][n_SFsuffix][n_JETsuffix][n_Zsuffix], error_data_pre[n_region][n_SFsuffix][n_JETsuffix][n_Zsuffix], error_num[n_region][n_SFsuffix][n_JETsuffix][n_Zsuffix], error_den[n_region][n_SFsuffix][n_JETsuffix][n_Zsuffix], error_tot[n_region][n_SFsuffix][n_JETsuffix][n_Zsuffix];

  double center_value = -999.;

  for(int ddd=0; ddd<n_Zsuffix; ddd++){
    for(int ccc=0; ccc<n_JETsuffix; ccc++){//jet suffix
      for(int bbb=0; bbb<n_SFsuffix; bbb++){//SF suffix
        for(int aaa=0; aaa<n_region; aaa++){//region suffix
          h_data_Z_mass_obs[aaa][bbb][ccc][ddd] = (TH1D*)(file_data->Get("observed_Z_mass"+JETsuffix[ccc]+s_region[aaa]+IDsuffix+SAMPLEsuffix+Zsuffix[ddd])->Clone());
          h_data_Z_mass_pre[aaa][bbb][ccc][ddd] = (TH1D*)(file_data->Get("predicted_Z_mass"+JETsuffix[ccc]+s_region[aaa]+IDsuffix+SAMPLEsuffix+SFsuffix[bbb]+Zsuffix[ddd])->Clone());
          h_fake_bkg_Z_mass_obs[aaa][bbb][ccc][ddd] = (TH1D*)(file_fake_bkg->Get("observed_Z_mass"+JETsuffix[ccc]+s_region[aaa]+IDsuffix+Zsuffix[ddd])->Clone());
          h_Z_mass_comp = (TH1D*)h_data_Z_mass_obs[aaa][bbb][ccc][ddd]->Clone();
          h_Z_mass_comp->Add(h_fake_bkg_Z_mass_obs[aaa][bbb][ccc][ddd], -1.);
          h_Z_mass_comp->Divide(h_data_Z_mass_pre[aaa][bbb][ccc][ddd]);

          h_data_n_events_obs[aaa][bbb][ccc][ddd] = (TH1D*)(file_data->Get("observed_n_events"+JETsuffix[ccc]+s_region[aaa]+IDsuffix+SAMPLEsuffix+Zsuffix[ddd])->Clone());
          h_data_n_events_pre[aaa][bbb][ccc][ddd] = (TH1D*)(file_data->Get("predicted_n_events"+JETsuffix[ccc]+s_region[aaa]+IDsuffix+SAMPLEsuffix+SFsuffix[bbb]+Zsuffix[ddd])->Clone());
          h_fake_bkg_n_events_obs[aaa][bbb][ccc][ddd] = (TH1D*)(file_fake_bkg->Get("observed_n_events"+JETsuffix[ccc]+s_region[aaa]+IDsuffix+Zsuffix[ddd])->Clone());
          TCanvas *canvas_temp_Z_mass = new TCanvas("canvas", "", 800, 600);
          canvas_temp_Z_mass->Draw();
          TPad *canvas_temp_Z_mass_up, *canvas_temp_Z_mass_down;
          canvas_temp_Z_mass_up = new TPad("canvas_up", "", 0, 0.25, 1, 1);
          canvas_temp_Z_mass_down = new TPad("canvas_down", "", 0, 0, 1, 0.32);
  
          canvas_temp_Z_mass_down->SetGridx();
          canvas_temp_Z_mass_down->SetGridy();
          canvas_temp_Z_mass_up->Draw();
          canvas_temp_Z_mass_down->Draw();

          canvas_temp_Z_mass_up->cd();
          h_data_Z_mass_obs[aaa][bbb][ccc][ddd]->SetMarkerStyle(20);
          h_data_Z_mass_pre[aaa][bbb][ccc][ddd]->SetLineColor(kAzure+8);
          h_data_Z_mass_pre[aaa][bbb][ccc][ddd]->SetFillColor(kAzure+8);

          h_data_Z_mass_obs[aaa][bbb][ccc][ddd]->Add(h_fake_bkg_Z_mass_obs[aaa][bbb][ccc][ddd], -1.);
          h_stack[aaa][bbb][ccc][ddd]->Add(h_data_Z_mass_pre[aaa][bbb][ccc][ddd]);

          //if(aaa == 3) h_stack[aaa][bbb][ccc]->SetMaximum(100);
          h_stack[aaa][bbb][ccc][ddd]->SetMaximum(80);
          h_stack[aaa][bbb][ccc][ddd]->Draw("hist");
          h_data_Z_mass_obs[aaa][bbb][ccc][ddd]->Draw("same");

          TLegend *lg;
          lg = new TLegend(0.70, 0.6, 0.90, 0.90);
          lg->AddEntry(h_data_Z_mass_obs[aaa][bbb][ccc][ddd], "observed", "p");
          lg->AddEntry(h_data_Z_mass_pre[aaa][bbb][ccc][ddd], "predicted", "f");
//        lg->AddEntry(h_fake_bkg_Z_mass_obs[aaa][bbb][ccc], "fake", "f");

          lg->Draw();

          canvas_temp_Z_mass_down->cd();
          line_mid->SetTitle("");
          line_mid->SetMarkerStyle(20);
          line_mid->SetMarkerSize(0.2);
          line_mid->GetXaxis()->SetLabelFont(63);
          line_mid->GetXaxis()->SetLabelSize(14);
          line_mid->GetYaxis()->SetLabelFont(63);
          line_mid->GetYaxis()->SetLabelSize(12);
          line_mid->SetMaximum(1.5);
          line_mid->SetMinimum(0.5);
          line_mid->Draw("");
          h_Z_mass_comp->Draw("sameE1");

          canvas_temp_Z_mass->SaveAs(plotpath+"SS_Z_mass"+JETsuffix[ccc]+s_region[aaa]+IDsuffix+SAMPLEsuffix+Zsuffix[ddd]+SFsuffix[bbb]+".pdf");
          delete canvas_temp_Z_mass;

          n_events_data_obs[aaa][bbb][ccc][ddd] = h_data_n_events_obs[aaa][bbb][ccc][ddd]->GetBinContent(1);
          n_events_data_pre[aaa][bbb][ccc][ddd] = h_data_n_events_pre[aaa][bbb][ccc][ddd]->GetBinContent(1);
          n_events_fake_bkg_obs[aaa][bbb][ccc][ddd] = h_fake_bkg_n_events_obs[aaa][bbb][ccc][ddd]->GetBinContent(1);
	  error_data_obs[aaa][bbb][ccc][ddd] = TMath::Sqrt(n_events_data_obs[aaa][bbb][ccc][ddd]);
	  error_data_pre[aaa][bbb][ccc][ddd] = TMath::Sqrt(n_events_data_pre[aaa][bbb][ccc][ddd]);
	  error_fake_bkg_obs[aaa][bbb][ccc][ddd] = TMath::Sqrt(n_events_fake_bkg_obs[aaa][bbb][ccc][ddd]);
          error_num[aaa][bbb][ccc][ddd] = TMath::Sqrt(error_data_obs[aaa][bbb][ccc][ddd]*error_data_obs[aaa][bbb][ccc][ddd]+error_fake_bkg_obs[aaa][bbb][ccc][ddd]*error_fake_bkg_obs[aaa][bbb][ccc][ddd]);
          error_den[aaa][bbb][ccc][ddd] = TMath::Sqrt(n_events_data_pre[aaa][bbb][ccc][ddd]);
        }
      }
    }
  }
  double scalefactor[n_region][n_SFsuffix][n_JETsuffix][n_Zsuffix]={{{{0.,},},},};
  for(int ddd=0; ddd<n_Zsuffix; ddd++){
    for(int ccc=0; ccc<n_JETsuffix; ccc++){
      for(int bbb=0; bbb<n_SFsuffix; bbb++){
        for(int aaa=0; aaa<n_region; aaa++){
          scalefactor[aaa][bbb][ccc][ddd] = fabs(n_events_data_obs[aaa][bbb][ccc][ddd] - n_events_fake_bkg_obs[aaa][bbb][ccc][ddd])/n_events_data_pre[aaa][bbb][ccc][ddd];
	  error_tot[aaa][bbb][ccc][ddd] = scalefactor[aaa][bbb][ccc][ddd]*TMath::Sqrt((error_num[aaa][bbb][ccc][ddd]/(n_events_data_obs[aaa][bbb][ccc][ddd]-n_events_fake_bkg_obs[aaa][bbb][ccc][ddd]))*(error_num[aaa][bbb][ccc][ddd]/(n_events_data_obs[aaa][bbb][ccc][ddd]-n_events_fake_bkg_obs[aaa][bbb][ccc][ddd])) + (error_den[aaa][bbb][ccc][ddd]/n_events_data_pre[aaa][bbb][ccc][ddd])*(error_den[aaa][bbb][ccc][ddd]/n_events_data_pre[aaa][bbb][ccc][ddd]));
//cout<<error_num[aaa][bbb][ccc][ddd]<<" "<<n_events_data_obs[aaa][bbb][ccc][ddd]-n_events_fake_bkg_obs[aaa][bbb][ccc][ddd]<<endl;
//cout<<error_den[aaa][bbb][ccc][ddd]<<" "<<n_events_data_pre[aaa][bbb][ccc][ddd]<<endl;
//cout<<error_tot[aaa][bbb][ccc][ddd]<<endl;
        }
      }
    }
  }
  double uncert_sum = 0.;

  cout << " ***************************************************************** " << endl;
  for(int ddd=0; ddd<n_Zsuffix; ddd++){
    for(int aaa=0; aaa<n_region; aaa++){
      cout <<
      " " << s_region_title[aaa]+Zsuffix[ddd] << endl <<
      " >>> n_obs : " << n_events_data_obs[aaa][0][0][ddd] << endl <<
      " >>> n_bkg : " << n_events_fake_bkg_obs[aaa][0][0][ddd] << endl <<
      " >>> n_pre : " << n_events_data_pre[aaa][0][0][ddd] << endl <<
      " ========> before scale factor : " << scalefactor[aaa][0][0][ddd] << " +- " << error_tot[aaa][0][0][ddd] << endl <<
      " ====> 0 jets : << scalefactor   : " << scalefactor[aaa][0][1][ddd] << endl <<
      " ====> non0 jets : << scalefactor   : " << scalefactor[aaa][0][2][ddd] << endl <<
      " ====> 1 jets : << scalefactor   : " << scalefactor[aaa][0][3][ddd] << endl <<
      " ========> after scale factor  : " << scalefactor[aaa][1][0][ddd] << " +- " << error_tot[aaa][0][0][ddd] << endl << 
      " ====> 0 jets : << scalefactor   : " << scalefactor[aaa][1][1][ddd] << endl <<
      " ====> non0 jets : << scalefactor   : " << scalefactor[aaa][1][2][ddd] << endl <<
      " ====> 1 jets : << scalefactor   : " << scalefactor[aaa][1][3][ddd] << endl <<
      " ***************************************************************** " << endl;
      if(aaa==3 && ddd==0) center_value = scalefactor[aaa][1][0][ddd];

      if(aaa==3) uncert_sum+=((scalefactor[aaa][1][0][ddd]-center_value)/center_value)*((scalefactor[aaa][1][0][ddd]-center_value)/center_value);
//      cout<<uncert_sum<<endl;
    }
  }
cout<<TMath::Sqrt(uncert_sum)<<endl;
  return;
}
