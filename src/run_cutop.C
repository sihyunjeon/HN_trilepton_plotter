#include "cutop.cc"

double PunziFunction(double eff_sig, double bkg_tot, double bkg_fake);
void printcurrunttime();

void run_cutop(int sig_mass){
  
  int SignalClass;
  if(sig_mass <= 50) SignalClass = 1;
  else if(sig_mass <= 80) SignalClass = 2;
  else if(sig_mass <= 500) SignalClass = 3;
  else SignalClass = 4;

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString dataset = WORKING_DIR+"/rootfiles/v8-0-4.8/CutOp/";
  FILE *cutop_cuts;

  vector<double> cuts_first_pt, cuts_second_pt, cuts_third_pt, cuts_W_pri_mass, cuts_PFMET;
  string define_cut;

  if(SignalClass==1||SignalClass==2){

    cuts_first_pt = {30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 55};
    cuts_second_pt = {20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 45};
    cuts_third_pt = {20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50};
    cuts_W_pri_mass = {85, 90, 95, 100, 105, 110, 115, 120, 125, 130, 135, 140, 145, 150, 155, 160, 165, 170, 175, 180, 185, 190, 195, 200, 205, 210, 215, 220};
    cuts_PFMET = {30, 32, 34, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 48, 50, 55};
  }
  else if(SignalClass==3){
    cuts_first_pt = {30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 175, 200, 225, 250};
    cuts_second_pt = {10, 15, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 175, 200};
    cuts_third_pt = {10, 15, 20, 30, 40, 50, 60, 70, 80, 90, 100, 120, 140, 160, 180, 200, 225, 250};
    cuts_W_pri_mass = {80, 85, 90, 95, 100, 125, 150, 175, 190, 200, 210, 220, 230, 240, 250, 275, 300, 350, 400, 450, 460, 470, 480, 490, 500, 510, 520, 530, 540, 550, 600};
    cuts_PFMET = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
  }
  else if(SignalClass==4){
/*    cuts_first_pt = {80, 190, 1100};
    cuts_second_pt = {30, 140, 150};
    cuts_third_pt = {20, 130};
    cuts_W_pri_mass = {50, 500, 550, 600};
    cuts_PFMET = {10, 20};*/


    cuts_first_pt = {50, 60, 70, 80, 85, 90, 95, 100, 110, 120, 130, 140, 150, 175, 200};
    cuts_second_pt = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    cuts_third_pt = {10, 15, 20, 30, 50, 100, 150, 175, 200};
    cuts_W_pri_mass = {150, 200, 250, 300, 350, 400, 425, 450, 475, 500, 525, 550, 600};
    cuts_PFMET = {10, 15, 20, 25, 30, 35, 40, 50, 100};

  }
  else{
    cout << "Signal Class Wrong" << endl;
    return;
  } 

  Long64_t TOTAL_it = cuts_first_pt.size()*cuts_second_pt.size()*cuts_third_pt.size()*cuts_W_pri_mass.size()*cuts_PFMET.size();
  Long64_t LogEvery = 500;
  
  cout
  << "##################################################" << endl
  << "TOTAL # of Loop = " << TOTAL_it << endl
  << "##################################################" << endl;
  
  double cut_first_pt_SEL=0., cut_second_pt_SEL=0., cut_third_pt_SEL=0., cut_W_pri_mass_SEL=0., cut_PFMET_SEL=0.;
  double n_bkg_fake_SEL=0, n_sig_SEL=0, n_data_SEL=0;
  double eff_sig_SEL=0;
  double max_punzi=0;

  Long64_t this_it = 0;
  
for(unsigned int i_PFMET=0; i_PFMET<cuts_PFMET.size(); i_PFMET++){
  for(unsigned int i_first_pt=0; i_first_pt<cuts_first_pt.size(); i_first_pt++){
    for(unsigned int i_second_pt=0; i_second_pt<cuts_second_pt.size(); i_second_pt++){
      for(unsigned int i_third_pt=0; i_third_pt<cuts_third_pt.size(); i_third_pt++){
        for(unsigned int i_W_pri_mass=0; i_W_pri_mass<cuts_W_pri_mass.size(); i_W_pri_mass++){
          this_it++;
          if(this_it%LogEvery==0){
            cout << "["; printcurrunttime(); cout <<"] ";
            cout
            << this_it<<"/"<<TOTAL_it << " ( "<<100.*this_it/TOTAL_it<<" % )"<<endl
            << "\t(first pt_SEL) = " << cut_first_pt_SEL << " GeV" << endl
            << "\t(second pt_SEL) = " << cut_second_pt_SEL << " GeV" << endl
            << "\t(third pt_SEL) = " << cut_third_pt_SEL << " GeV" << endl
	    << "\tW_pri_mass_SEL = " << cut_W_pri_mass_SEL << " GeV" << endl
	    << "\tPFMET_SEL = " << cut_PFMET_SEL << " GeV" << endl;
          }
          double n_bkg_fake(0.), n_sig(0.), n_data(0.);

          cutop m_data(dataset+"HNSSSFMuMuE_ntuple_data_MuonEG_cat_v8-0-4.root", "ntuple_Central");
          m_data.cut_first_pt = cuts_first_pt.at(i_first_pt);
          m_data.cut_second_pt = cuts_second_pt.at(i_second_pt);
          m_data.cut_third_pt = cuts_third_pt.at(i_third_pt);
          m_data.cut_W_pri_mass = cuts_W_pri_mass.at(i_W_pri_mass);
          m_data.cut_PFMET = cuts_PFMET.at(i_PFMET);
          m_data.signalclass = SignalClass;
          m_data.Loop();
          n_data = m_data.n_weighted;
          if(n_data < 1) continue;

          cutop m_sig(dataset+"HNSSSFMuMuE_ntuple_SKHN_SSSF_MuMuE_"+TString::Itoa(sig_mass, 10)+"_dilep_cat_v8-0-4.root", "ntuple_Central");
          m_sig.cut_first_pt = cuts_first_pt.at(i_first_pt);
          m_sig.cut_second_pt = cuts_second_pt.at(i_second_pt);
          m_sig.cut_third_pt = cuts_third_pt.at(i_third_pt);
          m_sig.cut_W_pri_mass = cuts_W_pri_mass.at(i_W_pri_mass);
	  m_sig.cut_PFMET = cuts_PFMET.at(i_PFMET);

          m_sig.signalclass = SignalClass;
          m_sig.Loop();

          double n_generated = 100000.;
          n_sig = m_sig.n_unweighted;
          cutop m_bkg_fake(dataset+"HNSSSFMuMuE_FR_ntuple_data_MuonEG_cat_v8-0-4.root", "ntuple_Central");
          m_bkg_fake.cut_first_pt = cuts_first_pt.at(i_first_pt);
          m_bkg_fake.cut_second_pt = cuts_second_pt.at(i_second_pt);
          m_bkg_fake.cut_third_pt = cuts_third_pt.at(i_third_pt);
          m_bkg_fake.cut_W_pri_mass = cuts_W_pri_mass.at(i_W_pri_mass);
	  m_bkg_fake.cut_PFMET = cuts_PFMET.at(i_PFMET);
          m_bkg_fake.signalclass = SignalClass;
          m_bkg_fake.Loop();
          n_bkg_fake = m_bkg_fake.n_weighted;
 
          double this_punzi = PunziFunction(n_sig/n_generated, n_bkg_fake, n_bkg_fake);
          if( this_punzi > max_punzi ){
            cut_first_pt_SEL = cuts_first_pt.at(i_first_pt);
            cut_second_pt_SEL = cuts_second_pt.at(i_second_pt);
            cut_third_pt_SEL = cuts_third_pt.at(i_third_pt);
            cut_W_pri_mass_SEL = cuts_W_pri_mass.at(i_W_pri_mass);
	    cut_PFMET_SEL = cuts_PFMET.at(i_PFMET);            
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
}  

  if(SignalClass==1||SignalClass==2){
    cout
    << endl
    << "====================================================================" << endl
    << "(first pt) < " << cut_first_pt_SEL << " GeV" << endl
    << "(second pt) < " << cut_second_pt_SEL << " GeV" << endl
    << "(third pt) < " << cut_third_pt_SEL << " GeV" << endl
    << "W_pri_mass < " << cut_W_pri_mass_SEL << " GeV" << endl
    << "PFMET < " << cut_PFMET_SEL << " GeV" << endl;
  }
  else{
    cout
    << endl
    << "====================================================================" << endl
    << "(first pt) > " << cut_first_pt_SEL << " GeV" << endl
    << "(second pt) > " << cut_second_pt_SEL << " GeV" << endl
    << "(third pt) > " << cut_third_pt_SEL << " GeV" << endl
    << "W_pri_mass > " << cut_W_pri_mass_SEL << " GeV" << endl
    << "PFMET > " << cut_PFMET_SEL << " GeV" << endl;

  }
  cout
//  << "==> Data = " << n_data_SEL << endl
  << "==> Fake bkg = " << n_bkg_fake_SEL << endl
  << "==> Total bkg = " << n_bkg_fake_SEL << endl
  << "==> n_sig = " << n_sig_SEL << ", eff_sig = " << eff_sig_SEL << endl
  << "==> Max Punzi = " << max_punzi << endl;
}


double PunziFunction(double eff_sig, double bkg_tot, double bkg_fake){
  
  double den = 1 + sqrt( bkg_tot + (0.32 * bkg_fake)*(0.32 * bkg_fake) );
  //double den = sqrt( bkg_tot );
  
  return eff_sig/den;
  
}


void printcurrunttime(){
  
  TDatime datime;
  cout << datime.GetYear()<<"/"<<datime.GetMonth()<<"/"<<datime.GetDay()<<" "<<datime.GetHour()<<":"<<datime.GetMinute()<<":"<<datime.GetSecond();
  
}
