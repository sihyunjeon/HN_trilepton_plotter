#include "canvas_margin.h"

void TnP(int fix_select){
/*  TString fix_select_char;
  TString str(itoa(fix_select,fix_select_char,fix_select));*/

  TString fix_select_char;
  fix_select_char.Form("%d",fix_select);
  cout << "char : " <<  fix_select_char << endl;

  bool DrawFitResult = true;

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString dataset = "v8-0-2.12";
  TString filepath = WORKING_DIR+"/rootfiles/"+dataset+"/TnP/";

  TString plotpath;
  if( fix_select == 0 ) plotpath = WORKING_DIR+"/plots/"+dataset+"/TnP_before_fix/";
  else{
    plotpath = WORKING_DIR+"/plots/"+dataset+"/TnP_after_fix_"+fix_select_char+"/";
  }

  if( !gSystem->mkdir(plotpath, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }
  gSystem->mkdir(plotpath+"ID", kTRUE);
  gSystem->mkdir(plotpath+"ID/fitresult/", kTRUE);
  gSystem->mkdir(plotpath+"ID/fitresult/Data", kTRUE);
  gSystem->mkdir(plotpath+"ID/fitresult/MC", kTRUE);
  gSystem->mkdir(plotpath+"PR", kTRUE);
  gSystem->mkdir(plotpath+"PR/fitresult/", kTRUE);
  gSystem->mkdir(plotpath+"PR/fitresult/Data", kTRUE);
  gSystem->mkdir(plotpath+"PR/fitresult/MC", kTRUE);
  vector<double> abseta = {0.0, 0.8, 1.479, 2.0, 2.5};
  vector<double> pt = {10., 20., 25., 30., 35., 45., 60., 80., 100., 200.};

  TString dirname = "tpTree/HN_muonsel_pt_eta/";

  //============
  //==== Select Fit Function
  //============

  bool eta_pt_bin_select_MC = false, eta_pt_bin_select_Data = false;

  vector<string> select_fit_function_MC, select_fit_function_Data;
  if( fix_select == 0 ){
    select_fit_function_MC = {
      "vpvPlusExpo",            //ptbin0
      "vpvPlusExpo",            //ptbin1
      "vpvPlusExpo",            //ptbin2
      "vpvPlusExpo",            //ptbin3
      "vpvPlusExpo",      //ptbin4
      "vpvPlusExpo",      //ptbin5
      "vpvPlusExpo",      //ptbin6
      "vpvPlusExpo",      //ptbin7
      "vpvPlusExpo",      //ptbin8
      "vpvPlusExpo"       //ptbin9
    };
    select_fit_function_Data = {
      "vpvPlusExpo",            //ptbin0
      "vpvPlusExpo",            //ptbin1
      "vpvPlusExpo",            //ptbin2
      "vpvPlusExpo",            //ptbin3
      "vpvPlusExpo",      //ptbin4
      "vpvPlusExpo",      //ptbin5
      "vpvPlusExpo",      //ptbin6
      "vpvPlusExpo",      //ptbin7
      "vpvPlusExpo",      //ptbin8
      "vpvPlusExpo"       //ptbin9
    };
  }
  else if( fix_select == 1 ){
    select_fit_function_MC = {
      "vpvPlusExpo",            //ptbin0
      "vpvPlusExpo",            //ptbin1
      "vpvPlusExpo",            //ptbin2
      "vpvPlusCheb",            //ptbin3
      "vpvPlusCheb",      //ptbin4
      "vpvPlusCheb",      //ptbin5
      "vpvPlusCheb",      //ptbin6
      "vpvPlusCheb",      //ptbin7
      "vpvPlusCheb",      //ptbin8
    };
    select_fit_function_Data = {
      "vpvPlusExpo",            //ptbin0
      "vpvPlusExpo",            //ptbin1
      "vpvPlusExpo",            //ptbin2
      "vpvPlusExpo",            //ptbin3
      "vpvPlusCheb",      //ptbin4
      "vpvPlusCheb",      //ptbin5
      "vpvPlusCheb",      //ptbin6
      "vpvPlusCheb",      //ptbin7
      "vpvPlusCheb",      //ptbin8
    };
  }
  else{
    select_fit_function_MC = {
      "vpvPlusExpo",            //ptbin0
      "vpvPlusExpo",            //ptbin1
      "vpvPlusExpo",            //ptbin2
      "vpvPlusCheb",            //ptbin3
      "vpvPlusCheb",      //ptbin4
      "vpvPlusCheb",      //ptbin5
      "vpvPlusCheb",      //ptbin6
      "vpvPlusCheb",      //ptbin7
      "vpvPlusCheb",      //ptbin8
    };
    select_fit_function_Data = {
      "vpvPlusExpo",            //ptbin0
      "vpvPlusExpo",            //ptbin1
      "vpvPlusExpo",            //ptbin2
      "vpvPlusCheb",            //ptbin3
      "vpvPlusCheb",      //ptbin4
      "vpvPlusCheb",      //ptbin5
      "vpvPlusCheb",      //ptbin6
      "vpvPlusCheb",      //ptbin7
      "vpvPlusCheb",      //ptbin8
    };
  }

  //============
  //==== ID SF
  //============
  TFile *file_ID_Data, *file_ID_MC;
  TString file_ID_Data_string, file_ID_MC_string;
  if(fix_select == 888) goto PR;

  if( fix_select == 0 ){
    file_ID_Data_string = filepath+"TnP_Muon_ID_Data.root";
    file_ID_MC_string = filepath+"TnP_Muon_ID_MC.root";
  }
  else{
    file_ID_Data_string = filepath+"TnP_Muon_ID_Data_Cheb.root";
    file_ID_MC_string = filepath+"TnP_Muon_ID_MC_Cheb.root";
  }
  file_ID_Data = new TFile(file_ID_Data_string);
  file_ID_MC = new TFile(file_ID_MC_string);

  //==== FitResult
  if(DrawFitResult){
    for(unsigned int i_eta = 0; i_eta<abseta.size()-1; i_eta++){
      for(unsigned int i_pt = 0; i_pt<pt.size()-1; i_pt++){
	eta_pt_bin_select_MC = false; eta_pt_bin_select_Data = false;

	if( (i_eta == 0 && i_pt == 4) ){
	//   eta_pt_bin_select_MC = true;
 	}

	if( eta_pt_bin_select_MC ){
          TString dirname_fit_result_MC = "abseta_bin"+TString::Itoa(i_eta,10)+"__pt_bin"+TString::Itoa(i_pt,10)+"__vpvPlusCheb_3rd";
          TCanvas *c_MC = (TCanvas*)file_ID_MC->Get(dirname+dirname_fit_result_MC+"/fit_canvas");
          c_MC->SaveAs(plotpath+"ID/fitresult/MC/"+dirname_fit_result_MC+".png");
	}
	else{
          TString dirname_fit_result_MC = "abseta_bin"+TString::Itoa(i_eta,10)+"__pt_bin"+TString::Itoa(i_pt,10)+"__"+select_fit_function_MC[i_pt];
          TCanvas *c_MC = (TCanvas*)file_ID_MC->Get(dirname+dirname_fit_result_MC+"/fit_canvas");
          c_MC->SaveAs(plotpath+"ID/fitresult/MC/"+dirname_fit_result_MC+".png");
	}

	if( eta_pt_bin_select_Data ){
          TString dirname_fit_result_Data = "abseta_bin"+TString::Itoa(i_eta,10)+"__pt_bin"+TString::Itoa(i_pt,10)+"__vpvPlusCheb_4th";
          TCanvas *c_data = (TCanvas*)file_ID_Data->Get(dirname+dirname_fit_result_Data+"/fit_canvas");
          c_data->SaveAs(plotpath+"ID/fitresult/Data/"+dirname_fit_result_Data+".png");
	}
	else{
          TString dirname_fit_result_Data = "abseta_bin"+TString::Itoa(i_eta,10)+"__pt_bin"+TString::Itoa(i_pt,10)+"__"+select_fit_function_Data[i_pt];
          TCanvas *c_data = (TCanvas*)file_ID_Data->Get(dirname+dirname_fit_result_Data+"/fit_canvas");
          c_data->SaveAs(plotpath+"ID/fitresult/Data/"+dirname_fit_result_Data+".png");
	}
      }
    }
  }
  //==== Eff vs pt for each eta region
  for(unsigned int i_eta = 0; i_eta<abseta.size()-1; i_eta++){
   
    TGraphAsymmErrors *eff_Data = (TGraphAsymmErrors*)file_ID_Data->Get(dirname+"fit_eff_plots/pt_PLOT_abseta_bin"+TString::Itoa(i_eta,10))->FindObject("hxy_fit_eff");
    TGraphAsymmErrors *eff_MC = (TGraphAsymmErrors*)file_ID_MC->Get(dirname+"fit_eff_plots/pt_PLOT_abseta_bin"+TString::Itoa(i_eta,10))->FindObject("hxy_fit_eff");
 
    TCanvas *c_eff = new TCanvas("c_eff", "", 800, 800);
    c_eff->Draw();
    TPad *c1_up = new TPad("c1", "", 0, 0.25, 1, 1);
    TPad *c1_down = new TPad("c1_down", "", 0, 0, 1, 0.25);
    canvas_margin(c_eff, c1_up, c1_down);
    c1_down->SetGridx();
    c1_down->SetGridy();
    c1_up->Draw();
    c1_down->Draw();
    c1_up->cd();
    eff_Data->SetLineColor(kBlack);
    eff_MC->SetLineColor(kBlue);
    eff_Data->SetMarkerColor(kBlack);
    eff_MC->SetMarkerColor(kBlue);
    eff_MC->SetMarkerStyle(21);

    eff_Data->Draw("ap");
    eff_MC->Draw("psame");

    TLegend *lg = new TLegend(0.5, 0.5, 0.8, 0.8);
    lg->SetFillStyle(0);
    lg->SetBorderSize(0);
    lg->AddEntry(eff_Data, "Run BCDEF", "lp");
    lg->AddEntry(eff_MC, "MC", "lp");
    lg->Draw();

    eff_Data->SetTitle("");
    eff_Data->GetYaxis()->SetTitle("Efficiency");
    eff_Data->GetYaxis()->SetRangeUser(0, 1.1);

    c1_down->cd();

    if (eff_Data->GetN() == 0 || eff_MC->GetN() == 0) return;
    TGraphAsymmErrors *ratio = new TGraphAsymmErrors(eff_Data->GetN());
    double max = 0;
    for (size_t i = 0, n = eff_Data->GetN(); i < n; ++i) {
      double r   = eff_Data->GetY()[i]/eff_MC->GetY()[i];
      double rup = (eff_Data->GetY()[i] == 0 ? eff_Data->GetErrorYhigh(i)/(eff_MC->GetY()[i]) :
                                             r*TMath::Hypot(eff_Data->GetErrorYhigh(i)/eff_Data->GetY()[i], eff_MC->GetErrorYlow(i)/eff_MC->GetY()[i]));
      double rdn = (eff_Data->GetY()[i] == 0 ? 0 :
                                             r*TMath::Hypot(eff_Data->GetErrorYlow(i)/eff_Data->GetY()[i],  eff_MC->GetErrorYhigh(i)/eff_MC->GetY()[i]));
      max = TMath::Max(max, fabs(r-1+rup));
      max = TMath::Max(max, fabs(r-1-rdn));
      ratio->SetPoint(i, eff_Data->GetX()[i], r);
      ratio->SetPointError(i, eff_Data->GetErrorXlow(i), eff_Data->GetErrorXhigh(i), rdn, rup);
    }

    ratio->SetLineWidth(2);
    ratio->SetLineColor(kBlack);
    ratio->SetMarkerColor(kBlack);
    ratio->SetMarkerStyle(20);
    ratio->SetMarkerSize(1.6);
    ratio->Draw("AP");
    ratio->GetXaxis()->SetTitle("p_{T} [GeV]");
    ratio->GetYaxis()->SetTitle("Data/MC");
    ratio->GetYaxis()->SetRangeUser(0, 1.5);

/*
    for(size_t i = 0, n = eff_Data->GetN(); i < n; ++i){
      double a,b;
      eff_Data->GetPoint(i, a, b);
      cout << "x = " << a << ", Data = " << b << endl;
      eff_MC->GetPoint(i, a, b);
      cout << "x = " << a << ", MC = " << b << endl;
      ratio->GetPoint(i, a, b);
      cout << "x = " << a << ", ratio = " << b << endl <<  endl;
    }
*/

    hist_axis(eff_Data, ratio);

    TLine line(ratio->GetX()[0]-ratio->GetErrorXlow(0), 1, ratio->GetX()[ratio->GetN()-1]+ratio->GetErrorXhigh(ratio->GetN()-1), 1);
    line.SetLineWidth(2);
    line.SetLineColor(kRed);
    line.DrawClone("SAME");

    c_eff->cd();
    TLatex latex_CMSPriliminary, latex_Lumi;
    latex_CMSPriliminary.SetNDC();
    latex_Lumi.SetNDC();
    latex_CMSPriliminary.SetTextSize(0.035);
    latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS} #font[42]{#it{#scale[0.8]{Preliminary}}}");
    latex_Lumi.SetTextSize(0.035);
    latex_Lumi.DrawLatex(0.7, 0.96, "27.66 fb^{-1} (13 TeV)");

    c_eff->SaveAs(plotpath+"ID/pt_PLOT_abseta_bin"+TString::Itoa(i_eta,10)+".png");
    
    c_eff->Close();
    delete c_eff;

  }

  //==== Eff vs abseta for each pt region
  for(unsigned int i_pt = 0; i_pt<pt.size()-1; i_pt++){
    
    TGraphAsymmErrors *eff_Data = (TGraphAsymmErrors*)file_ID_Data->Get(dirname+"fit_eff_plots/abseta_PLOT_pt_bin"+TString::Itoa(i_pt,10))->FindObject("hxy_fit_eff");
    TGraphAsymmErrors *eff_MC = (TGraphAsymmErrors*)file_ID_MC->Get(dirname+"fit_eff_plots/abseta_PLOT_pt_bin"+TString::Itoa(i_pt,10))->FindObject("hxy_fit_eff");
    
    TCanvas *c_eff = new TCanvas("c_eff", "", 800, 800);
    c_eff->Draw();
    TPad *c1_up = new TPad("c1", "", 0, 0.25, 1, 1);
    TPad *c1_down = new TPad("c1_down", "", 0, 0, 1, 0.25);
    canvas_margin(c_eff, c1_up, c1_down);
    c1_down->SetGridx();
    c1_down->SetGridy();
    c1_up->Draw();
    c1_down->Draw();
    c1_up->cd();
    
    eff_Data->SetLineColor(kBlack);
    eff_MC->SetLineColor(kBlue);
    eff_Data->SetMarkerColor(kBlack);
    eff_MC->SetMarkerColor(kBlue);
    eff_MC->SetMarkerStyle(21);
    
    eff_Data->Draw("ap");
    eff_MC->Draw("psame");

    TLegend *lg = new TLegend(0.5, 0.5, 0.8, 0.8);
    lg->SetFillStyle(0);
    lg->SetBorderSize(0);
    lg->AddEntry(eff_Data, "Run BCDEF", "lp");
    lg->AddEntry(eff_MC, "MC", "lp");
    lg->Draw();
    
    eff_Data->SetTitle("");
    eff_Data->GetYaxis()->SetTitle("Efficiency");
    eff_Data->GetYaxis()->SetRangeUser(0, 1.1);
    
    c1_down->cd();
    
    if (eff_Data->GetN() == 0 || eff_MC->GetN() == 0) return;
    TGraphAsymmErrors *ratio = new TGraphAsymmErrors(eff_Data->GetN());
    double max = 0;
    for (size_t i = 0, n = eff_Data->GetN(); i < n; ++i) {
      double r   = eff_Data->GetY()[i]/eff_MC->GetY()[i];
      double rup = (eff_Data->GetY()[i] == 0 ? eff_Data->GetErrorYhigh(i)/(eff_MC->GetY()[i]) :
                    r*TMath::Hypot(eff_Data->GetErrorYhigh(i)/eff_Data->GetY()[i], eff_MC->GetErrorYlow(i)/eff_MC->GetY()[i]));
      double rdn = (eff_Data->GetY()[i] == 0 ? 0 :
                    r*TMath::Hypot(eff_Data->GetErrorYlow(i)/eff_Data->GetY()[i],  eff_MC->GetErrorYhigh(i)/eff_MC->GetY()[i]));
      max = TMath::Max(max, fabs(r-1+rup));
      max = TMath::Max(max, fabs(r-1-rdn));
      ratio->SetPoint(i, eff_Data->GetX()[i], r);
      ratio->SetPointError(i, eff_Data->GetErrorXlow(i), eff_Data->GetErrorXhigh(i), rdn, rup);
    }
    
    ratio->SetLineWidth(2);
    ratio->SetLineColor(kBlack);
    ratio->SetMarkerColor(kBlack);
    ratio->SetMarkerStyle(20);
    ratio->SetMarkerSize(1.6);
    ratio->Draw("AP");
    ratio->GetXaxis()->SetTitle("|#eta|");
    ratio->GetYaxis()->SetTitle("Data/MC");
    ratio->GetYaxis()->SetRangeUser(0, 1.5);
    
    hist_axis(eff_Data, ratio);
    
    TLine line(ratio->GetX()[0]-ratio->GetErrorXlow(0), 1, ratio->GetX()[ratio->GetN()-1]+ratio->GetErrorXhigh(ratio->GetN()-1), 1);
    line.SetLineWidth(2);
    line.SetLineColor(kRed);
    line.DrawClone("SAME");
    
    c_eff->cd();
    TLatex latex_CMSPriliminary, latex_Lumi;
    latex_CMSPriliminary.SetNDC();
    latex_Lumi.SetNDC();
    latex_CMSPriliminary.SetTextSize(0.035);
    latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS} #font[42]{#it{#scale[0.8]{Preliminary}}}");
    latex_Lumi.SetTextSize(0.035);
    latex_Lumi.DrawLatex(0.7, 0.96, "27.66 fb^{-1} (13 TeV)");
    
    
    c_eff->SaveAs(plotpath+"ID/abseta_PLOT_pt_bin"+TString::Itoa(i_pt,10)+".png");
    
    c_eff->Close();
    delete c_eff;
    
  }
  
  PR:;
  //============
  //==== PR SF
  //============
  TFile *file_PR_Data, *file_PR_MC;
  TString file_PR_Data_string, file_PR_MC_string;
  if( fix_select == 0 ){
    file_PR_Data_string = filepath+"TnP_Muon_PR_Data.root";
    file_PR_MC_string = filepath+"TnP_Muon_PR_MC.root";
  }
  else{
    file_PR_Data_string = filepath+"TnP_Muon_PR_Data_Cheb_GH.root";
    file_PR_MC_string = filepath+"TnP_Muon_PR_MC_Cheb.root";
  }
  file_PR_Data = new TFile(file_PR_Data_string);
  file_PR_MC = new TFile(file_PR_MC_string);
