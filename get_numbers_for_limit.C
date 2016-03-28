void get_numbers_for_limit(){

  TFile* file = new TFile("plots/hists.root");
  TDirectory* dir = (TDirectory*)file->Get("_cutdR_cutW");
  TCanvas* c1 = (TCanvas*)dir->Get("n_events");
  TPad* pad1 = (TPad*)c1->GetPrimitive("c1_up");
  TH1F* hist = (TH1F*)pad1->GetPrimitive("MC_stacked_err");
  cout << hist->GetBinContent(1) << '\t' << hist->GetBinError(1) << endl;

}
