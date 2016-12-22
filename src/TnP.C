#include "canvas_margin.h"

void TnP(){

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString dataset = "v8-0-2.9";
  TString filepath = WORKING_DIR+"/rootfiles/"+dataset+"/TnP/";
  TString plotpath = WORKING_DIR+"/plots/"+dataset+"/TnP/";

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

  vector<double> abseta = {0.0, 0.8, 1.479, 2.0, 2.5 };
  vector<double> pt = {5., 15., 20., 25., 30., 35., 45., 60., 80., 100.};

  TString dirname = "tpTree/HN_TRI_TIGHT_pt_eta/";

  //============
  //==== ID SF
  //============

  TFile *file_ID_Data = new TFile(filepath+"TnP_Muon_ID_Data.root");
  TFile *file_ID_MC = new TFile(filepath+"TnP_Muon_ID_MC.root");


  //==== FitResult
  for(unsigned int i_eta = 0; i_eta<abseta.size()-1; i_eta++){
    for(unsigned int i_pt = 0; i_pt<pt.size()-1; i_pt++){

      TString dirname_fit_result = "abseta_bin"+TString::Itoa(i_eta,10)+"__pt_bin"+TString::Itoa(i_pt,10)+"__vpvPlusExpo";

      //==== Data
      TCanvas *c_data = (TCanvas*)file_ID_Data->Get(dirname+dirname_fit_result+"/fit_canvas");
      c_data->SaveAs(plotpath+"ID/fitresult/Data/"+dirname_fit_result+".png");
      //==== MC
      TCanvas *c_MC = (TCanvas*)file_ID_MC->Get(dirname+dirname_fit_result+"/fit_canvas");
      c_MC->SaveAs(plotpath+"ID/fitresult/MC/"+dirname_fit_result+".png");

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

    TLegend *lg = new TLegend(0.5, );

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
        ratio->SetPoint(i+1, eff_Data->GetX()[i], r);
        ratio->SetPointError(i+1, eff_Data->GetErrorXlow(i), eff_Data->GetErrorXhigh(i), rdn, rup);
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
      ratio->SetPoint(i+1, eff_Data->GetX()[i], r);
      ratio->SetPointError(i+1, eff_Data->GetErrorXlow(i), eff_Data->GetErrorXhigh(i), rdn, rup);
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
  
  //============
  //==== PR SF
  //============
  
  TFile *file_PR_Data = new TFile(filepath+"TnP_Muon_PR_Data.root");
  TFile *file_PR_MC = new TFile(filepath+"TnP_Muon_PR_MC.root");
  
  //==== FitResult
  for(unsigned int i_eta = 0; i_eta<abseta.size()-1; i_eta++){
    for(unsigned int i_pt = 0; i_pt<pt.size()-1; i_pt++){
      
      TString dirname_fit_result = "abseta_bin"+TString::Itoa(i_eta,10)+"__combRelIsoPF04dBeta_bin0__pt_bin"+TString::Itoa(i_pt,10)+"__vpvPlusExpo";
      cout << dirname_fit_result << endl;
      
      //==== Data
      TCanvas *c_data = (TCanvas*)file_PR_Data->Get(dirname+dirname_fit_result+"/fit_canvas");
      c_data->SaveAs(plotpath+"PR/fitresult/Data/"+dirname_fit_result+".png");
      //==== MC
      TCanvas *c_MC = (TCanvas*)file_PR_MC->Get(dirname+dirname_fit_result+"/fit_canvas");
      c_MC->SaveAs(plotpath+"PR/fitresult/MC/"+dirname_fit_result+".png");
      
    }
  }

  
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
    eff_MC->Draw("psame");
    
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
      ratio->SetPoint(i+1, eff_Data->GetX()[i], r);
      ratio->SetPointError(i+1, eff_Data->GetErrorXlow(i), eff_Data->GetErrorXhigh(i), rdn, rup);
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
      ratio->SetPoint(i+1, eff_Data->GetX()[i], r);
      ratio->SetPointError(i+1, eff_Data->GetErrorXlow(i), eff_Data->GetErrorXhigh(i), rdn, rup);
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