cout << "wrong2?" << endl;
  
  //==== FitResult
  if(DrawFitResult){
    for(unsigned int i_eta = 0; i_eta<abseta.size()-1; i_eta++){
cout << i_eta << " " << abseta.size() << endl;
      for(unsigned int i_pt = 0; i_pt<pt.size()-1; i_pt++){
cout << i_pt << pt.size() << endl;
        eta_pt_bin_select_MC = false; eta_pt_bin_select_Data = false;

/*        if( (i_eta == 0 && ((i_pt == 4) || (i_pt == 5)))
         || (i_eta == 1 && ((i_pt == 4) || (i_pt == 5) || (i_pt == 7)))
         || (i_eta == 2 && ((i_pt == 0) || (i_pt == 4) || (i_pt == 5)))
         || (i_eta == 3 && ((i_pt == 2) || (i_pt == 4))) ){
           eta_pt_bin_select_MC = true;
        }*/
//        if( (i_eta == 2 && i_pt == 7) ) eta_pt_bin_select_Data = true;

        if( eta_pt_bin_select_MC ){
          TString dirname_fit_result_MC = "abseta_bin"+TString::Itoa(i_eta,10)+"__combRelIsoPF04dBeta_bin0__pt_bin"+TString::Itoa(i_pt,10)+"__vpvPlusCheb";
          TCanvas *c_MC = (TCanvas*)file_PR_MC->Get(dirname+dirname_fit_result_MC+"/fit_canvas");
          c_MC->SaveAs(plotpath+"PR/fitresult/MC/"+dirname_fit_result_MC+".png");
        }
        else{
          TString dirname_fit_result_MC = "abseta_bin"+TString::Itoa(i_eta,10)+"__combRelIsoPF04dBeta_bin0__pt_bin"+TString::Itoa(i_pt,10)+"__"+select_fit_function_MC[i_pt];
          TCanvas *c_MC = (TCanvas*)file_PR_MC->Get(dirname+dirname_fit_result_MC+"/fit_canvas");
          c_MC->SaveAs(plotpath+"PR/fitresult/MC/"+dirname_fit_result_MC+".png");
        }
        if( eta_pt_bin_select_Data ){
          TString dirname_fit_result_Data = "abseta_bin"+TString::Itoa(i_eta,10)+"__combRelIsoPF04dBeta_bin0__pt_bin"+TString::Itoa(i_pt,10)+"__vpvPlusCheb_4th";
          TCanvas *c_data = (TCanvas*)file_PR_Data->Get(dirname+dirname_fit_result_Data+"/fit_canvas");
          c_data->SaveAs(plotpath+"PR/fitresult/Data/"+dirname_fit_result_Data+".png");
        }
        else{
          TString dirname_fit_result_Data = "abseta_bin"+TString::Itoa(i_eta,10)+"__combRelIsoPF04dBeta_bin0__pt_bin"+TString::Itoa(i_pt,10)+"__"+select_fit_function_Data[i_pt];
          TCanvas *c_data = (TCanvas*)file_PR_Data->Get(dirname+dirname_fit_result_Data+"/fit_canvas");
          c_data->SaveAs(plotpath+"PR/fitresult/Data/"+dirname_fit_result_Data+".png");
        }
cout << "end pt loop" << endl;
      }
cout << "end eta loop" << endl;

    }
  }

