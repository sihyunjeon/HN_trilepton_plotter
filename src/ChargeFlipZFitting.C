#include "RooWorkspace.h"
#include "RooAbsPdf.h"
#include "RooRealVar.h"
#include "RooPlot.h"
#include "RooDataSet.h"
#include "RooFitResult.h"
#include "RooDataHist.h"
#include "RooPolynomial.h"
#include "RooAddPdf.h"
#include "RooExtendPdf.h"
#include "RooChi2Var.h"
#include "TAxis.h"
#include "TFile.h"
#include "TH1.h"
#include "TPad.h"

const char * workspaceName = "w";
const char * pdfName = "pdf";
const char * dataName = "data";
using namespace RooFit;

void ChargeFlipZFitting( TString XXX ){

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString plotpath = WORKING_DIR+"/plots/v8-0-7.18/CFRateCalculator/";

  TFile* file = TFile::Open("./rootfiles/v8-0-7.18/CFRateCalculator/CFRateCalculator_data_DoubleEG_cat_v8-0-7.root");

  TH1D* obs_hist;
  TString obs_hist_name = "FIT_observed_Z_mass";
  if( XXX == "_JETS1" ) obs_hist_name = obs_hist_name + "_global_JETS1_HNTIGHT"; 
  else obs_hist_name = obs_hist_name + XXX + "_HNTIGHT";
  obs_hist = (TH1D*)(file->Get(obs_hist_name)->Clone());
  RooRealVar x("x", "x", 70., 110.);
  RooRealVar width1("width", "width", 1., 3.);
  RooRealVar width2("width", "width", 2., 5.);
  RooDataHist data("data", "observed Z mass", x, obs_hist);

  RooRealVar a0("a0", "a0", -0.1, 0.1);//5050
  RooRealVar a1("a1", "a1", -5., 5.);
  RooRealVar a2("a2", "a2", -5., 5.);
  RooRealVar c("c", "c", -1., 0.);

  RooPolynomial bmodel("bmodel", "bmodel", x, RooArgList(a1), 0);
  
  RooRealVar mass("mass", "mass", 91.1876, 91.1876, 91.1876);
  RooRealVar sigma1("sigma1", "sigma1", 3., 1., 5.);
  RooRealVar sigma2("sigma2", "sigma2", 5., 2., 10.);

//  RooVoigtian smodel1("smodel1", "smodel1", x, mass, width1, sigma1);
//  RooVoigtian smodel2("smodel2", "smodel2", x, mass, width2, sigma2);
  RooGaussian smodel1("smodel1", "smodel1", x, mass, sigma1);
  RooGaussian smodel2("smodel2", "smodel2", x, mass, sigma2);

  RooRealVar sigfrac("sigfrac", "sigfrac", 0.5, 1.);
  RooRealVar frac("frac", "frac", 0., 1.);

  RooAddPdf smodel("smodel", "smodel", smodel1,smodel2);

  int aaa[2] = {410, 200};
  if( XXX == "_BB" ){ aaa[0] = 150; aaa[1] = 50;}
  if( XXX == "_EE" ){ aaa[0] = 80; aaa[1] = 15;}
  if( XXX == "_BE" ){ aaa[0] = 100; aaa[1] = 50;}
  if( XXX == "_JETS1" ){ aaa[0] = 150; aaa[1] = 40;}

  double maxnbkg = 300.;
  if(XXX=="_JETS1") maxnbkg = 200.;

  RooRealVar nsig("nsig", "signal events", aaa[0], 750);
  RooRealVar nbkg("nbkg", "signal background events", aaa[1], maxnbkg);
  RooAddPdf model("model", "model",RooArgList(smodel,bmodel),RooArgList(nsig,nbkg));
//  RooAddPdf model("model", "model", RooArgList(smodel,bmodel), frac);

  RooFitResult *r = model.fitTo(data,  Extended(), Save());
  //r->Print();


  RooPlot *all_plot = x.frame();
  RooPlot *bkg_plot = x.frame();

  data.plotOn(all_plot);
  model.plotOn(all_plot, LineColor(kBlack));
  model.plotOn(all_plot, Components("bmodel"), LineStyle(kDashed), LineColor(kBlue));
  model.plotOn(all_plot, Components("smodel"), LineStyle(kDashed),LineColor(kRed));

//  model.plotOn(bkg_plot, Components("bmodel"), LineStyle(kDashed), LineColor(kBlue));
  all_plot->Draw();
  RooArgSet* params = model.getVariables();
  params->Print("v");

  auto aaaa = a1.getVal();
  auto bbbb = a0.getVal();


  TCanvas *canvas_temp = new TCanvas("canvas","canvas",900,600);
  all_plot->SetTitle("Fitting"+XXX);
  all_plot->Draw();
  all_plot->SaveAs(plotpath+"/dilep_fitting"+XXX+".pdf");
  //bkg_plot->SaveAs("test.root");
//  bkg_plot->addTH1(obs_hist);
//  bkg_plot->Draw("same");
  return;
/*  canvas->Divide(2);
  THStack *stack_hist = new THStack("stack_hist","stack_hist");
  obs_hist->SetFillColor(kCyan-9);
  stack_hist->Add(obs_hist);*/


}

