void print_signal_eff(){

  TString cmssw_version = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString filepath = WORKING_DIR+"/rootfiles/"+dataset+"/SR/";

  vector<int> masses = {5, 10, 20, 30, 40, 50, 60, 70, 90, 100, 150, 200, 300, 400, 500, 700, 1000};

/*
    GetHist("cutflow")->GetXaxis()->SetBinLabel(1,"NoCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(2,"EventCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(3,"TriggerCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(4,"VertexCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(5,"3muon");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(6,"2SS1OS");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(7,"mllsf4");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(8,"ZVeto");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(9,"bjetVeto");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(10,"LowMass");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(11,"HighMass");
*/

  for(unsigned int i=0; i<masses.size(); i++){
    int mass = masses.at(i);
    TString str_mass = TString::Itoa(mass,10);
    
    TFile *file = new TFile(filepath+"trilepton_mumumu_SKHN_MuMuMu_"+str_mass+"_cat_v8-0-2.root");
    TH1D *hist_Preselection = (TH1D*)file->Get("n_events_cut0");
    TH1D *hist_LowMass = (TH1D*)file->Get("n_events_cutWlow");
    TH1D *hist_HighMass = (TH1D*)file->Get("n_events_cutWhigh");
    
    cout
    << str_mass+" \\GeVcc\t& 100000\t& "
    <<std::fixed<<std::setprecision(4)<<100.*hist_Preselection->GetEntries()/100000.<<" $\\pm$ "
    <<std::fixed<<std::setprecision(4)<<100.*sqrt(hist_Preselection->GetEntries())/100000. << "\t& ";

    if(mass < 80){
      cout
      <<std::fixed<<std::setprecision(4)<<100.*hist_LowMass->GetEntries()/100000.<<" $\\pm$ "
      <<std::fixed<<std::setprecision(4)<<100.*sqrt(hist_LowMass->GetEntries())/100000. << "\t& "
      <<std::fixed<<std::setprecision(4)<<hist_LowMass->GetBinContent(1)<<" $\\pm$ "
      <<std::fixed<<std::setprecision(4)<<hist_LowMass->GetBinError(1)<<" \\\\"<<endl;
    }
    else{
      cout
      <<std::fixed<<std::setprecision(4)<<100.*hist_HighMass->GetEntries()/100000.<<" $\\pm$ "
      <<std::fixed<<std::setprecision(4)<<100.*sqrt(hist_HighMass->GetEntries())/100000. << "\t& "
      <<std::fixed<<std::setprecision(4)<<hist_HighMass->GetBinContent(1)<<" $\\pm$ "
      <<std::fixed<<std::setprecision(4)<<hist_HighMass->GetBinError(1)<<" \\\\"<<endl;
    }
    
  }


}