cout << "wrong?" << endl;

  //==== Eff vs pt for each eta region
  for(unsigned int i_eta = 0; i_eta<abseta.size()-1; i_eta++){
    
    TGraphAsymmErrors *eff_Data = (TGraphAsymmErrors*)file_PR_Data->Get(dirname+"fit_eff_plots/pt_PLOT_abseta_bin"+TString::Itoa(i_eta,10))->FindObject("hxy_fit_eff");
    TGraphAsymmErrors *eff_MC = (TGraphAsymmErrors*)file_PR_MC->Get(dirname+"fit_eff_plots/pt_PLOT_abseta_bin"+TString::Itoa(i_eta,10))->FindObject("hxy_fit_eff");
    
    TCanvas *c_eff = new TCanvas("c_eff", "", 800, 800);
    c_eff->Draw();
    TPad *c1_up = new TPad("c1", "", 0, 0.25, 1, 1);
    TPad *c1_down = new TPad("c1_down", "", 0, 0, 1, 0.25);
    canvas_margin(c_eff, c1_up, c1_down);
    c1_down->SetGridx();
    c1_down->SetGridy();
    c1_up->Draw();
    c1_down->Draw();
    c1_up->cd();
    
    eff_Data->SetLineColor(kBlack);
    eff_MC->SetLineColor(kBlue);
    eff_Data->SetMarkerColor(kBlack);
    eff_MC->SetMarkerColor(kBlue);
    eff_MC->SetMarkerStyle(21);
    
    eff_Data->Draw("ap");
//    eff_MC->Draw("psame");

    TLegend *lg = new TLegend(0.5, 0.5, 0.8, 0.8);
    lg->SetFillStyle(0);
    lg->SetBorderSize(0);
    lg->AddEntry(eff_Data, "Run BCDEF", "lp");
    lg->AddEntry(eff_MC, "MC", "lp");
    lg->Draw();

    eff_Data->SetTitle("");
    eff_Data->GetYaxis()->SetTitle("Efficiency");
    eff_Data->GetYaxis()->SetRangeUser(0, 1.1);
    
    c1_down->cd();
    
    if (eff_Data->GetN() == 0 || eff_MC->GetN() == 0) return;
    TGraphAsymmErrors *ratio = new TGraphAsymmErrors(eff_Data->GetN());
    double max = 0;
    for (size_t i = 0, n = eff_Data->GetN(); i < n; ++i) {
      double r   = eff_Data->GetY()[i]/eff_MC->GetY()[i];
      double rup = (eff_Data->GetY()[i] == 0 ? eff_Data->GetErrorYhigh(i)/(eff_MC->GetY()[i]) :
                    r*TMath::Hypot(eff_Data->GetErrorYhigh(i)/eff_Data->GetY()[i], eff_MC->GetErrorYlow(i)/eff_MC->GetY()[i]));
      double rdn = (eff_Data->GetY()[i] == 0 ? 0 :
                    r*TMath::Hypot(eff_Data->GetErrorYlow(i)/eff_Data->GetY()[i],  eff_MC->GetErrorYhigh(i)/eff_MC->GetY()[i]));
      max = TMath::Max(max, fabs(r-1+rup));
      max = TMath::Max(max, fabs(r-1-rdn));
      ratio->SetPoint(i, eff_Data->GetX()[i], r);
      ratio->SetPointError(i, eff_Data->GetErrorXlow(i), eff_Data->GetErrorXhigh(i), rdn, rup);
    }
    
    ratio->SetLineWidth(2);
    ratio->SetLineColor(kBlack);
    ratio->SetMarkerColor(kBlack);
    ratio->SetMarkerStyle(20);
    ratio->SetMarkerSize(1.6);
    ratio->Draw("AP");
    ratio->GetXaxis()->SetTitle("p_{T} [GeV]");
    ratio->GetYaxis()->SetTitle("Data/MC");
    ratio->GetYaxis()->SetRangeUser(0, 1.5);
    
    hist_axis(eff_Data, ratio);
    
    TLine line(ratio->GetX()[0]-ratio->GetErrorXlow(0), 1, ratio->GetX()[ratio->GetN()-1]+ratio->GetErrorXhigh(ratio->GetN()-1), 1);
    line.SetLineWidth(2);
    line.SetLineColor(kRed);
    line.DrawClone("SAME");
    
    c_eff->cd();
    TLatex latex_CMSPriliminary, latex_Lumi;
    latex_CMSPriliminary.SetNDC();
    latex_Lumi.SetNDC();
    latex_CMSPriliminary.SetTextSize(0.035);
    latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS} #font[42]{#it{#scale[0.8]{Preliminary}}}");
    latex_Lumi.SetTextSize(0.035);
    latex_Lumi.DrawLatex(0.7, 0.96, "27.66 fb^{-1} (13 TeV)");
    
    
    c_eff->SaveAs(plotpath+"PR/pt_PLOT_abseta_bin"+TString::Itoa(i_eta,10)+".png");
    
    c_eff->Close();
    delete c_eff;
    
  }
  
  //==== Eff vs abseta for each pt region
  for(unsigned int i_pt = 0; i_pt<pt.size()-1; i_pt++){
    
    TGraphAsymmErrors *eff_Data = (TGraphAsymmErrors*)file_PR_Data->Get(dirname+"fit_eff_plots/abseta_PLOT_pt_bin"+TString::Itoa(i_pt,10))->FindObject("hxy_fit_eff");
    TGraphAsymmErrors *eff_MC = (TGraphAsymmErrors*)file_PR_MC->Get(dirname+"fit_eff_plots/abseta_PLOT_pt_bin"+TString::Itoa(i_pt,10))->FindObject("hxy_fit_eff");
    
    TCanvas *c_eff = new TCanvas("c_eff", "", 800, 800);
    c_eff->Draw();
    TPad *c1_up = new TPad("c1", "", 0, 0.25, 1, 1);
    TPad *c1_down = new TPad("c1_down", "", 0, 0, 1, 0.25);
    canvas_margin(c_eff, c1_up, c1_down);
    c1_down->SetGridx();
    c1_down->SetGridy();
    c1_up->Draw();
    c1_down->Draw();
    c1_up->cd();
    
    eff_Data->SetLineColor(kBlack);
    eff_MC->SetLineColor(kBlue);
    eff_Data->SetMarkerColor(kBlack);
    eff_MC->SetMarkerColor(kBlue);
    eff_MC->SetMarkerStyle(21);
    
    eff_Data->Draw("ap");
    eff_MC->Draw("psame");

    TLegend *lg = new TLegend(0.5, 0.5, 0.8, 0.8);
    lg->SetFillStyle(0);
    lg->SetBorderSize(0);
    lg->AddEntry(eff_Data, "Run BCDEF", "lp");
    lg->AddEntry(eff_MC, "MC", "lp");
    lg->Draw();

    eff_Data->SetTitle("");
    eff_Data->GetYaxis()->SetTitle("Efficiency");
    eff_Data->GetYaxis()->SetRangeUser(0, 1.1);
    
    c1_down->cd();
    
    if (eff_Data->GetN() == 0 || eff_MC->GetN() == 0) return;
    TGraphAsymmErrors *ratio = new TGraphAsymmErrors(eff_Data->GetN());
    double max = 0;
    for (size_t i = 0, n = eff_Data->GetN(); i < n; ++i) {
      double r   = eff_Data->GetY()[i]/eff_MC->GetY()[i];
      double rup = (eff_Data->GetY()[i] == 0 ? eff_Data->GetErrorYhigh(i)/(eff_MC->GetY()[i]) :
                    r*TMath::Hypot(eff_Data->GetErrorYhigh(i)/eff_Data->GetY()[i], eff_MC->GetErrorYlow(i)/eff_MC->GetY()[i]));
      double rdn = (eff_Data->GetY()[i] == 0 ? 0 :
                    r*TMath::Hypot(eff_Data->GetErrorYlow(i)/eff_Data->GetY()[i],  eff_MC->GetErrorYhigh(i)/eff_MC->GetY()[i]));
      max = TMath::Max(max, fabs(r-1+rup));
      max = TMath::Max(max, fabs(r-1-rdn));
      ratio->SetPoint(i, eff_Data->GetX()[i], r);
      ratio->SetPointError(i, eff_Data->GetErrorXlow(i), eff_Data->GetErrorXhigh(i), rdn, rup);
    }
    
    ratio->SetLineWidth(2);
    ratio->SetLineColor(kBlack);
    ratio->SetMarkerColor(kBlack);
    ratio->SetMarkerStyle(20);
    ratio->SetMarkerSize(1.6);
    ratio->Draw("AP");
    ratio->GetXaxis()->SetTitle("|#eta|");
    ratio->GetYaxis()->SetTitle("Data/MC");
    ratio->GetYaxis()->SetRangeUser(0, 1.5);
    
    hist_axis(eff_Data, ratio);
    
    TLine line(ratio->GetX()[0]-ratio->GetErrorXlow(0), 1, ratio->GetX()[ratio->GetN()-1]+ratio->GetErrorXhigh(ratio->GetN()-1), 1);
    line.SetLineWidth(2);
    line.SetLineColor(kRed);
    line.DrawClone("SAME");
    
    c_eff->cd();
    TLatex latex_CMSPriliminary, latex_Lumi;
    latex_CMSPriliminary.SetNDC();
    latex_Lumi.SetNDC();
    latex_CMSPriliminary.SetTextSize(0.035);
    latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS} #font[42]{#it{#scale[0.8]{Preliminary}}}");
    latex_Lumi.SetTextSize(0.035);
    latex_Lumi.DrawLatex(0.7, 0.96, "27.66 fb^{-1} (13 TeV)");
    
    
    c_eff->SaveAs(plotpath+"PR/abseta_PLOT_pt_bin"+TString::Itoa(i_pt,10)+".png");
    
    c_eff->Close();
    delete c_eff;
    
  }

  

}











