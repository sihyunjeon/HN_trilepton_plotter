#include "cutop.cc"

double PunziFunction(double eff_sig, double bkg_tot, double bkg_fake);
void printcurrunttime();
void fillarray(vector<double>& array, double start, double end, double d);


void run_cutop(int sig_mass){
  
  int SignalClass;
  if(sig_mass <= 50) SignalClass = 1;
  else if(sig_mass <= 80) SignalClass = 2;
  else if(sig_mass <= 1000) SignalClass = 3;
  else SignalClass = 4;

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");

  TString filepath = WORKING_DIR+"/rootfiles/"+dataset+"/CutOp/";
  vector<TString> bkg_prompt_list = {
    "VV",
    "Vgamma",
    "top",
    "VVV"
  };
  
  vector<double> cuts_first_pt, cuts_second_pt, cuts_third_pt, cuts_W_pri_mass;

  if(SignalClass==1||SignalClass==2){
    //cuts_first_pt = {9999999};
    //cuts_second_pt = {99999999};
    //cuts_third_pt = {999999};
    //cuts_W_pri_mass = {150};
    fillarray( cuts_first_pt, 25, 100, 5 );
    fillarray( cuts_second_pt, 15, 100, 5 );
    fillarray( cuts_third_pt, 15, 100, 5 );
    fillarray( cuts_W_pri_mass, 85, 300, 5);
  }
  else if(SignalClass==3){
    //cuts_first_pt = {20};
    //cuts_second_pt = {10};
    //cuts_third_pt = {10};
    //cuts_W_pri_mass = {200};
    fillarray( cuts_first_pt, 25, 250, 5 );
    fillarray( cuts_second_pt, 15, 200, 5 );
    fillarray( cuts_third_pt, 15, 100, 5 );
    fillarray( cuts_W_pri_mass, sig_mass*0.8, sig_mass*1.5, 10);

  }
  else if(SignalClass==4){
    //cuts_first_pt = {20};
    //cuts_second_pt = {10};
    //cuts_third_pt = {10};
    //cuts_W_pri_mass = {200};

    cuts_first_pt = {50, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 300, 310, 320, 330, 340, 350};
    cuts_second_pt = {50, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 300, 310, 320, 330, 340, 350};
    cuts_third_pt = {50, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 300, 310, 320, 330, 340, 350};
    cuts_W_pri_mass = {100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 950, 1000};
  }
  else{
    cout << "Signal Class Wrong" << endl;
    return;
  } 

  Long64_t TOTAL_it = cuts_first_pt.size()*cuts_second_pt.size()*cuts_third_pt.size()*cuts_W_pri_mass.size();
  Long64_t LogEvery = 1000;
  
  cout
  << "##################################################" << endl
  << "TOTAL # of Loop = " << TOTAL_it << endl
  << "##################################################" << endl;
  
  double cut_first_pt_SEL=0., cut_second_pt_SEL=0., cut_third_pt_SEL=0., cut_W_pri_mass_SEL=0.;
  double n_bkg_prompt_SEL=0, n_bkg_fake_SEL=0, n_sig_SEL=0, n_data_SEL=0;
  double eff_sig_SEL=0;
  double max_punzi=0;

  Long64_t this_it = 0;
  
  for(unsigned int i_first_pt=0; i_first_pt<cuts_first_pt.size(); i_first_pt++){
    for(unsigned int i_second_pt=0; i_second_pt<cuts_second_pt.size(); i_second_pt++){
      for(unsigned int i_third_pt=0; i_third_pt<cuts_third_pt.size(); i_third_pt++){
        for(unsigned int i_W_pri_mass=0; i_W_pri_mass<cuts_W_pri_mass.size(); i_W_pri_mass++){
          
          this_it++;
          if(this_it%LogEvery==0){
            cout << "["; printcurrunttime(); cout <<"] ";
            cout
            << this_it<<"/"<<TOTAL_it << " ( "<<100.*this_it/TOTAL_it<<" % ) : Current Max Punzi = " << max_punzi << endl;
						if(SignalClass==1||SignalClass==2){
							cout
							<< endl
							<< "====================================================================" << endl
							<< "(first pt) < " << cut_first_pt_SEL << " GeV" << endl
							<< "(second pt) < " << cut_second_pt_SEL << " GeV" << endl
							<< "(third pt) < " << cut_third_pt_SEL << " GeV" << endl
							<< "W_pri_mass < " << cut_W_pri_mass_SEL << " GeV" << endl;
						}
						else{
							cout
							<< endl
							<< "====================================================================" << endl
							<< "(first pt) > " << cut_first_pt_SEL << " GeV" << endl
							<< "(second pt) > " << cut_second_pt_SEL << " GeV" << endl
							<< "(third pt) > " << cut_third_pt_SEL << " GeV" << endl
							<< "W_pri_mass > " << cut_W_pri_mass_SEL << " GeV" << endl;
						}
						cout
						//<< "==> Data = " << n_data_SEL << endl
						<< "==> Prompt bkg = " << n_bkg_prompt_SEL << endl
						<< "==> Fake bkg = " << n_bkg_fake_SEL << endl
						<< "==> Total bkg = " << n_bkg_prompt_SEL+n_bkg_fake_SEL << endl
						<< "==> n_sig = " << n_sig_SEL << ", eff_sig = " << eff_sig_SEL << endl
						<< "==> Max Punzi = " << max_punzi << endl;
          }
          
          double n_bkg_prompt(0.), n_bkg_fake(0.), n_sig(0.), n_data(0.);
          
          for(unsigned int k=0; k<bkg_prompt_list.size(); k++){
            TString this_samplename = bkg_prompt_list.at(k);
            cutop m_bkg_prompt(filepath+"trilepton_mumumu_SK"+this_samplename+"_dilep_cat_"+catversion+".root", "cutop");
            m_bkg_prompt.cut_first_pt = cuts_first_pt.at(i_first_pt);
            m_bkg_prompt.cut_second_pt = cuts_second_pt.at(i_second_pt);
            m_bkg_prompt.cut_third_pt = cuts_third_pt.at(i_third_pt);
            m_bkg_prompt.cut_W_pri_mass = cuts_W_pri_mass.at(i_W_pri_mass);
            m_bkg_prompt.signalclass = SignalClass;
            m_bkg_prompt.Loop();
            n_bkg_prompt += m_bkg_prompt.n_weighted;
          }
          
          //cutop m_sig(filepath+"trilepton_mumumu_SKHN"+TString::Itoa(sig_mass, 10)+"_mumumu_VmuN_0p1_cat_"+catversion+".root", "cutop");
          cutop m_sig(filepath+"trilepton_mumumu_SKHN_MuMuMu_"+TString::Itoa(sig_mass, 10)+"_cat_"+catversion+".root", "cutop");
          m_sig.cut_first_pt = cuts_first_pt.at(i_first_pt);
          m_sig.cut_second_pt = cuts_second_pt.at(i_second_pt);
          m_sig.cut_third_pt = cuts_third_pt.at(i_third_pt);
          m_sig.cut_W_pri_mass = cuts_W_pri_mass.at(i_W_pri_mass);
          m_sig.signalclass = SignalClass;
          m_sig.Loop();
          double n_generated = 100000.;
          n_sig = m_sig.n_unweighted;
          
          cutop m_bkg_fake(filepath+"trilepton_mumumu_SKfake_sfed_HighdXY_dilep_cat_"+catversion+".root", "cutop");
          m_bkg_fake.cut_first_pt = cuts_first_pt.at(i_first_pt);
          m_bkg_fake.cut_second_pt = cuts_second_pt.at(i_second_pt);
          m_bkg_fake.cut_third_pt = cuts_third_pt.at(i_third_pt);
          m_bkg_fake.cut_W_pri_mass = cuts_W_pri_mass.at(i_W_pri_mass);
          m_bkg_fake.signalclass = SignalClass;
          m_bkg_fake.Loop();
          n_bkg_fake = m_bkg_fake.n_weighted;
          
          cutop m_data(filepath+"trilepton_mumumu_data_DoubleMuon_dilep_cat_"+catversion+".root", "cutop");
          m_data.cut_first_pt = cuts_first_pt.at(i_first_pt);
          m_data.cut_second_pt = cuts_second_pt.at(i_second_pt);
          m_data.cut_third_pt = cuts_third_pt.at(i_third_pt);
          m_data.cut_W_pri_mass = cuts_W_pri_mass.at(i_W_pri_mass);
          m_data.signalclass = SignalClass;
          m_data.Loop();
          n_data = m_data.n_weighted;
          
          
          double this_punzi = PunziFunction(n_sig/n_generated, n_bkg_prompt+n_bkg_fake, n_bkg_fake);
          
          if( this_punzi > max_punzi ){
            cut_first_pt_SEL = cuts_first_pt.at(i_first_pt);
            cut_second_pt_SEL = cuts_second_pt.at(i_second_pt);
            cut_third_pt_SEL = cuts_third_pt.at(i_third_pt);
            cut_W_pri_mass_SEL = cuts_W_pri_mass.at(i_W_pri_mass);
            
            n_bkg_prompt_SEL = n_bkg_prompt;
            n_bkg_fake_SEL = n_bkg_fake;
            n_sig_SEL = n_sig;
            eff_sig_SEL = n_sig/n_generated;
            n_data_SEL = n_data;
            max_punzi = this_punzi;
          }
          
        }
      }
    }
  }
  
  if(SignalClass==1||SignalClass==2){
    cout
    << endl
    << "====================================================================" << endl
    << "(first pt) < " << cut_first_pt_SEL << " GeV" << endl
    << "(second pt) < " << cut_second_pt_SEL << " GeV" << endl
    << "(third pt) < " << cut_third_pt_SEL << " GeV" << endl
    << "W_pri_mass < " << cut_W_pri_mass_SEL << " GeV" << endl;
  }
  else{
    cout
    << endl
    << "====================================================================" << endl
    << "(first pt) > " << cut_first_pt_SEL << " GeV" << endl
    << "(second pt) > " << cut_second_pt_SEL << " GeV" << endl
    << "(third pt) > " << cut_third_pt_SEL << " GeV" << endl
    << "W_pri_mass > " << cut_W_pri_mass_SEL << " GeV" << endl;
  }
  cout
  //<< "==> Data = " << n_data_SEL << endl
  << "==> Prompt bkg = " << n_bkg_prompt_SEL << endl
  << "==> Fake bkg = " << n_bkg_fake_SEL << endl
  << "==> Total bkg = " << n_bkg_prompt_SEL+n_bkg_fake_SEL << endl
  << "==> n_sig = " << n_sig_SEL << ", eff_sig = " << eff_sig_SEL << endl
  << "==> Max Punzi = " << max_punzi << endl;

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

void fillarray(vector<double>& array, double start, double end, double d){

  int n_total = (end-start)/d+1;

  for(int i=0; i<n_total; i++){
    array.push_back( start + d * i );
  }

}





