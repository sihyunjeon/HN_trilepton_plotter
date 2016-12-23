void get_numbers_for_limit(){

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString dataset = getenv("CATANVERSION");

  TString fake = "SFed_HighdXY";

  //=============
  //==== For SR
  //=============
  //TString SearchRegion = "SR";
  //TString signalfileprefix = "trilepton_mumumu_SKHN";
  //TString cut = "_cut0";
  //TString cut = "_cutWlow";
  
  //=============
  //==== For CR
  //=============
  TString SearchRegion = "CR";
  TString signalfileprefix = "trilepton_mumumu_CR_SKHN";
  //TString cut = "_cut0";
  TString cut = "_ZJets";

  TString filepath = WORKING_DIR+"/plots/"+dataset+"/"+SearchRegion+"/use_FR_method/"+fake+"/hists.root";

  TFile* file = new TFile(filepath);
  TDirectory* dir = (TDirectory*)file->Get(cut);
  TCanvas* c1 = (TCanvas*)dir->Get("n_events");
  TPad* pad1 = (TPad*)c1->GetPrimitive("c1");

  cout << "ok" << endl;
/*
  TH1F* hist_data = (TH1F*)pad1->GetPrimitive("n_events"+cut+"_data");
  cout
  << "Data" << endl
  << " (# of event) = " << hist_data->GetBinContent(1) << endl
  <<  " (# of entry) = " << hist_data->GetEntries() << endl
  << " stat uncert. = " << hist_data->GetBinError(1) << endl;
*/

  TH1F* hist_bkg;
  if(pad1) hist_bkg = (TH1F*)pad1->GetPrimitive("MC_stacked_err");
  else hist_bkg = (TH1F*)c1->GetPrimitive("MC_stacked_err");
  cout
  << "Bkg" << endl
  << " (# of event) = " << hist_bkg->GetBinContent(1) << endl
  << " (# of entry) = " << hist_bkg->GetEntries() << endl
  << "        error = " << hist_bkg->GetBinError(1) << endl;

  vector<TString> sig_mass = {"40", "60", "150", "700"};
  vector<double> n_generated = {100000, 100000, 100000, 100000};
  for(unsigned int i=0; i<sig_mass.size(); i++){

    TFile* file_sig = new TFile(WORKING_DIR+"/rootfiles/"+dataset+"/"+SearchRegion+"/"+signalfileprefix+sig_mass.at(i)+"_mumumu_VmuN_0p1_cat_v8-0-2.root");
    TH1F* hist_sig = (TH1F*)file_sig->Get("n_events"+cut);

    cout
    << "HN"+sig_mass.at(i)+" Sig" << endl
    << " (# of event) = " << hist_sig->GetBinContent(1) << endl
    << " (# of entry) = " << hist_sig->GetEntries() << endl
    << "        error = " << hist_sig->GetBinError(1) << endl
    << "   efficiency = " << hist_sig->GetEntries()/n_generated.at(i) << endl;

  }

}
