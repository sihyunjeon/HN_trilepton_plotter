void get_numbers_for_CR(){

  TString data_class = "dXY_0p01_dZ_0p5_leadpt_20/";

  vector<TString> CRs = {"CR1", "CR2"};
  vector<TString> sig_mass = {"40", "50", "60"};
  vector<double> n_generated = {99986, 99991, 99989};
  
  for(unsigned int i=0; i<CRs.size(); i++){
    TFile* file_data = new TFile("rootfiles/"+data_class+CRs.at(i)+"/trilepton_mumumu_CR_SKdata_5_3_20.root");
    TH1F* hist_data = (TH1F*)file_data->Get("TT_n_events_control_PU");
    for(unsigned int j=0; j<sig_mass.size(); j++){
      TFile* file_sig = new TFile("rootfiles/"+data_class+CRs.at(i)+"/trilepton_mumumu_CR_SKHN"+sig_mass.at(j)+"_mumumu_new_5_3_20.root");
      TH1F* hist_sig = (TH1F*)file_sig->Get("TT_n_events_control_PU");
      cout
      << "HN"+sig_mass.at(j)+" Sig" << endl
      << " (# of event in "+CRs.at(i)+") = " << hist_sig->GetBinContent(1) << endl
      << " ===> Eff = " << hist_sig->GetEntries()/n_generated.at(j) << endl
      << " ===> Signal/Data ( at |VmN|^2 = 10^-4 ) = " << 0.0001*hist_sig->GetBinContent(1)/hist_data->GetBinContent(1) << endl;
    }
  }


}
