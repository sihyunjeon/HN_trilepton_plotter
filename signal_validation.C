void signal_validation(){

  vector<int> signal_mass = {40, 50, 60, 100, 150, 200, 300, 400, 500, 700, 1000};
 
  const int n_sig = signal_mass.size();
  double x[n_sig], y[n_sig];

  cout << "Signal Mass" << '\t' << "pri pt > sec pt prob." << endl;
  for(unsigned int i = 0; i < signal_mass.size(); i++){
    TFile* file = new TFile("./rootfiles/trilepton_mumumu_SKHN"+TString::Itoa(signal_mass[i], 10)+"_mumumu_new_5_3_14.root");
    TH1F* hist = (TH1F*)file->Get("pri_lep_pt_greater_check");
    cout << signal_mass[i] << '\t' << hist->GetMean() << endl;
    x[i] = signal_mass[i];
    y[i] = hist->GetMean();

  }

  TGraph* gr = new TGraph(n_sig, x, y);
  gr->Draw("ap");
  gr->SetMarkerStyle(3);
  gPad->SetLogx();
  gr->GetYaxis()->SetRangeUser(0, 1);


}
