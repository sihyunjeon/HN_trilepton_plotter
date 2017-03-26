#include "trilepton_mumumu.cc"
#include <fstream>

void run_trilepton_mumumu_2015(int XXX){
  
  //==== decalre class
  trilepton_mumumu m;
  
  //==== set data class
  m.data_class =
  "v8-0-2.11/";
  
  //==== set prefixes and suffixes
  m.filename_prefix = "HNSSSFMuMuE";
  m.filename_suffix =
  "_cat_v8-0-2.root";
  m.histname_suffix = {"_cut0"};

  //==== set sample mapping
  m.map_sample_string_to_list["DY_MCatNLO"] = {"DYJets_10to50", "DYJets"};
  m.map_sample_string_to_list["WJets_MCatNLO"] = {"WJets"};
  m.map_sample_string_to_list["Vgamma"] = {"WGtoLNuEE", "WGtoLNuG", "WGtoLNuMM", "ZGto2LG"};
  m.map_sample_string_to_list["VV_incl"] = {"WW", "WZ", "ZZ"};
  m.map_sample_string_to_list["VVV_incl"] = {"WWW", "WWZ", "WZZ", "ZZZ"};
  m.map_sample_string_to_list["singletop"] = {"SingleTop_s", "SingleTop_t", "SingleTop_tW", "SingleTbar_t", "SingleTbar_tW"};
  m.map_sample_string_to_list["ttbar"] = {"TTLJ_powheg", "TTLL_powheg"};
  m.map_sample_string_to_list["ttV"] = {"ttW", "ttZ"};
  m.map_sample_string_to_list["higgs"] = {"GG_HToMuMu", "VBF_HToMuMu", "ttH_bb", "ttH_nonbb"};

  m.map_sample_string_to_list["fake_HighdXY"] = {"fake_HighdXY"};
  m.map_sample_string_to_list["fake_sfed_HighdXY"] = {"fake_sfed_HighdXY"};
  m.map_sample_string_to_list["fake_pt_sfed_HighdXY"] = {"fake_pt_sfed_HighdXY"};
  m.map_sample_string_to_list["fake_DiMuon_HighdXY"] = {"fake_HighdXY"};
  
  m.map_sample_string_to_legendinfo["DY_MCatNLO"] = make_pair("DY", kAzure+8);
  m.map_sample_string_to_legendinfo["WJets_MCatNLO"] = make_pair("WJets", kGray);
  m.map_sample_string_to_legendinfo["Vgamma"] = make_pair("V#gamma", kOrange);
  m.map_sample_string_to_legendinfo["VV_incl"] = make_pair("VV", kGreen);
  m.map_sample_string_to_legendinfo["VVV_incl"] = make_pair("VVV", kOrange-7);
  m.map_sample_string_to_legendinfo["singletop"] = make_pair("singletop", kRed);
  m.map_sample_string_to_legendinfo["ttbar"] = make_pair("ttbar", kCyan+3);
  m.map_sample_string_to_legendinfo["ttV"] = make_pair("ttV", kViolet);
  m.map_sample_string_to_legendinfo["higgs"] = make_pair("higgs", kRed-7);

  m.map_sample_string_to_legendinfo["fake_HighdXY"] = make_pair("Misd", kAzure+8);
  m.map_sample_string_to_legendinfo["fake_sfed_HighdXY"] = make_pair("Misd", kAzure+8);
  m.map_sample_string_to_legendinfo["fake_pt_sfed_HighdXY"] = make_pair("Misd", kAzure+8);
  m.map_sample_string_to_legendinfo["fake_DiMuon_HighdXY"] = make_pair("Misd", kAzure+8);
  
  //==== set and make sample list
  if(XXX==0){
    m.data_class = m.data_class;
    m.samples_to_use = {"DY_MCatNLO", "WJets_MCatNLO", "Vgamma", "VV_incl", "VVV_incl", "singletop", "ttbar", "ttV", "higgs"};
  }
  if(XXX==1){
    m.data_class = m.data_class+"/before_prompt_matching";
    m.samples_to_use = {"DY_MCatNLO", "WJets_MCatNLO", "VV_excl", "t", "Wgamma", "Zgamma"};
  }
  if(XXX==2) m.samples_to_use = {"fake_HighdXY", "VV_prompt", "ttV", "ttH", "VVV_MCatNLO", "Wgamma", "Zgamma"};
  if(XXX==3) m.samples_to_use = {"fake_sfed_HighdXY", "VV_prompt", "ttV", "ttH", "VVV_MCatNLO", "Wgamma", "Zgamma"};
  if(XXX==4) m.samples_to_use = {"fake_pt_sfed_HighdXY", "VV_prompt", "ttV", "ttH", "VVV_MCatNLO", "Wgamma", "Zgamma"};

  m.make_bkglist();
cout <<"ERROR" << endl; 
  //==== set variables to draw
  m.histname = {
    "HN_mass_class1", "HN_mass_class2", "HN_mass_class3", "HN_mass_class4",
    "W_primary_highmass", "W_primary_lowmass",
    "W_secondary_highmass", "W_secondary_lowmass",
    "number_of_events", "h_NMuons", "h_NElectrons",
    "h_leadingMuonPt", "h_leadingMuonEta", "h_leadingMuondZ", "h_leadingMuondXY", "h_leadingMuondXYSig", "h_leadingMuonRelIso04",
    "h_secondMuonPt", "h_secondMuonEta", "h_secondMuondZ", "h_secondMuondXY", "h_secondMuondXYSig", "h_secondMuonRelIso04",
    "h_ElectronPt", "h_ElectronEta",
    "h_NJets", "h_JetPt", "h_JetEta",
    "h_PFMET",
    "h_HT"
  };
  m.x_title = {
    "m(#mue#nu) [GeV]", "m(#mue#nu) [GeV]", "m(#mue#nu) [GeV]", "m(#mue#nu) [GeV]",
    "m(#mu#mu#mu#nu) [GeV]", "m(#mu#mue#nu) [GeV]",
    "m(e#nu) [GeV]", "m(e#nu) [GeV]",
    "number of events", "number of muons", "number of electrons",
    "Pt [GeV]", "#eta", "dZ [cm]", "dXY [cm]", "dXY/#sigma", "Rel.Iso",
    "Pt [GeV]", "#eta", "dZ [cm]", "dXY [cm]", "dXY/#sigma", "Rel.Iso",
    "Pt [GeV]", "#eta",
    "number of jets", "Pt [GeV]", "#eta",
    "MET [GeV]",
    "Pt [GeV]"
  };

  //==== cut-var skips
  for(unsigned int i=0; i<m.histname.size(); i++){
    TString this_var = m.histname.at(i);
//    if( this_var.Contains("class3") || this_var.Contains("class4") || this_var.Contains("highmass") ) m.CutVarSkips.push_back( make_pair("_cutdR_cutW", this_var) );
  }
cout <<"ERROR"<<endl;
  //==== set signal mass points
  m.signal_mass = {40, 60, 150, 700};
  m.signal_color = {kRed, kBlue, kYellow+3, kViolet};
  
  //==== set signal coupling constants
  m.coupling_constants[make_pair("_cut0", 40)] = 0.1;
  m.coupling_constants[make_pair("_cut0", 60)] = 0.1;
  m.coupling_constants[make_pair("_cut0", 150)] = 100.;
  m.coupling_constants[make_pair("_cut0", 700)] = 10000.;
  m.coupling_constants[make_pair("_cutdR", 150)] = 100.;
  m.coupling_constants[make_pair("_cutdR", 700)] = 10000.;
  m.coupling_constants[make_pair("_cutdR_cutW", 40)] = 0.01;
  m.coupling_constants[make_pair("_cutdR_cutW", 60)] = 0.01;
  m.coupling_constants[make_pair("_cutdR_cutW", 150)] = 100.;
  m.coupling_constants[make_pair("_cutdR_cutW", 700)] = 10000.;
  
  
  //==== set signal mass for each class
  m.map_class_to_signal_mass[trilepton_mumumu::class1] = {40};
  m.map_class_to_signal_mass[trilepton_mumumu::class2] = {60};
  m.map_class_to_signal_mass[trilepton_mumumu::lowmass] = {40, 60};
  m.map_class_to_signal_mass[trilepton_mumumu::class3] = {150};
  m.map_class_to_signal_mass[trilepton_mumumu::class4] = {700};
  m.map_class_to_signal_mass[trilepton_mumumu::highmass] = {150, 700};
  
  //==== rebins
  //ofstream skeleton_rebins("./txt/skeleton_rebins.txt", ios::trunc);
  //for(unsigned int i=0; i<m.histname_suffix.size(); i++){
  //  for(unsigned int j=0; j<m.histname.size(); j++){
  //    skeleton_rebins
  //    << "  m.rebins[make_pair(\""+m.histname_suffix.at(i)+"\", \""+m.histname.at(j)+"\")] = 1;" << endl;
  //  }
  //}
  //skeleton_rebins.close();
  //return;
  m.rebins[make_pair("_cut0", "h_leadingLepton_Eta")] = 5;
  m.rebins[make_pair("_cut0", "h_secondLepton_Eta")] = 5;
  m.rebins[make_pair("_cut0", "h_thirdLepton_Eta")] = 5;
  m.rebins[make_pair("_cut0", "W_pri_highmass_mass")] = 10;
  m.rebins[make_pair("_cut0", "h_HT")] = 10;
  m.rebins[make_pair("_cutdR", "h_leadingLepton_Eta")] = 5;
  m.rebins[make_pair("_cutdR", "h_secondLepton_Eta")] = 5;
  m.rebins[make_pair("_cutdR", "h_thirdLepton_Eta")] = 5;
  m.rebins[make_pair("_cutdR", "W_pri_highmass_mass")] = 10;
  m.rebins[make_pair("_cutdR", "h_HT")] = 10;
  m.rebins[make_pair("_cutdR_cutW", "h_leadingLepton_Eta")] = 5;
  m.rebins[make_pair("_cutdR_cutW", "h_secondLepton_Eta")] = 5;
  m.rebins[make_pair("_cutdR_cutW", "h_thirdLepton_Eta")] = 5;
  m.rebins[make_pair("_cutdR_cutW", "W_pri_highmass_mass")] = 10;
  m.rebins[make_pair("_cutdR_cutW", "h_HT")] = 10;
  
  //==== y_maxs
  //ofstream skeleton_y_maxs("./txt/skeleton_y_maxs.txt", ios::trunc);
  //for(unsigned int i=0; i<m.histname_suffix.size(); i++){
  //  for(unsigned int j=0; j<m.histname.size(); j++){
  //    skeleton_y_maxs
  //    << "  m.y_maxs[make_pair(\""+m.histname_suffix.at(i)+"\", \""+m.histname.at(j)+"\")] = 1;" << endl;
  //  }
  //}
  //skeleton_y_maxs.close();
  //return;
  m.default_y_max = 1000;
  m.y_maxs[make_pair("_cut0", "HN_mass_class1")] = 100;
  m.y_maxs[make_pair("_cut0", "HN_mass_class2")] = 100;
  m.y_maxs[make_pair("_cut0", "HN_mass_class3")] = 100;
  m.y_maxs[make_pair("_cut0", "HN_mass_class4")] = 100;
  m.y_maxs[make_pair("_cut0", "W_pri_lowmass_mass")] = 100;
  m.y_maxs[make_pair("_cut0", "W_pri_highmass_mass")] = 100;
  m.y_maxs[make_pair("_cut0", "deltaR_OS_min")] = 50;
  m.y_maxs[make_pair("_cut0", "gamma_star_mass")] = 50;
  m.y_maxs[make_pair("_cut0", "n_jets")] = 250;
  m.y_maxs[make_pair("_cut0", "z_candidate_mass")] = 100;
  m.y_maxs[make_pair("_cut0", "h_PFMET")] = 100;
  m.y_maxs[make_pair("_cut0", "h_leadingLepton_Pt")] = 100;
  m.y_maxs[make_pair("_cut0", "h_secondLepton_Pt")] = 100;
  m.y_maxs[make_pair("_cut0", "h_thirdLepton_Pt")] = 200;
  m.y_maxs[make_pair("_cut0", "h_leadingLepton_Eta")] = 100;
  m.y_maxs[make_pair("_cut0", "h_secondLepton_Eta")] = 100;
  m.y_maxs[make_pair("_cut0", "h_thirdLepton_Eta")] = 100;
  m.y_maxs[make_pair("_cut0", "h_leadingLepton_LeptonRelIso")] = 300;
  m.y_maxs[make_pair("_cut0", "h_secondLepton_LeptonRelIso")] = 300;
  m.y_maxs[make_pair("_cut0", "h_thirdLepton_LeptonRelIso")] = 300;
  m.y_maxs[make_pair("_cut0", "h_leadingLepton_dXY")] = 50;
  m.y_maxs[make_pair("_cut0", "h_secondLepton_dXY")] = 50;
  m.y_maxs[make_pair("_cut0", "h_thirdLepton_dXY")] = 50;
  m.y_maxs[make_pair("_cut0", "h_leadingLepton_dZ")] = 50;
  m.y_maxs[make_pair("_cut0", "h_secondLepton_dZ")] = 50;
  m.y_maxs[make_pair("_cut0", "h_thirdLepton_dZ")] = 50;
  m.y_maxs[make_pair("_cut0", "h_leadingLepton_GlobalChi2")] = 300;
  m.y_maxs[make_pair("_cut0", "h_secondLepton_GlobalChi2")] = 300;
  m.y_maxs[make_pair("_cut0", "h_thirdLepton_GlobalChi2")] = 300;
  m.y_maxs[make_pair("_cut0", "h_HT")] = 1500;
  m.y_maxs[make_pair("_cut0", "n_events")] = 500;
  m.y_maxs[make_pair("_cut0", "h_nVertices")] = 100;
  m.y_maxs[make_pair("_cut0", "h_osllmass")] = 200;
  m.y_maxs[make_pair("_cutdR", "HN_mass_class1")] = 100;
  m.y_maxs[make_pair("_cutdR", "HN_mass_class2")] = 100;
  m.y_maxs[make_pair("_cutdR", "HN_mass_class3")] = 100;
  m.y_maxs[make_pair("_cutdR", "HN_mass_class4")] = 100;
  m.y_maxs[make_pair("_cutdR", "W_pri_lowmass_mass")] = 100;
  m.y_maxs[make_pair("_cutdR", "W_pri_highmass_mass")] = 100;
  m.y_maxs[make_pair("_cutdR", "deltaR_OS_min")] = 50;
  m.y_maxs[make_pair("_cutdR", "gamma_star_mass")] = 50;
  m.y_maxs[make_pair("_cutdR", "n_jets")] = 250;
  m.y_maxs[make_pair("_cutdR", "z_candidate_mass")] = 100;
  m.y_maxs[make_pair("_cutdR", "h_PFMET")] = 100;
  m.y_maxs[make_pair("_cutdR", "h_leadingLepton_Pt")] = 100;
  m.y_maxs[make_pair("_cutdR", "h_secondLepton_Pt")] = 100;
  m.y_maxs[make_pair("_cutdR", "h_thirdLepton_Pt")] = 200;
  m.y_maxs[make_pair("_cutdR", "h_leadingLepton_Eta")] = 100;
  m.y_maxs[make_pair("_cutdR", "h_secondLepton_Eta")] = 100;
  m.y_maxs[make_pair("_cutdR", "h_thirdLepton_Eta")] = 100;
  m.y_maxs[make_pair("_cutdR", "h_leadingLepton_LeptonRelIso")] = 300;
  m.y_maxs[make_pair("_cutdR", "h_secondLepton_LeptonRelIso")] = 300;
  m.y_maxs[make_pair("_cutdR", "h_thirdLepton_LeptonRelIso")] = 300;
  m.y_maxs[make_pair("_cutdR", "h_leadingLepton_dXY")] = 50;
  m.y_maxs[make_pair("_cutdR", "h_secondLepton_dXY")] = 50;
  m.y_maxs[make_pair("_cutdR", "h_thirdLepton_dXY")] = 50;
  m.y_maxs[make_pair("_cutdR", "h_leadingLepton_dZ")] = 50;
  m.y_maxs[make_pair("_cutdR", "h_secondLepton_dZ")] = 50;
  m.y_maxs[make_pair("_cutdR", "h_thirdLepton_dZ")] = 50;
  m.y_maxs[make_pair("_cutdR", "h_leadingLepton_GlobalChi2")] = 300;
  m.y_maxs[make_pair("_cutdR", "h_secondLepton_GlobalChi2")] = 300;
  m.y_maxs[make_pair("_cutdR", "h_thirdLepton_GlobalChi2")] = 300;
  m.y_maxs[make_pair("_cutdR", "h_HT")] = 1000;
  m.y_maxs[make_pair("_cutdR", "n_events")] = 500;
  m.y_maxs[make_pair("_cutdR", "h_nVertices")] = 100;
  m.y_maxs[make_pair("_cutdR", "h_osllmass")] = 200;
  m.y_maxs[make_pair("_cutdR_cutW", "HN_mass_class1")] = 15;
  m.y_maxs[make_pair("_cutdR_cutW", "HN_mass_class2")] = 15;
  m.y_maxs[make_pair("_cutdR_cutW", "W_pri_lowmass_mass")] = 15;
  m.y_maxs[make_pair("_cutdR_cutW", "deltaR_OS_min")] = 10;
  m.y_maxs[make_pair("_cutdR_cutW", "gamma_star_mass")] = 10;
  m.y_maxs[make_pair("_cutdR_cutW", "n_jets")] = 25;
  m.y_maxs[make_pair("_cutdR_cutW", "z_candidate_mass")] = 15;
  m.y_maxs[make_pair("_cutdR_cutW", "h_PFMET")] = 15;
  m.y_maxs[make_pair("_cutdR_cutW", "h_leadingLepton_Pt")] = 15;
  m.y_maxs[make_pair("_cutdR_cutW", "h_secondLepton_Pt")] = 15;
  m.y_maxs[make_pair("_cutdR_cutW", "h_thirdLepton_Pt")] = 25;
  m.y_maxs[make_pair("_cutdR_cutW", "h_leadingLepton_Eta")] = 15;
  m.y_maxs[make_pair("_cutdR_cutW", "h_secondLepton_Eta")] = 15;
  m.y_maxs[make_pair("_cutdR_cutW", "h_thirdLepton_Eta")] = 15;
  m.y_maxs[make_pair("_cutdR_cutW", "h_leadingLepton_LeptonRelIso")] = 15;
  m.y_maxs[make_pair("_cutdR_cutW", "h_secondLepton_LeptonRelIso")] = 15;
  m.y_maxs[make_pair("_cutdR_cutW", "h_thirdLepton_LeptonRelIso")] = 15;
  m.y_maxs[make_pair("_cutdR_cutW", "h_leadingLepton_dXY")] = 10;
  m.y_maxs[make_pair("_cutdR_cutW", "h_secondLepton_dXY")] = 10;
  m.y_maxs[make_pair("_cutdR_cutW", "h_thirdLepton_dXY")] = 10;
  m.y_maxs[make_pair("_cutdR_cutW", "h_leadingLepton_dZ")] = 10;
  m.y_maxs[make_pair("_cutdR_cutW", "h_secondLepton_dZ")] = 10;
  m.y_maxs[make_pair("_cutdR_cutW", "h_thirdLepton_dZ")] = 10;
  m.y_maxs[make_pair("_cutdR_cutW", "h_leadingLepton_GlobalChi2")] = 30;
  m.y_maxs[make_pair("_cutdR_cutW", "h_secondLepton_GlobalChi2")] = 30;
  m.y_maxs[make_pair("_cutdR_cutW", "h_thirdLepton_GlobalChi2")] = 30;
  m.y_maxs[make_pair("_cutdR_cutW", "h_HT")] = 150;
  m.y_maxs[make_pair("_cutdR_cutW", "n_events")] = 50;
  m.y_maxs[make_pair("_cutdR_cutW", "h_nVertices")] = 20;
  m.y_maxs[make_pair("_cutdR_cutW", "h_osllmass")] = 20;

  //==== x_mins
  //ofstream skeleton_x_mins("./txt/skeleton_x_mins.txt", ios::trunc);
  //for(unsigned int i=0; i<m.histname_suffix.size(); i++){
  //  for(unsigned int j=0; j<m.histname.size(); j++){
  //    skeleton_x_mins
  //    << "  m.x_mins[make_pair(\""+m.histname_suffix.at(i)+"\", \""+m.histname.at(j)+"\")] = 1;" << endl;
  //  }
  //}
  //skeleton_x_mins.close();
  //return;
  m.x_maxs[make_pair("_cut0", "h_leadingLepton_dXY")] = 0.01;
  m.x_maxs[make_pair("_cut0", "h_secondLepton_dXY")] = 0.01;
  m.x_maxs[make_pair("_cut0", "h_thirdLepton_dXY")] = 0.01;
  m.x_maxs[make_pair("_cut0", "h_leadingLepton_dZ")] = 0.05;
  m.x_maxs[make_pair("_cut0", "h_secondLepton_dZ")] = 0.05;
  m.x_maxs[make_pair("_cut0", "h_thirdLepton_dZ")] = 0.05;
  m.x_maxs[make_pair("_cut0", "h_leadingLepton_GlobalChi2")] = 10;
  m.x_maxs[make_pair("_cut0", "h_secondLepton_GlobalChi2")] = 10;
  m.x_maxs[make_pair("_cut0", "h_thirdLepton_GlobalChi2")] = 10;
  m.x_maxs[make_pair("_cut0", "h_leadingLepton_LeptonRelIso")] = 0.1;
  m.x_maxs[make_pair("_cut0", "h_secondLepton_LeptonRelIso")] = 0.1;
  m.x_maxs[make_pair("_cut0", "h_thirdLepton_LeptonRelIso")] = 0.1;
  m.x_maxs[make_pair("_cut0", "h_osllmass")] = 150;
  m.x_maxs[make_pair("_cut0", "h_PFMET")] = 150;
  m.x_maxs[make_pair("_cutdR", "h_leadingLepton_dXY")] = 0.01;
  m.x_maxs[make_pair("_cutdR", "h_secondLepton_dXY")] = 0.01;
  m.x_maxs[make_pair("_cutdR", "h_thirdLepton_dXY")] = 0.01;
  m.x_maxs[make_pair("_cutdR", "h_leadingLepton_dZ")] = 0.05;
  m.x_maxs[make_pair("_cutdR", "h_secondLepton_dZ")] = 0.05;
  m.x_maxs[make_pair("_cutdR", "h_thirdLepton_dZ")] = 0.05;
  m.x_maxs[make_pair("_cutdR", "h_leadingLepton_GlobalChi2")] = 10;
  m.x_maxs[make_pair("_cutdR", "h_secondLepton_GlobalChi2")] = 10;
  m.x_maxs[make_pair("_cutdR", "h_thirdLepton_GlobalChi2")] = 10;
  m.x_maxs[make_pair("_cutdR", "h_leadingLepton_LeptonRelIso")] = 0.1;
  m.x_maxs[make_pair("_cutdR", "h_secondLepton_LeptonRelIso")] = 0.1;
  m.x_maxs[make_pair("_cutdR", "h_thirdLepton_LeptonRelIso")] = 0.1;
  m.x_maxs[make_pair("_cutdR", "h_osllmass")] = 150;
  m.x_maxs[make_pair("_cutdR", "h_PFMET")] = 150;
  m.x_maxs[make_pair("_cutdR_cutW", "h_leadingLepton_dXY")] = 0.01;
  m.x_maxs[make_pair("_cutdR_cutW", "h_secondLepton_dXY")] = 0.01;
  m.x_maxs[make_pair("_cutdR_cutW", "h_thirdLepton_dXY")] = 0.01;
  m.x_maxs[make_pair("_cutdR_cutW", "h_leadingLepton_dZ")] = 0.05;
  m.x_maxs[make_pair("_cutdR_cutW", "h_secondLepton_dZ")] = 0.05;
  m.x_maxs[make_pair("_cutdR_cutW", "h_thirdLepton_dZ")] = 0.05;
  m.x_maxs[make_pair("_cutdR_cutW", "h_leadingLepton_GlobalChi2")] = 10;
  m.x_maxs[make_pair("_cutdR_cutW", "h_secondLepton_GlobalChi2")] = 10;
  m.x_maxs[make_pair("_cutdR_cutW", "h_thirdLepton_GlobalChi2")] = 10;
  m.x_maxs[make_pair("_cutdR_cutW", "h_leadingLepton_LeptonRelIso")] = 0.1;
  m.x_maxs[make_pair("_cutdR_cutW", "h_secondLepton_LeptonRelIso")] = 0.1;
  m.x_maxs[make_pair("_cutdR_cutW", "h_thirdLepton_LeptonRelIso")] = 0.1;
  m.x_maxs[make_pair("_cutdR_cutW", "h_leadingLepton_Pt")] = 100;
  m.x_maxs[make_pair("_cutdR_cutW", "h_secondLepton_Pt")] = 100;
  m.x_maxs[make_pair("_cutdR_cutW", "h_thirdLepton_Pt")] = 100;
  m.x_maxs[make_pair("_cutdR_cutW", "h_PFMET")] = 150;
  m.x_maxs[make_pair("_cutdR_cutW", "h_osllmass")] = 150;
  
  //==== k-factor
  m.k_factor = 1.34;
  
  //==== mixing at generation level
  m.log_of_generation_mixing = -2.;
  
  //==== prepare plot directories
  m.make_plot_directory();
  
  //==== declare output rootfiles
  m.outputfile = new TFile(m.plotpath+"/hists.root", "RECREATE");
  
  //==== finally, draw plots
  m.draw_hist();

}






