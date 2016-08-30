#include "trilepton_mumumu.cc"
#include <fstream>

void run_trilepton_mumumu(int XXX){
  
  //==== decalre class
  trilepton_mumumu m;
  
  //==== set data class
  m.data_class =
  "v7-6-6.2/SR";
  
  //==== set prefixes and suffixes
  m.filename_prefix = "trilepton_mumumu";
  m.filename_suffix =
  "_cat_v7-6-6.root";
  m.histname_suffix = {"_cut0", "_cutdR", "_cutdR_cutW"};

  //==== set sample mapping
  m.map_sample_string_to_list["DY_MCatNLO"] = {"DY10to50_MCatNLO", "DY50plus_MCatNLO"};
  m.map_sample_string_to_list["DY_madgraph"] = {"DY50plus_madgraph"};
  m.map_sample_string_to_list["WJets_MCatNLO"] = {"WJets_MCatNLO"};
  m.map_sample_string_to_list["VV_excl_MCatNLO"] = {"WZ_lllnu_MCatNLO", "WZ_llqq_MCatNLO", "ZZ_llqq_MCatNLO", "ZZ_llll_MCatNLO"};
  m.map_sample_string_to_list["VV_excl"] = {"WZ_lllnu_powheg", "WW_llnn_powheg", "ZZ_llnunu_powheg", "ZZ_llll_powheg"};
  m.map_sample_string_to_list["VV_incl"] = {"WZ_pythia8", "WW_pythia8", "ZZ_pythia8"};
  m.map_sample_string_to_list["VVV_MCatNLO"] = {"WZZ_MCatNLO"};
  m.map_sample_string_to_list["t"] = {"singletop_s_MCatNLO", "singletop_tbar_Powheg", "singletop_t_Powheg", "singletop_tbarW_Powheg", "singletop_tW_Powheg"};
  m.map_sample_string_to_list["VV_prompt"] = {"WZ_lllnu_powheg", "ZZ_llll_powheg"};
  m.map_sample_string_to_list["others"] = {"WZZ_MCatNLO", "ttWJetsToLNu_MCatNLO"};
  m.map_sample_string_to_list["DoubleW"] = {"WpWp_madgraph", "WmWm_madgraph"};
  m.map_sample_string_to_list["fake_dijet_topology"] = {"fake_dijet_topology"};
  m.map_sample_string_to_list["fake_HighdXY"] = {"fake_HighdXY"};
  m.map_sample_string_to_list["fake_DiMuon_HighdXY"] = {"fake_HighdXY"};
  
  m.map_sample_string_to_legendinfo["DY_MCatNLO"] = make_pair("DY", kAzure+8);
  m.map_sample_string_to_legendinfo["DY_madgraph"] = make_pair("DY", kAzure+8);
  m.map_sample_string_to_legendinfo["WJets_MCatNLO"] = make_pair("WJets", kOrange);
  m.map_sample_string_to_legendinfo["VV_excl_MCatNLO"] = make_pair("VV", kGreen);
  m.map_sample_string_to_legendinfo["VV_excl"] = make_pair("VV", kGreen);
  m.map_sample_string_to_legendinfo["VV_incl"] = make_pair("VV", kGreen);
  m.map_sample_string_to_legendinfo["VVV_MCatNLO"] = make_pair("VVV", kYellow);
  m.map_sample_string_to_legendinfo["t"] = make_pair("top", kRed);
  m.map_sample_string_to_legendinfo["VV_prompt"] = make_pair("VV", kGreen);
  m.map_sample_string_to_legendinfo["others"] = make_pair("others", kRed-7);
  m.map_sample_string_to_legendinfo["DoubleW"] = make_pair("DoubleW", kRed-7);
  m.map_sample_string_to_legendinfo["fake_dijet_topology"] = make_pair("Misd", kAzure+8);
  m.map_sample_string_to_legendinfo["fake_HighdXY"] = make_pair("Misd", kAzure+8);
  m.map_sample_string_to_legendinfo["fake_DiMuon_HighdXY"] = make_pair("Misd", kAzure+8);
  
  //==== set and make sample list
  if(XXX==0) m.samples_to_use = {"DY_MCatNLO", "WJets_MCatNLO", "VV_excl_MCatNLO", "t"};
  if(XXX==1) m.samples_to_use = {"DY_MCatNLO", "WJets_MCatNLO", "VV_excl", "t"};
  if(XXX==2) m.samples_to_use = {"fake_dijet_topology", "VV_prompt"};
  if(XXX==3) m.samples_to_use = {"fake_HighdXY", "VV_prompt", "others"};
  if(XXX==4) m.samples_to_use = {"fake_DiMuon_HighdXY", "VV_prompt"};

  m.make_bkglist();
 
  //==== set variables to draw
  m.histname = {
    "HN_mass_class1", "HN_mass_class2", "HN_mass_class3", "HN_mass_class4",
    "W_pri_lowmass_mass", "W_pri_highmass_mass",
    "deltaR_OS_min", "gamma_star_mass", "n_jets", "z_candidate_mass", "h_PFMET",
    "h_leadingLepton_Pt",
    "h_secondLepton_Pt",
    "h_thirdLepton_Pt",
    "h_leadingLepton_Eta",
    "h_secondLepton_Eta",
    "h_thirdLepton_Eta",
    "h_leadingLepton_LeptonRelIso",
    "h_secondLepton_LeptonRelIso",
    "h_thirdLepton_LeptonRelIso",
    "h_leadingLepton_dXY",
    "h_secondLepton_dXY",
    "h_thirdLepton_dXY",
    "h_leadingLepton_dZ",
    "h_secondLepton_dZ",
    "h_thirdLepton_dZ",
    "h_leadingLepton_GlobalChi2",
    "h_secondLepton_GlobalChi2",
    "h_thirdLepton_GlobalChi2",
    "n_events",
    "h_nVertices"
  };
  m.x_title = {
    "m(#mu#mu#nu) [GeV]", "m(#mu#mu#nu) [GeV]", "m(#mu#mu#nu) [GeV]", "m(#mu#mu#nu) [GeV]",
    "m(#mu#mu#mu#nu) [GeV]", "m(#mu#mu#mu#nu) [GeV]",
    "#DeltaR(OS)_{min}", "m(#mu+#mu-) [GeV]", "# of jets", "m(#mu+#mu-) [GeV]", "PFMET [GeV]",
    "pT [GeV]",
    "pT [GeV]",
    "pT [GeV]",
    "#eta",
    "#eta",
    "#eta",
    "LepRelIso03",
    "LepRelIso03",
    "LepRelIso03",
    "dXY [cm]",
    "dXY [cm]",
    "dXY [cm]",
    "dZ [cm]",
    "dZ [cm]",
    "dZ [cm]",
    "GlobalChi2",
    "GlobalChi2",
    "GlobalChi2",
    "onebin",
    "# of Vertices"
  };

  //==== cut-var skips
  for(unsigned int i=0; i<m.histname.size(); i++){
    TString this_var = m.histname.at(i);
    if( this_var.Contains("class3") || this_var.Contains("class4") || this_var.Contains("highmass") ) m.CutVarSkips.push_back( make_pair("_cutdR_cutW", this_var) );
  }
  
  //==== set signal mass points
  m.signal_mass = {40, 60, 150, 700};
  m.signal_color = {kRed, kBlue, kYellow+3, kViolet};
  
  //==== set signal coupling constants
  m.coupling_constants[make_pair("_cut0", 40)] = 0.1;
  m.coupling_constants[make_pair("_cut0", 60)] = 0.1;
  m.coupling_constants[make_pair("_cut0", 150)] = 100.;
  m.coupling_constants[make_pair("_cut0", 700)] = 10000.;
  m.coupling_constants[make_pair("_cutdR", 40)] = 0.1;
  m.coupling_constants[make_pair("_cutdR", 60)] = 0.1;
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
  m.y_maxs[make_pair("_cutdR_cutW", "HN_mass_class1")] = 30;
  m.y_maxs[make_pair("_cutdR_cutW", "HN_mass_class2")] = 30;
  m.y_maxs[make_pair("_cutdR_cutW", "W_pri_lowmass_mass")] = 30;
  m.y_maxs[make_pair("_cutdR_cutW", "deltaR_OS_min")] = 30;
  m.y_maxs[make_pair("_cutdR_cutW", "gamma_star_mass")] = 30;
  m.y_maxs[make_pair("_cutdR_cutW", "n_jets")] = 30;
  m.y_maxs[make_pair("_cutdR_cutW", "z_candidate_mass")] = 30;
  m.y_maxs[make_pair("_cutdR_cutW", "h_PFMET")] = 30;
  m.y_maxs[make_pair("_cutdR_cutW", "h_leadingLepton_Pt")] = 30;
  m.y_maxs[make_pair("_cutdR_cutW", "h_secondLepton_Pt")] = 30;
  m.y_maxs[make_pair("_cutdR_cutW", "h_thirdLepton_Pt")] = 30;
  m.y_maxs[make_pair("_cutdR_cutW", "h_leadingLepton_Eta")] = 30;
  m.y_maxs[make_pair("_cutdR_cutW", "h_secondLepton_Eta")] = 30;
  m.y_maxs[make_pair("_cutdR_cutW", "h_thirdLepton_Eta")] = 30;
  m.y_maxs[make_pair("_cutdR_cutW", "h_leadingLepton_LeptonRelIso")] = 30;
  m.y_maxs[make_pair("_cutdR_cutW", "h_secondLepton_LeptonRelIso")] = 30;
  m.y_maxs[make_pair("_cutdR_cutW", "h_thirdLepton_LeptonRelIso")] = 30;
  m.y_maxs[make_pair("_cutdR_cutW", "h_leadingLepton_dXY")] = 20;
  m.y_maxs[make_pair("_cutdR_cutW", "h_secondLepton_dXY")] = 20;
  m.y_maxs[make_pair("_cutdR_cutW", "h_thirdLepton_dXY")] = 20;
  m.y_maxs[make_pair("_cutdR_cutW", "h_leadingLepton_dZ")] = 20;
  m.y_maxs[make_pair("_cutdR_cutW", "h_secondLepton_dZ")] = 20;
  m.y_maxs[make_pair("_cutdR_cutW", "h_thirdLepton_dZ")] = 20;
  m.y_maxs[make_pair("_cutdR_cutW", "h_leadingLepton_GlobalChi2")] = 30;
  m.y_maxs[make_pair("_cutdR_cutW", "h_secondLepton_GlobalChi2")] = 30;
  m.y_maxs[make_pair("_cutdR_cutW", "h_thirdLepton_GlobalChi2")] = 30;
  m.y_maxs[make_pair("_cutdR_cutW", "h_HT")] = 150;
  m.y_maxs[make_pair("_cutdR_cutW", "n_events")] = 50;
  m.y_maxs[make_pair("_cutdR_cutW", "h_nVertices")] = 50;

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
  m.x_maxs[make_pair("_cutdR_cutW", "h_PFMET")] = 100;
  
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






