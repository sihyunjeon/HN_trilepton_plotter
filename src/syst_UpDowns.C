#include "cutop.cc"

double PunziFunction(double eff_sig, double bkg_tot, double bkg_fake);
void printcurrunttime();
void setCutsForEachSignalMass(int sig_mass, double& cut_first_pt, double& cut_second_pt, double& cut_third_pt, double& cut_W_pri_mass, double& cut_PFMET);
double GetMeanUncert(double a, double b, bool square=false);

void syst_UpDowns(int sig_mass, bool forlatex=false, bool inclusive=false){

  TH1::SetDefaultSumw2(true);

  double uncert_lumi = 0.046;
  double uncert_fake = 0.26;
  double N_MC = 100000.;

  TString region = "Preselection";
  //TString region = "WZ";
  //TString region = "ZJets";
  
  int SignalClass;
  if(sig_mass <= 50) SignalClass = 1;
  else if(sig_mass <= 80) SignalClass = 2;
  else if(sig_mass <= 1000) SignalClass = 3;
  else SignalClass = 4;

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");

  TString filepath = WORKING_DIR+"/rootfiles/"+dataset+"/UpDownSyst/";

  vector<TString> bkg_prompt_list = {
    "WZTo3LNu_powheg",
    "ZZTo4L_powheg",
    "Vgamma",
    "top",
    "VVV"
  };
  
  double cut_first_pt, cut_second_pt, cut_third_pt, cut_W_pri_mass, cut_PFMET;
  setCutsForEachSignalMass(sig_mass, cut_first_pt, cut_second_pt, cut_third_pt, cut_W_pri_mass, cut_PFMET);

  if(inclusive){

    if(sig_mass < 80){
      cut_first_pt = 99999999.;
      cut_second_pt = 99999999.;
      cut_third_pt = 99999999.;
      cut_W_pri_mass = 150;
      cut_PFMET = 0.;
    }
    else{
      cut_first_pt = 20.;
      cut_second_pt = 10.;
      cut_third_pt = 10.;
      cut_W_pri_mass = 0.;
      cut_PFMET = 20.;
    }

  }

  if(!forlatex){
    if(SignalClass==1||SignalClass==2){
      cout
      << endl
      << "====================================================================" << endl
      << "(first pt) < " << cut_first_pt << " GeV" << endl
      << "(second pt) < " << cut_second_pt << " GeV" << endl
      << "(third pt) < " << cut_third_pt << " GeV" << endl
      << "W_pri_mass < " << cut_W_pri_mass << " GeV" << endl
      << "====================================================================" << endl << endl;
    }
    else{
      cout
      << endl
      << "====================================================================" << endl
      << "(first pt) > " << cut_first_pt << " GeV" << endl
      << "(second pt) > " << cut_second_pt << " GeV" << endl
      << "(third pt) > " << cut_third_pt << " GeV" << endl
      << "W_pri_mass > " << cut_W_pri_mass << " GeV" << endl
      << "PFMET > " << cut_PFMET << " GeV" << endl
      << "====================================================================" << endl << endl;
    }
  }

  vector<TString> systtypes = {"Central", "MuonEn_up", "MuonEn_down", "JetEn_up", "JetEn_down", "JetRes_up", "JetRes_down", "Unclustered_up", "Unclustered_down", "MCxsec_up", "MCxsec_down", "MuonIDSF_up", "MuonIDSF_down"};
  vector<double> yields_prompt, yields_fake, yields_data, yields_signal;
  vector<double> uncerts_prompt, uncerts_fake, uncerts_data, uncerts_signal;
  double stat_error_prompt, stat_error_fake, stat_error_data, stat_error_signal;

  for(int i=0; i<systtypes.size(); i++){

    TString this_syst = systtypes.at(i);
    if(this_syst.Contains("MCxsec_")) this_syst = "Central";
          
    double n_bkg_prompt(0.), n_bkg_fake(0.), n_data(0.), n_signal(0.);
    
    TH1D *hist_bkg_for_error = NULL;
    if(systtypes.at(i)=="Central") hist_bkg_for_error = new TH1D("hist_bkg_for_error", "", 1, 0., 1.);
    
    for(unsigned int k=0; k<bkg_prompt_list.size(); k++){
      TString this_samplename = bkg_prompt_list.at(k);
      cutop m_bkg_prompt(filepath+"trilepton_mumumu_ntp_SK"+this_samplename+"_dilep_cat_"+catversion+".root", "Ntp_"+this_syst);
      m_bkg_prompt.SearchRegion = region;
      m_bkg_prompt.cut_first_pt = cut_first_pt;
      m_bkg_prompt.cut_second_pt = cut_second_pt;
      m_bkg_prompt.cut_third_pt = cut_third_pt;
      m_bkg_prompt.cut_W_pri_mass = cut_W_pri_mass;
      m_bkg_prompt.cut_PFMET = cut_PFMET;
      m_bkg_prompt.signalclass = SignalClass;
      m_bkg_prompt.Loop();
      
      if(systtypes.at(i)=="Central"){
        hist_bkg_for_error->Add(m_bkg_prompt.hist_for_error);

        if(!forlatex) cout << this_samplename << " : " << m_bkg_prompt.n_weighted << ", error = " << m_bkg_prompt.hist_for_error->GetBinError(1) << endl;
      }

      if(systtypes.at(i).Contains("MCxsec_")){

        if(systtypes.at(i) == "MCxsec_up"){
          if(this_samplename=="WZTo3LNu_powheg"){
            n_bkg_prompt += (1+0.01*12.)*m_bkg_prompt.n_weighted;
          }
          else if(this_samplename=="ZZTo4L_powheg"){
            n_bkg_prompt += (1+0.01*13.)*m_bkg_prompt.n_weighted;
          }
          else if(this_samplename=="Vgamma"){
            n_bkg_prompt += (1+0.01*6.)*m_bkg_prompt.n_weighted;
          }
          else if(this_samplename=="top"){
            n_bkg_prompt += (1+0.01*6.)*m_bkg_prompt.n_weighted;
          }
          else if(this_samplename=="VV"){
            n_bkg_prompt += (1+0.01*15.)*m_bkg_prompt.n_weighted;
          }
          else{
            n_bkg_prompt += m_bkg_prompt.n_weighted;
          }
        }
        else if(systtypes.at(i) == "MCxsec_down"){
          if(this_samplename=="WZTo3LNu_powheg"){
            n_bkg_prompt += (1-0.01*12)*m_bkg_prompt.n_weighted;
          }
          else if(this_samplename=="ZZTo4L_powheg"){
            n_bkg_prompt += (1-0.01*13)*m_bkg_prompt.n_weighted;
          }
          else if(this_samplename=="Vgamma"){
            n_bkg_prompt += (1-0.01*6.)*m_bkg_prompt.n_weighted;
          }
          else if(this_samplename=="top"){
            n_bkg_prompt += (1-0.01*6.)*m_bkg_prompt.n_weighted;
          }
          else if(this_samplename=="VV"){
            n_bkg_prompt += (1-0.01*15.)*m_bkg_prompt.n_weighted;
          }
          else{
            n_bkg_prompt += m_bkg_prompt.n_weighted;
          }
        }
        else{ }
  

      }
      else{
        n_bkg_prompt += m_bkg_prompt.n_weighted;
      }

    }

    cutop m_bkg_fake(filepath+"trilepton_mumumu_ntp_SKfake_sfed_HighdXY_dilep_cat_"+catversion+".root", "Ntp_"+this_syst);
    m_bkg_fake.SearchRegion = region;
    m_bkg_fake.cut_first_pt = cut_first_pt;
    m_bkg_fake.cut_second_pt = cut_second_pt;
    m_bkg_fake.cut_third_pt = cut_third_pt;
    m_bkg_fake.cut_W_pri_mass = cut_W_pri_mass;
    m_bkg_fake.cut_PFMET = cut_PFMET;
    m_bkg_fake.signalclass = SignalClass;
    m_bkg_fake.Loop();
    n_bkg_fake = m_bkg_fake.n_weighted;

    cutop m_sig(filepath+"trilepton_mumumu_ntp_SKHN_MuMuMu_"+TString::Itoa(sig_mass, 10)+"_cat_"+catversion+".root", "Ntp_"+this_syst);
    m_sig.SearchRegion = region;
    m_sig.cut_first_pt = cut_first_pt;
    m_sig.cut_second_pt = cut_second_pt;
    m_sig.cut_third_pt = cut_third_pt;
    m_sig.cut_W_pri_mass = cut_W_pri_mass;
    m_sig.cut_PFMET = cut_PFMET;
    m_sig.signalclass = SignalClass;
    m_sig.Loop();
    n_signal = m_sig.n_unweighted;
    //n_signal = m_sig.n_weighted;
    
    cutop m_data(filepath+"trilepton_mumumu_ntp_data_DoubleMuon_cat_"+catversion+".root", "Ntp_"+this_syst);
    m_data.SearchRegion = region;
    m_data.cut_first_pt = cut_first_pt;
    m_data.cut_second_pt = cut_second_pt;
    m_data.cut_third_pt = cut_third_pt;
    m_data.cut_W_pri_mass = cut_W_pri_mass;
    m_data.cut_PFMET = cut_PFMET;
    m_data.signalclass = SignalClass;
    m_data.Loop();
    n_data = m_data.n_weighted;

    yields_prompt.push_back(n_bkg_prompt);
    yields_fake.push_back(n_bkg_fake);
    yields_signal.push_back(n_signal);
    yields_data.push_back(n_data);

    uncerts_prompt.push_back( (n_bkg_prompt-yields_prompt.at(0))/yields_prompt.at(0) );
    uncerts_fake.push_back( (n_bkg_fake-yields_fake.at(0))/yields_fake.at(0) );
    uncerts_signal.push_back( (n_signal-yields_signal.at(0))/yields_signal.at(0) );
    uncerts_data.push_back( (n_data-yields_data.at(0))/yields_data.at(0) );
    
    if(systtypes.at(i)=="Central"){
      stat_error_prompt = hist_bkg_for_error->GetBinError(1);
      
      double err_fake_sumw2 = m_bkg_fake.hist_for_error->GetBinError(1);

      double err_fake_prop = m_bkg_fake.hist_for_error_up->GetBinContent(1) - m_bkg_fake.hist_for_error->GetBinContent(1);
      stat_error_fake = sqrt(err_fake_sumw2*err_fake_sumw2+err_fake_prop*err_fake_prop);
      
      stat_error_data = m_data.hist_for_error->GetBinError(1);
      stat_error_signal = m_sig.hist_for_error->GetBinError(1);;
    }
          
  }

  double squared_uncert_prompt = uncert_lumi*uncert_lumi;
  for(unsigned int i=1; i<uncerts_prompt.size(); i++) squared_uncert_prompt += 0.5*uncerts_prompt.at(i)*uncerts_prompt.at(i);
  double squared_uncert_fake = uncert_fake*uncert_fake;
  for(unsigned int i=1; i<uncerts_fake.size(); i++) squared_uncert_fake += 0.5*uncerts_fake.at(i)*uncerts_fake.at(i);
  double squared_uncert_signal = uncert_lumi*uncert_lumi;
  for(unsigned int i=1; i<uncerts_signal.size(); i++) squared_uncert_signal += 0.5*uncerts_signal.at(i)*uncerts_signal.at(i);
  
  if(forlatex){

    TString str_mass = TString::Itoa(sig_mass, 10);

    //==== low mass
    if(sig_mass < 80){
      cout
      <<str_mass<<"\t& $< "<<cut_W_pri_mass<<"$\t& $< "<<cut_first_pt<<"$\t& $< "<<cut_second_pt<<"$\t& $< "<<cut_third_pt << "$\t& "
      <<"$"<<std::fixed<<std::setprecision(2)<<yields_prompt.at(0)
      <<" \\pm "<<std::fixed<<std::setprecision(2)<<stat_error_prompt<<"~\\stat"
      <<" \\pm "<<std::fixed<<std::setprecision(2)<<yields_prompt.at(0)*sqrt(squared_uncert_prompt) << "~\\syst$\t& "
      <<"$"<<std::fixed<<std::setprecision(2)<<yields_fake.at(0)
      <<" \\pm "<<std::fixed<<std::setprecision(2)<<stat_error_fake<<"~\\stat"
      <<" \\pm "<<std::fixed<<std::setprecision(2)<<yields_fake.at(0)*sqrt(squared_uncert_fake) << "~\\syst$\t& "
      <<"$"<<std::fixed<<std::setprecision(2)<<yields_prompt.at(0)+yields_fake.at(0)
      <<" \\pm "<<std::fixed<<std::setprecision(2)<<sqrt(stat_error_prompt*stat_error_prompt+stat_error_fake*stat_error_fake)<<"~\\stat"
      <<" \\pm "<<std::fixed<<std::setprecision(2)<<sqrt(yields_prompt.at(0)*yields_prompt.at(0)*squared_uncert_prompt+yields_fake.at(0)*yields_fake.at(0)*squared_uncert_fake) << "~\\syst$\t& "
      <<"$"<<std::fixed<<std::setprecision(2)<<100.*yields_signal.at(0)/N_MC
      <<" \\pm "<<std::fixed<<std::setprecision(2)<<100.*stat_error_signal/N_MC<<"~\\stat"
      <<" \\pm "<<std::fixed<<std::setprecision(2)<<100.*yields_signal.at(0)*sqrt(squared_uncert_signal)/N_MC << "$\t& "
      <<"$9999$ \\\\" << endl;
    }
    //==== high mass
    else{
      cout
      <<str_mass<<"\t& $> "<<cut_W_pri_mass<<"$\t& $> "<<cut_PFMET<<"$\t& $> "<<cut_first_pt<<"$\t& $> "<<cut_second_pt<<"$\t& $> "<<cut_third_pt << "$\t& "
      <<"$"<<std::fixed<<std::setprecision(2)<<yields_prompt.at(0)
      <<" \\pm "<<std::fixed<<std::setprecision(2)<<stat_error_prompt<<"~\\stat"
      <<" \\pm "<<std::fixed<<std::setprecision(2)<<yields_prompt.at(0)*sqrt(squared_uncert_prompt) << "~\\syst$\t& "
      <<"$"<<std::fixed<<std::setprecision(2)<<yields_fake.at(0)
      <<" \\pm "<<std::fixed<<std::setprecision(2)<<stat_error_fake<<"~\\stat"
      <<" \\pm "<<std::fixed<<std::setprecision(2)<<yields_fake.at(0)*sqrt(squared_uncert_fake) << "~\\syst$\t& "
      <<"$"<<std::fixed<<std::setprecision(2)<<yields_prompt.at(0)+yields_fake.at(0)
      <<" \\pm "<<std::fixed<<std::setprecision(2)<<sqrt(stat_error_prompt*stat_error_prompt+stat_error_fake*stat_error_fake)<<"~\\stat"
      <<" \\pm "<<std::fixed<<std::setprecision(2)<<sqrt(yields_prompt.at(0)*yields_prompt.at(0)*squared_uncert_prompt+yields_fake.at(0)*yields_fake.at(0)*squared_uncert_fake) << "~\\syst$\t& "
      <<"$"<<std::fixed<<std::setprecision(2)<<100.*yields_signal.at(0)/N_MC
      <<" \\pm "<<std::fixed<<std::setprecision(2)<<100.*stat_error_signal/N_MC<<"~\\stat"
      <<" \\pm "<<std::fixed<<std::setprecision(2)<<100.*yields_signal.at(0)*sqrt(squared_uncert_signal)/N_MC << "~\\syst$\t& "
      <<"$9999$ \\\\" << endl;
    }

  }
  else{
    cout << endl << "######################### Results #########################" << endl;
    //==== Prompt Systematic
    cout
    << "[Prompt]" << endl
    << "Central Value = " << yields_prompt.at(0) << endl
    << "Muon Resolution" << endl
    << "  Up   = " << yields_prompt.at(1) << " ==> Diff = " << yields_prompt.at(1)-yields_prompt.at(0) << " ("<<100.*uncerts_prompt.at(1)<<")" << endl
    << "  Down = " << yields_prompt.at(2) << " ==> Diff = " << yields_prompt.at(2)-yields_prompt.at(0) << " ("<<100.*uncerts_prompt.at(2)<<")" << endl
    << "  Mean = " << 100.*GetMeanUncert(uncerts_prompt.at(1), uncerts_prompt.at(2)) << endl
    << "JES" << endl
    << "  Up   = " << yields_prompt.at(3) << " ==> Diff = " << yields_prompt.at(3)-yields_prompt.at(0) << " ("<<100.*uncerts_prompt.at(3)<<")" << endl
    << "  Down = " << yields_prompt.at(4) << " ==> Diff = " << yields_prompt.at(4)-yields_prompt.at(0) << " ("<<100.*uncerts_prompt.at(4)<<")" << endl
    << "  Mean = " << 100.*GetMeanUncert(uncerts_prompt.at(3), uncerts_prompt.at(4)) << endl
    << "JER" << endl
    << "  Up   = " << yields_prompt.at(5) << " ==> Diff = " << yields_prompt.at(5)-yields_prompt.at(0) << " ("<<100.*uncerts_prompt.at(5)<<")" << endl
    << "  Down = " << yields_prompt.at(6) << " ==> Diff = " << yields_prompt.at(6)-yields_prompt.at(0) << " ("<<100.*uncerts_prompt.at(6)<<")" << endl
    << "  Mean = " << 100.*GetMeanUncert(uncerts_prompt.at(5), uncerts_prompt.at(6)) << endl
    << "Uncluestered" << endl
    << "  Up   = " << yields_prompt.at(7) << " ==> Diff = " << yields_prompt.at(7)-yields_prompt.at(0) << " ("<<100.*uncerts_prompt.at(7)<<")" << endl
    << "  Down = " << yields_prompt.at(8) << " ==> Diff = " << yields_prompt.at(8)-yields_prompt.at(0) << " ("<<100.*uncerts_prompt.at(8)<<")" << endl
    << "  Mean = " << 100.*GetMeanUncert(uncerts_prompt.at(7), uncerts_prompt.at(8)) << endl
    << "MCxsec" << endl
    << "  Up   = " << yields_prompt.at(9) << " ==> Diff = " << yields_prompt.at(9)-yields_prompt.at(0) << " ("<<100.*uncerts_prompt.at(9)<<")" << endl
    << "  Down = " << yields_prompt.at(10) << " ==> Diff = " << yields_prompt.at(10)-yields_prompt.at(0) << " ("<<100.*uncerts_prompt.at(10)<<")" << endl
    << "  Mean = " << 100.*GetMeanUncert(uncerts_prompt.at(9), uncerts_prompt.at(10)) << endl
    << "ID SF" << endl
    << "  Up   = " << yields_prompt.at(11) << " ==> Diff = " << yields_prompt.at(11)-yields_prompt.at(0) << " ("<<100.*uncerts_prompt.at(11)<<")" << endl
    << "  Down = " << yields_prompt.at(12) << " ==> Diff = " << yields_prompt.at(12)-yields_prompt.at(0) << " ("<<100.*uncerts_prompt.at(12)<<")" << endl
    << "  Mean = " << 100.*GetMeanUncert(uncerts_prompt.at(11), uncerts_prompt.at(12)) << endl;
    cout << "=====================> total % = " << 100.*sqrt(squared_uncert_prompt) << endl;
    cout << "=====================> total # = " << yields_prompt.at(0)*sqrt(squared_uncert_prompt) << endl;
    
    //==== Fake Systematic
    cout
    << "[Fake]" << endl
    << "Central Value = " << yields_fake.at(0) << endl
    << "Muon Resolution" << endl
    << "  Up   = " << yields_fake.at(1) << " ==> Diff = " << yields_fake.at(1)-yields_fake.at(0) << " ("<<100.*uncerts_fake.at(1)<<")" << endl
    << "  Down = " << yields_fake.at(2) << " ==> Diff = " << yields_fake.at(2)-yields_fake.at(0) << " ("<<100.*uncerts_fake.at(2)<<")" << endl
    << "  Mean = " << 100.*GetMeanUncert(uncerts_fake.at(1), uncerts_fake.at(2)) << endl
    << "JES" << endl
    << "  Up   = " << yields_fake.at(3) << " ==> Diff = " << yields_fake.at(3)-yields_fake.at(0) << " ("<<100.*uncerts_fake.at(3)<<")" << endl
    << "  Down = " << yields_fake.at(4) << " ==> Diff = " << yields_fake.at(4)-yields_fake.at(0) << " ("<<100.*uncerts_fake.at(4)<<")" << endl
    << "  Mean = " << 100.*GetMeanUncert(uncerts_fake.at(3), uncerts_fake.at(4)) << endl
    << "JER" << endl
    << "  Up   = " << yields_fake.at(5) << " ==> Diff = " << yields_fake.at(5)-yields_fake.at(0) << " ("<<100.*uncerts_fake.at(5)<<")" << endl
    << "  Down = " << yields_fake.at(6) << " ==> Diff = " << yields_fake.at(6)-yields_fake.at(0) << " ("<<100.*uncerts_fake.at(6)<<")" << endl
    << "  Mean = " << 100.*GetMeanUncert(uncerts_fake.at(5), uncerts_fake.at(6)) << endl
    << "Uncluestered" << endl
    << "  Up   = " << yields_fake.at(7) << " ==> Diff = " << yields_fake.at(7)-yields_fake.at(0) << " ("<<100.*uncerts_fake.at(7)<<")" << endl
    << "  Down = " << yields_fake.at(8) << " ==> Diff = " << yields_fake.at(8)-yields_fake.at(0) << " ("<<100.*uncerts_fake.at(8)<<")" << endl
    << "  Mean = " << 100.*GetMeanUncert(uncerts_fake.at(7), uncerts_fake.at(8)) << endl;
    cout << "=====================> total % = " << 100.*sqrt(squared_uncert_fake) << endl;
    cout << "=====================> total # = " << yields_fake.at(0)*sqrt(squared_uncert_fake) << endl;
    
    //==== signal Systematic
    cout
    << "[signal]" << endl
    << "Central Value = " << yields_signal.at(0) << endl
    << "Muon Resolution" << endl
    << "  Up   = " << yields_signal.at(1) << " ==> Diff = " << yields_signal.at(1)-yields_signal.at(0) << " ("<<100.*uncerts_signal.at(1)<<")" << endl
    << "  Down = " << yields_signal.at(2) << " ==> Diff = " << yields_signal.at(2)-yields_signal.at(0) << " ("<<100.*uncerts_signal.at(2)<<")" << endl
    << "  Mean = " << 100.*GetMeanUncert(uncerts_signal.at(1), uncerts_signal.at(2)) << endl
    << "JES" << endl
    << "  Up   = " << yields_signal.at(3) << " ==> Diff = " << yields_signal.at(3)-yields_signal.at(0) << " ("<<100.*uncerts_signal.at(3)<<")" << endl
    << "  Down = " << yields_signal.at(4) << " ==> Diff = " << yields_signal.at(4)-yields_signal.at(0) << " ("<<100.*uncerts_signal.at(4)<<")" << endl
    << "  Mean = " << 100.*GetMeanUncert(uncerts_signal.at(3), uncerts_signal.at(4)) << endl
    << "JER" << endl
    << "  Up   = " << yields_signal.at(5) << " ==> Diff = " << yields_signal.at(5)-yields_signal.at(0) << " ("<<100.*uncerts_signal.at(5)<<")" << endl
    << "  Down = " << yields_signal.at(6) << " ==> Diff = " << yields_signal.at(6)-yields_signal.at(0) << " ("<<100.*uncerts_signal.at(6)<<")" << endl
    << "  Mean = " << 100.*GetMeanUncert(uncerts_signal.at(5), uncerts_signal.at(6)) << endl
    << "Uncluestered" << endl
    << "  Up   = " << yields_signal.at(7) << " ==> Diff = " << yields_signal.at(7)-yields_signal.at(0) << " ("<<100.*uncerts_signal.at(7)<<")" << endl
    << "  Down = " << yields_signal.at(8) << " ==> Diff = " << yields_signal.at(8)-yields_signal.at(0) << " ("<<100.*uncerts_signal.at(8)<<")" << endl
    << "  Mean = " << 100.*GetMeanUncert(uncerts_signal.at(7), uncerts_signal.at(8)) << endl
    << "ID SF" << endl
    << "  Up   = " << yields_signal.at(11) << " ==> Diff = " << yields_signal.at(11)-yields_signal.at(0) << " ("<<100.*uncerts_signal.at(11)<<")" << endl
    << "  Down = " << yields_signal.at(12) << " ==> Diff = " << yields_signal.at(12)-yields_signal.at(0) << " ("<<100.*uncerts_signal.at(12)<<")" << endl
    << "  Mean = " << 100.*GetMeanUncert(uncerts_signal.at(11), uncerts_signal.at(12)) << endl;
    cout << "=====================> total % = " << 100.*sqrt(squared_uncert_signal) << endl;
    cout << "=====================> total # = " << yields_signal.at(0)*sqrt(squared_uncert_signal) << endl;
  }

}


