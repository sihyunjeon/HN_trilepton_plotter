void get_numbers_for_limit(){

  TString data_class = "v7-6-6.2/SR/";

  TString fake = "HighdXY";

  //TString cut = "_cut0";
  //TString cut = "_cutdR";
  TString cut = "_cutdR_cutW";

  TFile* file = new TFile("plots/"+data_class+"use_FR_method/"+fake+"/hists.root");
  TDirectory* dir = (TDirectory*)file->Get(cut);
  TCanvas* c1 = (TCanvas*)dir->Get("n_events");
  TPad* pad1 = (TPad*)c1->GetPrimitive("c1_up");

  TH1F* hist_data = (TH1F*)pad1->GetPrimitive("n_events"+cut+"_PU_data");
  cout
  << "Data" << endl
  << " (# of event) = " << hist_data->GetBinContent(1) << endl
  << " stat uncert. = " << hist_data->GetBinError(1) << endl;

  TH1F* hist_bkg = (TH1F*)pad1->GetPrimitive("MC_stacked_err");
  cout
  << "Bkg" << endl
  << " (# of event) = " << hist_bkg->GetBinContent(1) << endl
  << "        error = " << hist_bkg->GetBinError(1) << endl;

  vector<TString> sig_mass = {"40", "60", "150", "700"};
  vector<double> n_generated = {100000, 100000, 100000, 100000};
  for(unsigned int i=0; i<sig_mass.size(); i++){

    TFile* file_sig = new TFile("rootfiles/"+data_class+"/trilepton_mumumu_SKHN"+sig_mass.at(i)+"_mumumu_cat_v7-6-6.root");
    TH1F* hist_sig = (TH1F*)file_sig->Get("n_events"+cut+"_PU");

    cout
    << "HN"+sig_mass.at(i)+" Sig" << endl
    << " (# of event) = " << hist_sig->GetBinContent(1) << endl
    << "        error = " << hist_sig->GetBinError(1) << endl
    << "   efficiency = " << hist_sig->GetEntries()/n_generated.at(i) << endl;

  }

}
