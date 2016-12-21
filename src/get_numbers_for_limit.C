void get_numbers_for_limit(){

  TString data_class = "v8-0-2.9/SR/";

  TString fake = "SFed_HighdXY";

  //TString cut = "_cut0";
  TString cut = "_cutWlow";

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TFile* file = new TFile(WORKING_DIR+"/plots/"+data_class+"use_FR_method/"+fake+"/hists.root");
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

    TFile* file_sig = new TFile(WORKING_DIR+"/rootfiles/"+data_class+"/trilepton_mumumu_SKHN"+sig_mass.at(i)+"_mumumu_VmuN_0p1_cat_v8-0-2.root");
    TH1F* hist_sig = (TH1F*)file_sig->Get("n_events"+cut);

    cout
    << "HN"+sig_mass.at(i)+" Sig" << endl
    << " (# of event) = " << hist_sig->GetBinContent(1) << endl
    << " (# of entry) = " << hist_sig->GetEntries() << endl
    << "        error = " << hist_sig->GetBinError(1) << endl
    << "   efficiency = " << hist_sig->GetEntries()/n_generated.at(i) << endl;

  }

}
