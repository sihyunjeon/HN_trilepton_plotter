#include "cutop.C"

double PunziFunction(double eff_sig, double bkg_tot, double bkg_fake);
void printcurrunttime();
void setCutsForEachSignalMass(int sig_mass, double& cut_first_pt, double& cut_second_pt, double& cut_third_pt, double& cut_W_pri_mass);

void run_syst_UpDowns(int sig_mass){
  
  int SignalClass;
  if(sig_mass <= 50) SignalClass = 1;
  else if(sig_mass <= 80) SignalClass = 2;
  else if(sig_mass <= 500) SignalClass = 3;
  else SignalClass = 4;

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString dataset = WORKING_DIR+"/rootfiles/v8-0-2.9/UpDownSyst/";
  vector<TString> bkg_prompt_list = {
    "VV",
    "Vgamma",
    "top",
    "VVV"
  };
  
  double cut_first_pt, cut_second_pt, cut_third_pt, cut_W_pri_mass;
  setCutsForEachSignalMass(sig_mass, cut_first_pt, cut_second_pt, cut_third_pt, cut_W_pri_mass);

  vector<TString> systtypes = {"Central", "MuonEn_up", "MuonEn_down", "JetEn_up", "JetEn_down", "JetRes_up", "JetRes_down", "Unclustered_up", "Unclustered_down"};
  vector<double> yields_prompt, yields_fake, yields_data, yields_signal;

  for(int i=0; i<systtypes.size(); i++){

    TString this_syst = systtypes.at(i);
    //cout << this_syst << endl;
          
		double n_bkg_prompt(0.), n_bkg_fake(0.), n_data(0.), n_sig(0.);
		
		for(unsigned int k=0; k<bkg_prompt_list.size(); k++){
			TString this_samplename = bkg_prompt_list.at(k);
			cutop m_bkg_prompt(dataset+"trilepton_mumumu_ntp_SK"+this_samplename+"_dilep_cat_v8-0-2.root", "Ntp_"+this_syst);
			m_bkg_prompt.cut_first_pt = cut_first_pt;
			m_bkg_prompt.cut_second_pt = cut_second_pt;
			m_bkg_prompt.cut_third_pt = cut_third_pt;
			m_bkg_prompt.cut_W_pri_mass = cut_W_pri_mass;
			m_bkg_prompt.signalclass = SignalClass;
			m_bkg_prompt.Loop();
			n_bkg_prompt += m_bkg_prompt.n_weighted;
		}

    cutop m_bkg_fake(dataset+"trilepton_mumumu_ntp_SKfake_sfed_HighdXY_dilep_cat_v8-0-2.root", "Ntp_"+this_syst);
    m_bkg_fake.cut_first_pt = cut_first_pt;
    m_bkg_fake.cut_second_pt = cut_second_pt;
    m_bkg_fake.cut_third_pt = cut_third_pt;
    m_bkg_fake.cut_W_pri_mass = cut_W_pri_mass;
    m_bkg_fake.signalclass = SignalClass;
    m_bkg_fake.Loop();
    n_bkg_fake = m_bkg_fake.n_weighted;

		cutop m_sig(dataset+"trilepton_mumumu_ntp_SKHN"+TString::Itoa(sig_mass, 10)+"_mumumu_VmuN_0p1_cat_v8-0-2.root", "Ntp_"+this_syst);
		m_sig.cut_first_pt = cut_first_pt;
		m_sig.cut_second_pt = cut_second_pt;
		m_sig.cut_third_pt = cut_third_pt;
		m_sig.cut_W_pri_mass = cut_W_pri_mass;
		m_sig.signalclass = SignalClass;
		m_sig.Loop();
		n_sig = m_sig.n_unweighted;
		
		cutop m_data(dataset+"trilepton_mumumu_ntp_data_DoubleMuon_cat_v8-0-2.root", "Ntp_"+this_syst);
		m_data.cut_first_pt = cut_first_pt;
		m_data.cut_second_pt = cut_second_pt;
		m_data.cut_third_pt = cut_third_pt;
		m_data.cut_W_pri_mass = cut_W_pri_mass;
		m_data.signalclass = SignalClass;
		m_data.Loop();
		n_data = m_data.n_weighted;

    yields_prompt.push_back(n_bkg_prompt);
    yields_fake.push_back(n_bkg_fake);
    yields_signal.push_back(n_sig);
    yields_data.push_back(n_data);
          
  }

  //==== get difference
  for(unsigned int i=0; i<systtypes.size(); i++){
    //==== Print Centreal Value
    if(i==0){
      cout
      << "==== Central Values for Check! ====" << endl
      << "Prompt = " << yields_prompt.at(0) << endl
      << "Fake = " << yields_fake.at(0) << endl
      << "HN"<<sig_mass<<" Signal = " << yields_signal.at(i) << endl
      << "==== Differences for each Syst. types ====" << endl;
    }
    else{
      cout
      << "["<<systtypes.at(i) << "]" << endl
      << "  Prompt = " << yields_prompt.at(i) << " ==> Diff = " << yields_prompt.at(i)-yields_prompt.at(0) << " ("<<100.*(yields_prompt.at(i)-yields_prompt.at(0))/yields_prompt.at(0)<<")" << endl
      << "  Fake = " << yields_fake.at(i) << " ==> Diff = " << yields_fake.at(i)-yields_fake.at(0) << " ("<<100.*(yields_fake.at(i)-yields_fake.at(0))/yields_fake.at(0)<<")" << endl
      << "  HN "<<sig_mass<<" Signal = " << yields_signal.at(i) << " ==> Diff = " << yields_signal.at(i)-yields_signal.at(0) << " ("<<100.*(yields_signal.at(i)-yields_signal.at(0))/yields_signal.at(0)<<")" << endl;
    }


  }

}


double PunziFunction(double eff_sig, double bkg_tot, double bkg_fake){
  
  double den = 1 + sqrt( bkg_tot + (0.35 * bkg_fake)*(0.35 * bkg_fake) );
  //double den = sqrt( bkg_tot );
  
  return eff_sig/den;
  
}


void printcurrunttime(){
  
  TDatime datime;
  cout << datime.GetYear()<<"/"<<datime.GetMonth()<<"/"<<datime.GetDay()<<" "<<datime.GetHour()<<":"<<datime.GetMinute()<<":"<<datime.GetSecond();
  
}

void setCutsForEachSignalMass(int sig_mass, double& cut_first_pt, double& cut_second_pt, double& cut_third_pt, double& cut_W_pri_mass){

  if(sig_mass == 40){
    cut_first_pt = 55;
    cut_second_pt = 55;
    cut_third_pt = 40;
    cut_W_pri_mass = 90;
  }
  else if(sig_mass == 60){
    cut_first_pt = 30;
    cut_second_pt = 30;
    cut_third_pt = 25;
    cut_W_pri_mass = 90;
  }
  else if(sig_mass == 150){
    cut_first_pt = 55;
    cut_second_pt = 45;
    cut_third_pt = 25;
    cut_W_pri_mass = 190;
  }
  else if(sig_mass == 700){
    cut_first_pt = 180;
    cut_second_pt = 140;
    cut_third_pt = 50;
    cut_W_pri_mass = 850;
  }
  else{
    cout << "Wrong Signal Mass" << endl;
    cut_first_pt = 9999999;
    cut_second_pt = 9999999;
    cut_third_pt = 99999999;
    cut_W_pri_mass = 99999999;
  }

}