double PunziFunction(double eff_sig, double bkg_tot, double bkg_fake){
  
  double den = 1 + sqrt( bkg_tot + (0.30 * bkg_fake)*(0.30 * bkg_fake) );
  //double den = sqrt( bkg_tot );
  
  return eff_sig/den;
  
}


void printcurrunttime(){
  
  TDatime datime;
  cout << datime.GetYear()<<"/"<<datime.GetMonth()<<"/"<<datime.GetDay()<<" "<<datime.GetHour()<<":"<<datime.GetMinute()<<":"<<datime.GetSecond();
  
}

void setCutsForEachSignalMass(int sig_mass, double& cut_first_pt, double& cut_second_pt, double& cut_third_pt, double& cut_W_pri_mass, double& cut_PFMET){

  if(sig_mass == 5){
    cut_first_pt = 100.;
    cut_second_pt = 45.;
    cut_third_pt = 35.;
    cut_W_pri_mass = 125.;
    cut_PFMET = 0.;
  }
  else if(sig_mass == 10){
    cut_first_pt = 60.;
    cut_second_pt = 55.;
    cut_third_pt = 35.;
    cut_W_pri_mass = 110.;
    cut_PFMET = 0.;
  }
  else if(sig_mass == 20){
    cut_first_pt = 100.;
    cut_second_pt = 55.;
    cut_third_pt = 50.;
    cut_W_pri_mass = 105.;
    cut_PFMET = 0.;
  }
  else if(sig_mass == 30){
    cut_first_pt = 40.;
    cut_second_pt = 30.;
    cut_third_pt = 25.;
    cut_W_pri_mass = 115.;
    cut_PFMET = 0.;
  }
  else if(sig_mass == 40){
    cut_first_pt = 35.;
    cut_second_pt = 30.;
    cut_third_pt = 25.;
    cut_W_pri_mass = 115.;
    cut_PFMET = 0.;
  }
  else if(sig_mass == 50){
    cut_first_pt = 30.;
    cut_second_pt = 30.;
    cut_third_pt = 25.;
    cut_W_pri_mass = 95.;
    cut_PFMET = 0.;
  }
  else if(sig_mass == 60){
    cut_first_pt = 30.;
    cut_second_pt = 25.;
    cut_third_pt = 25.;
    cut_W_pri_mass = 95.;
    cut_PFMET = 0.;
  }
  else if(sig_mass == 70){
    cut_first_pt = 100.;
    cut_second_pt = 75.;
    cut_third_pt = 45.;
    cut_W_pri_mass = 85.;
    cut_PFMET = 0.;
  }
  else if(sig_mass == 90){
    cut_first_pt = 40.;
    cut_second_pt = 35.;
    cut_third_pt = 15.;
    cut_W_pri_mass = 80.;
    cut_PFMET = 20.;
  }
  else if(sig_mass == 100){
    cut_first_pt = 25.;
    cut_second_pt = 20.;
    cut_third_pt = 15.;
    cut_W_pri_mass = 110.;
    cut_PFMET = 35.;
  }
  else if(sig_mass == 150){
    cut_first_pt = 25.;
    cut_second_pt = 35.;
    cut_third_pt = 20.;
    cut_W_pri_mass = 180.;
    cut_PFMET = 20.;
  }
  else if(sig_mass == 200){
    cut_first_pt = 60.;
    cut_second_pt = 50.;
    cut_third_pt = 25.;
    cut_W_pri_mass = 240.;
    cut_PFMET = 20.;
  }
  else if(sig_mass == 300){
    cut_first_pt = 100.;
    cut_second_pt = 55.;
    cut_third_pt = 25.;
    cut_W_pri_mass = 360.;
    cut_PFMET = 20.;
  }
  else if(sig_mass == 400){
    cut_first_pt = 110.;
    cut_second_pt = 55.;
    cut_third_pt = 25.;
    cut_W_pri_mass = 480.;
    cut_PFMET = 20.;
  }
  else if(sig_mass == 500){
    cut_first_pt = 130.;
    cut_second_pt = 110.;
    cut_third_pt = 20.;
    cut_W_pri_mass = 590.;
    cut_PFMET = 30.;
  }
  else if(sig_mass == 700){
    cut_first_pt = 190.;
    cut_second_pt = 100.;
    cut_third_pt = 45.;
    cut_W_pri_mass = 800.;
    cut_PFMET = 20.;
  }
  else{
    cout << "Wrong Signal Mass" << endl;
    cut_first_pt = 9999999;
    cut_second_pt = 9999999;
    cut_third_pt = 99999999;
    cut_W_pri_mass = 99999999;
  }

}

double GetMeanUncert(double a, double b, bool square){

  if(!square) return sqrt(0.5*(a*a+b*b));
  else return 0.5*(a*a+b*b);

}





