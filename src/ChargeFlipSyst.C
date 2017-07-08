#include "canvas_margin.h"
#include <TPaveStats.h>
#define n_xbins 9
#define n_ybins 4

void ChargeFlipSyst( int XXX, TString YYY ){

  double central_sf = 0.;
  double uncert_sum = 0.;

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
  TString plotpath = WORKING_DIR+"/plots/v8-0-7.9/CFRateCalculator/Systematic/"+IDsuffix+"/";
  TString catversion = "v8-0-7";

  if( !gSystem->mkdir(plotpath, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }

  TF1 *line_mid = new TF1("line_mid","1", 70., 110.);

  TFile *file_data = new TFile(filepath+"/CFRateCalculator_syst_data_DoubleEG_cat_"+catversion+".root");
  TFile *file_fake_bkg = new TFile(filepath+"/CFRateCalculator_FR_syst_DoubleEG_SKnonprompt_dilep_cat_"+catversion+".root");

  const int n_syst = 5;
  const int n_CF_syst = 3;
  const int n_region = 5;
  const int n_SFsuffix = 2;
  const int n_JETsuffix = 4;

  TString s_syst[n_syst] = {"Central", "ElectronE_Up", "ElectronE_Down", "Unclustered_Up", "Unclustered_Down"};
  TString s_CF_syst[n_CF_syst] = {"", "_CFup", "_CFdown"};
  TString s_region[n_region] = {"iBiB", "oBoB", "EE", "BE", "global"};
  TString s_region_title[n_region] = {"iBarrel_iBarrel", "oBarrel_oBarrel", "Endcap_Endcap", "Barrel_Endcap", "Global"};
  TString SFsuffix[n_SFsuffix] = {"", "_SF"};
  TString JETsuffix[n_JETsuffix] = {"_", "_JETS0_", "_JETS_", "_JETS1_"};

  for(int it_syst = 0; it_syst<n_syst; it_syst++){
    TH1D *h_data_n_events_obs[n_region][n_SFsuffix][n_JETsuffix], *h_fake_bkg_n_events_obs[n_region][n_SFsuffix][n_JETsuffix], *h_data_n_events_pre[n_region][n_SFsuffix][n_JETsuffix];
    double n_events_data_obs[n_region][n_SFsuffix][n_JETsuffix], n_events_fake_bkg_obs[n_region][n_SFsuffix][n_JETsuffix], n_events_data_pre[n_region][n_SFsuffix][n_JETsuffix];

    for(int ddd=0; ddd<n_CF_syst; ddd++){
      for(int ccc=0; ccc<n_JETsuffix; ccc++){//jet suffix
        for(int bbb=0; bbb<n_SFsuffix; bbb++){//SF suffix
          for(int aaa=0; aaa<n_region; aaa++){//region suffix
            h_data_n_events_obs[aaa][bbb][ccc] = (TH1D*)(file_data->Get("observed_n_events"+JETsuffix[ccc]+s_region[aaa]+IDsuffix+SAMPLEsuffix+"_"+s_syst[it_syst])->Clone());
            h_data_n_events_pre[aaa][bbb][ccc] = (TH1D*)(file_data->Get("predicted_n_events"+JETsuffix[ccc]+s_region[aaa]+IDsuffix+SAMPLEsuffix+SFsuffix[bbb]+"_"+s_syst[it_syst]+s_CF_syst[ddd])->Clone());
            h_fake_bkg_n_events_obs[aaa][bbb][ccc] = (TH1D*)(file_fake_bkg->Get("observed_n_events"+JETsuffix[ccc]+s_region[aaa]+IDsuffix+"_"+s_syst[it_syst])->Clone());

            n_events_data_obs[aaa][bbb][ccc] = h_data_n_events_obs[aaa][bbb][ccc]->GetBinContent(1);
            n_events_data_pre[aaa][bbb][ccc] = h_data_n_events_pre[aaa][bbb][ccc]->GetBinContent(1);
            n_events_fake_bkg_obs[aaa][bbb][ccc] = h_fake_bkg_n_events_obs[aaa][bbb][ccc]->GetBinContent(1);
          }
        }
      }
      double scalefactor[n_region][n_SFsuffix][n_JETsuffix]={{{0.,},},};

      for(int ccc=0; ccc<n_JETsuffix; ccc++){
        for(int bbb=0; bbb<n_SFsuffix; bbb++){
          for(int aaa=0; aaa<n_region; aaa++){
            scalefactor[aaa][bbb][ccc] = fabs(n_events_data_obs[aaa][bbb][ccc] - n_events_fake_bkg_obs[aaa][bbb][ccc])/n_events_data_pre[aaa][bbb][ccc];
            if(aaa==3) if(it_syst==0) if(ddd==0)  central_sf = scalefactor[aaa][1][0];
          }
        }
      }
      cout << s_syst[it_syst]+s_CF_syst[ddd] << endl <<
      " >>> n_obs : " << n_events_data_obs[3][1][0] << endl <<
      " >>> n_bkg : " << n_events_fake_bkg_obs[3][1][0] << endl <<
      " >>> n_pre : " << n_events_data_pre[3][1][0] << endl <<
      " =============> " << scalefactor[3][1][0] << endl <<
      " Uncertainty :: " << (scalefactor[3][1][0] - central_sf)/central_sf << endl;
      if(ddd==0) {uncert_sum+= ((scalefactor[3][1][0] - central_sf)/central_sf)*((scalefactor[3][1][0] - central_sf)/central_sf ); cout << "SUMMED" <<endl;}
      cout << " ***************************************************************** " << endl;

    }
  }
  uncert_sum = TMath::Sqrt(uncert_sum);
  cout << endl << endl << "================= Total Uncertainty =================" << endl <<
  " ======> " << uncert_sum << endl;
  return;
}
