#include "syst_UpDowns.C"

void make_rootfile_for_limit(bool newfile=true, bool printsyst=false){

  double N_MC = 100000.;

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString LIMIT_PATH = getenv("LIMIT_PATH");

  vector<double> masses = {5, 10, 20, 30, 40, 50, 60, 70, 90, 100, 150, 200, 300, 400, 500, 700, 1000};
  vector<double> xsec = {4.046, 3.982, 3.711, 3.241, 2.619, 1.875, 1.07, 0.3828, 0.02333, 0.01082, 0.001488, 0.0004567, 9.52E-05, 3.14E-05, 1.29E-05, 3.21E-06, 6.48E-07};
  if(printsyst){
    //masses = {40, 60, 150, 700};
    //xsec = {2.619, 1.07, 0.001488, 3.21E-06};
  }
  const int n_mass = masses.size();

  TH1D *hist_mass = new TH1D("hist_mass", "", n_mass, 0, n_mass);
  TH1D *hist_xsec = new TH1D("hist_xsec", "", n_mass, 0, n_mass);
  TH1D *hist_fake = new TH1D("hist_fake", "", n_mass, 0, n_mass);
  TH1D *hist_prompt = new TH1D("hist_prompt", "", n_mass, 0, n_mass);
  TH1D *hist_signal = new TH1D("hist_signal", "", n_mass, 0, n_mass);

  vector<double> signal_syst_Lumi, signal_syst_MuonPtRes, signal_syst_JES, signal_syst_Uncl, signal_syst_MuonID;

  for(unsigned int i=0; i<masses.size(); i++){

    double mass = masses.at(i);

    // syst_UpDowns(int sig_mass, bool printnumber=true, bool forlatex=false, bool inclusive=false, bool makeroot=false)
    NLimit n_limit = syst_UpDowns(mass, false, false, false, true);

    //double mass;
    //double n_fake,   n_stat_fake,   n_syst_fake;
    //double n_prompt, n_stat_prompt, n_syst_prompt;
    //double n_signal_gen, n_signal,  n_stat_signal,  n_syst_signal;
    //double n_data;

    hist_mass->SetBinContent(i+1, n_limit.mass);
    hist_xsec->SetBinContent(i+1, 2.*100.*xsec.at(i)); // X 2.0 is for setting VeN = 0

    hist_fake->SetBinContent(i+1, n_limit.n_fake);
    hist_fake->SetBinError(i+1, n_limit.err_total(NLimit::fake));

    hist_prompt->SetBinContent(i+1, n_limit.n_prompt);
    hist_prompt->SetBinError(i+1, n_limit.err_total(NLimit::prompt));

    hist_signal->SetBinContent(i+1, n_limit.n_signal/N_MC);
    hist_signal->SetBinError(i+1, n_limit.err_total(NLimit::signal)/N_MC);

    signal_syst_Lumi.push_back( 6.2 );
    signal_syst_MuonPtRes.push_back( 100.*n_limit.signal_systs[NLimit::MuonPtRes]/n_limit.n_signal );
    signal_syst_JES.push_back( 100.*n_limit.signal_systs[NLimit::JES]/n_limit.n_signal );
    signal_syst_Uncl.push_back( 100.*n_limit.signal_systs[NLimit::Uncl]/n_limit.n_signal );
    signal_syst_MuonID.push_back( 100.*n_limit.signal_systs[NLimit::MuonID]/n_limit.n_signal );

    cout << "mass = " << n_limit.mass << ", fake = " << n_limit.n_fake << ", fakeerr = " << n_limit.err_total(NLimit::fake) << ", prompt = " << n_limit.n_prompt << ", prompterr = " << n_limit.err_total(NLimit::prompt) << ", sigeff = " << n_limit.n_signal/N_MC << ", sigefferr = " << n_limit.err_total(NLimit::signal)/N_MC << endl;

  }

  
  if(newfile){
    TFile *file = new TFile(LIMIT_PATH+"/hist.root", "RECREATE");
    file->cd();
    hist_mass->Write();
    hist_xsec->Write();
    hist_fake->Write();
    hist_prompt->Write();
    hist_signal->Write();
    file->Close();
  }

  if(printsyst){

    cout << "###################### FOR LATEX ######################" << endl;

    cout << "~~~Integrated Luminosity"<<"\t";
    for(unsigned int i=0; i<masses.size(); i++){
      cout << "& "<<std::fixed<<std::setprecision(2)<<signal_syst_Lumi.at(i)<<"\\% ";
    }
    cout << " \\\\" << endl;

    cout << "~~~Muon Momentum Resolution"<<"\t";
    for(unsigned int i=0; i<masses.size(); i++){
      cout << "& "<<std::fixed<<std::setprecision(2)<<signal_syst_MuonPtRes.at(i)<<"\\% ";
    }
    cout << " \\\\" << endl;

    cout << "~~~Muon ID"<<"\t";
    for(unsigned int i=0; i<masses.size(); i++){
      cout << "& "<<std::fixed<<std::setprecision(2)<<signal_syst_MuonID.at(i)<<"\\% ";
    }
    cout << " \\\\" << endl;

    cout << "~~~Jet Energy Scale"<<"\t";
    for(unsigned int i=0; i<masses.size(); i++){
      cout << "& "<<std::fixed<<std::setprecision(2)<<signal_syst_JES.at(i)<<"\\% ";
    }
    cout << " \\\\" << endl;

    cout << "~~~Unclustered energy"<<"\t";
    for(unsigned int i=0; i<masses.size(); i++){
      cout << "& "<<std::fixed<<std::setprecision(2)<<signal_syst_Uncl.at(i)<<"\\% ";
    }
    cout << " \\\\" << endl;

    cout << "###################### FOR SPREADSHEET ######################" << endl;

    cout << "Signal Mass"<<"\t";
    for(unsigned int i=0; i<masses.size(); i++){
      cout << masses.at(i) << "\t";
    }
    cout << endl;

    cout << "Integrated Luminosity"<<"\t";
    for(unsigned int i=0; i<masses.size(); i++){
      cout <<std::fixed<<std::setprecision(2)<<signal_syst_Lumi.at(i)<<"\t";
    }
    cout << endl;

    cout << "Muon Momentum Resolution"<<"\t";
    for(unsigned int i=0; i<masses.size(); i++){
      cout <<std::fixed<<std::setprecision(2)<<signal_syst_MuonPtRes.at(i)<<"\t";
    }
    cout << endl;

    cout << "Muon ID"<<"\t";
    for(unsigned int i=0; i<masses.size(); i++){
      cout <<std::fixed<<std::setprecision(2)<<signal_syst_MuonID.at(i)<<"\t";
    }
    cout << endl;

    cout << "Jet Energy Scale"<<"\t";
    for(unsigned int i=0; i<masses.size(); i++){
      cout <<std::fixed<<std::setprecision(2)<<signal_syst_JES.at(i)<<"\t";
    }
    cout << endl;

    cout << "Unclustered energy"<<"\t";
    for(unsigned int i=0; i<masses.size(); i++){
      cout <<std::fixed<<std::setprecision(2)<<signal_syst_Uncl.at(i)<<"\t";
    }
    cout << endl;


  }





}
