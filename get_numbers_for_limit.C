void get_numbers_for_limit(){

  //TString data_class = "dXY_0p01_dZ_0p5/TTT/use_FR_method/dijet_topology";
  //TString data_class = "dXY_0p01_dZ_0p5/TTT_cluster";
  //TString data_class = "dXY_0p01_dZ_0p5/TTT_snucms_old_dilep";
  TString data_class = "dXY_0p01_dZ_0p5_leadpt_20/TTT_cluster";

  //TString cut = "_cut0";
  //TString cut = "_cutdR";
  TString cut = "_cutdR_cutW";

  TString fake = 
  "use_FR_method/dijet_topology";
  //"use_FR_method/HighdXY";
  //"use_FR_method/DiMuon_HighdXY";
  //"use_FR_method/SFed_dijet_topology";
  //"use_FR_method/SFed_HighdXY";
  //"use_FR_method/SFed_DiMuon_HighdXY";
  //"";

  TFile* file = new TFile("plots/"+data_class+"/"+fake+"/hists.root");
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

  vector<TString> sig_mass = {"40", "50", "60"};
  vector<double> n_generated = {99986, 99991, 99989};
  for(unsigned int i=0; i<sig_mass.size(); i++){

    TFile* file_sig = new TFile("rootfiles/"+data_class+"/trilepton_mumumu_SKHN"+sig_mass.at(i)+"_mumumu_new_5_3_20.root");
    TH1F* hist_sig = (TH1F*)file_sig->Get("n_events"+cut+"_PU");

    cout
    << "HN"+sig_mass.at(i)+" Sig" << endl
    << " (# of event) = " << hist_sig->GetBinContent(1) << endl
    << "        error = " << hist_sig->GetBinError(1) << endl
    << "   efficiency = " << hist_sig->GetEntries()/n_generated[i] << endl;

  }

}
