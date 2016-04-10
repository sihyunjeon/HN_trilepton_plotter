void get_numbers_for_limit(){

  //TString data_class = "TTT/use_FR_method";
  TString data_class = "TTT";

  TFile* file = new TFile("plots/"+data_class+"/hists.root");
  TDirectory* dir = (TDirectory*)file->Get("_cutdR_cutW");
  TCanvas* c1 = (TCanvas*)dir->Get("n_events");
  TPad* pad1 = (TPad*)c1->GetPrimitive("c1_up");

  TH1F* hist_data = (TH1F*)pad1->GetPrimitive("n_events_cutdR_cutW_PU_data");
  cout
  << "Data" << endl
  << " (# of event) = " << hist_data->GetBinContent(1) << endl
  << "        error = " << hist_data->GetBinError(1) << endl;

  TH1F* hist_bkg = (TH1F*)pad1->GetPrimitive("MC_stacked_err");
  cout
  << "Bkg" << endl
  << " (# of event) = " << hist_bkg->GetBinContent(1) << endl
  << "        error = " << hist_bkg->GetBinError(1) << endl;

}
