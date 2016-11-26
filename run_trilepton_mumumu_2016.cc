#include "trilepton_mumumu.cc"
#include <fstream>

void run_trilepton_mumumu_2016(int XXX){
  
  //==== decalre class
  trilepton_mumumu m;
  
  //==== set data class
  m.data_class =
  "v8-0-2.4/SR";
  
  //==== set prefixes and suffixes
  m.filename_prefix = "trilepton_mumumu";
  m.filename_suffix =
  "_cat_v8-0-2.root";
  m.histname_suffix = {"_cut0", "_cutdR", "_cutdR_cutW"};

  m.DrawPU = true;

  //==== set sample mapping
  m.map_sample_string_to_list["DY"] = {"DYJets_10to50", "DYJets"};
  m.map_sample_string_to_list["WJets"] = {"WJets"};
  m.map_sample_string_to_list["VV_excl"] = {"WZTo3LNu_powheg", "ZZTo4L_powheg"};
  m.map_sample_string_to_list["VV_incl"] = {"WZ", "WW", "ZZ"};
  m.map_sample_string_to_list["WZ_excl"] = {"WZTo3LNu_powheg"};
  m.map_sample_string_to_list["ZZ_excl"] = {"ZZTo4L_powheg"};
  m.map_sample_string_to_list["VVV"] = {"WWW", "WWZ", "WZZ", "ZZZ"};
  m.map_sample_string_to_list["ttbar"] = {"TTJets_aMC"};
  m.map_sample_string_to_list["ttV"] = {"ttW", "ttZ"};
  m.map_sample_string_to_list["ttH"] = {"ttH_nonbb"};
  m.map_sample_string_to_list["Wgamma"] = {"WGtoLNuG", "WGtoLNuMM"};
  m.map_sample_string_to_list["Zgamma"] = {"ZGto2LG"};
  m.map_sample_string_to_list["fake_HighdXY"] = {"fake_HighdXY"};
  m.map_sample_string_to_list["fake_sfed_HighdXY"] = {"fake_sfed_HighdXY"};
  m.map_sample_string_to_list["fake_pt_sfed_HighdXY"] = {"fake_pt_sfed_HighdXY"};
  m.map_sample_string_to_list["fake_DiMuon_HighdXY"] = {"fake_HighdXY"};

  m.map_sample_string_to_legendinfo["DY"] = make_pair("DY", kAzure+8);
  m.map_sample_string_to_legendinfo["WJets"] = make_pair("WJets", kOrange);
  m.map_sample_string_to_legendinfo["VV_excl"] = make_pair("VV", kGreen);
  m.map_sample_string_to_legendinfo["VV_incl"] = make_pair("VV", kGreen);
  m.map_sample_string_to_legendinfo["WZ_excl"] = make_pair("WZ", kGreen);
  m.map_sample_string_to_legendinfo["ZZ_excl"] = make_pair("ZZ", kRed-7);
  m.map_sample_string_to_legendinfo["VVV"] = make_pair("VVV", kOrange-7);
  m.map_sample_string_to_legendinfo["ttbar"] = make_pair("ttbar", kRed);
  m.map_sample_string_to_legendinfo["ttV"] = make_pair("ttV", kCyan+3);
  m.map_sample_string_to_legendinfo["ttH"] = make_pair("ttH", kViolet);
  m.map_sample_string_to_legendinfo["Wgamma"] = make_pair("W#gamma", kOrange);
  m.map_sample_string_to_legendinfo["Zgamma"] = make_pair("Z#gamma", kOrange);
  m.map_sample_string_to_legendinfo["fake_HighdXY"] = make_pair("Misd", kAzure+8);
  m.map_sample_string_to_legendinfo["fake_sfed_HighdXY"] = make_pair("Misd", kAzure+8);
  m.map_sample_string_to_legendinfo["fake_pt_sfed_HighdXY"] = make_pair("Misd", kAzure+8);
  m.map_sample_string_to_legendinfo["fake_DiMuon_HighdXY"] = make_pair("Misd", kAzure+8);
  
  //==== set and make sample list
  if(XXX==0){
    m.data_class = m.data_class+"/before_prompt_matching";
    m.samples_to_use = {"DY_MCatNLO", "WJets_MCatNLO", "VV_excl_MCatNLO", "t", "ttV", "ttH", "VVV_MCatNLO"};
  }
  if(XXX==1) m.samples_to_use = {"fake_HighdXY", "VV_excl", "ttV", "ttH", "VVV", "Wgamma", "Zgamma"};
  if(XXX==2) m.samples_to_use = {"fake_sfed_HighdXY", "VV_excl", "ttV", "ttH", "VVV", "Wgamma", "Zgamma"};
  if(XXX==3) m.samples_to_use = {"fake_pt_sfed_HighdXY", "VV_excl", "ttV", "ttH", "VVV", "Wgamma", "Zgamma"};

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
    "h_nVertices",
    "h_osllmass"
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
    "LepRelIso04",
    "LepRelIso04",
    "LepRelIso04",
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
    "# of Vertices",
    "m(OS) [GeV]"
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
  
  m.y_maxs[make_pair("_cut0", "deltaR_OS_min")] = 200;
  m.y_maxs[make_pair("_cut0", "gamma_star_mass")] = 400;
  m.y_maxs[make_pair("_cut0", "h_leadingLepton_dXY")] = 500;
  m.y_maxs[make_pair("_cut0", "h_leadingLepton_dZ")] = 100;
  m.y_maxs[make_pair("_cut0", "h_leadingLepton_Eta")] = 800;
  m.y_maxs[make_pair("_cut0", "h_leadingLepton_GlobalChi2")] = 2000;
  m.y_maxs[make_pair("_cut0", "h_leadingLepton_LeptonRelIso")] = 2000;
  m.y_maxs[make_pair("_cut0", "h_leadingLepton_Pt")] = 1000;
  m.y_maxs[make_pair("_cut0", "h_nVertices")] = 500;
  m.y_maxs[make_pair("_cut0", "h_osllmass")] = 2000;
  m.y_maxs[make_pair("_cut0", "h_PFMET")] = 500;
  m.y_maxs[make_pair("_cut0", "h_secondLepton_dXY")] = 500;
  m.y_maxs[make_pair("_cut0", "h_secondLepton_dZ")] = 100;
  m.y_maxs[make_pair("_cut0", "h_secondLepton_Eta")] = 800;
  m.y_maxs[make_pair("_cut0", "h_secondLepton_GlobalChi2")] = 2000;
  m.y_maxs[make_pair("_cut0", "h_secondLepton_LeptonRelIso")] = 2000;
  m.y_maxs[make_pair("_cut0", "h_secondLepton_Pt")] = 1000;
  m.y_maxs[make_pair("_cut0", "h_thirdLepton_dXY")] = 500;
  m.y_maxs[make_pair("_cut0", "h_thirdLepton_dZ")] = 100;
  m.y_maxs[make_pair("_cut0", "h_thirdLepton_Eta")] = 800;
  m.y_maxs[make_pair("_cut0", "h_thirdLepton_GlobalChi2")] = 2000;
  m.y_maxs[make_pair("_cut0", "h_thirdLepton_LeptonRelIso")] = 2000;
  m.y_maxs[make_pair("_cut0", "h_thirdLepton_Pt")] = 2000;
  m.y_maxs[make_pair("_cut0", "HN_mass_class1")] = 1000;
  m.y_maxs[make_pair("_cut0", "HN_mass_class2")] = 1000;
  m.y_maxs[make_pair("_cut0", "HN_mass_class3")] = 1000;
  m.y_maxs[make_pair("_cut0", "HN_mass_class4")] = 1000;
  m.y_maxs[make_pair("_cut0", "n_events")] = 10000;
  m.y_maxs[make_pair("_cut0", "n_jets")] = 2000;
  m.y_maxs[make_pair("_cut0", "W_pri_lowmass_mass")] = 400;
  m.y_maxs[make_pair("_cut0", "W_pri_highmass_mass")] = 1000;
  m.y_maxs[make_pair("_cut0", "z_candidate_mass")] = 1000;
  m.y_maxs[make_pair("_cutdR", "deltaR_OS_min")] = 200;
  m.y_maxs[make_pair("_cutdR", "gamma_star_mass")] = 400;
  m.y_maxs[make_pair("_cutdR", "h_leadingLepton_dXY")] = 500;
  m.y_maxs[make_pair("_cutdR", "h_leadingLepton_dZ")] = 100;
  m.y_maxs[make_pair("_cutdR", "h_leadingLepton_Eta")] = 800;
  m.y_maxs[make_pair("_cutdR", "h_leadingLepton_GlobalChi2")] = 2000;
  m.y_maxs[make_pair("_cutdR", "h_leadingLepton_LeptonRelIso")] = 2000;
  m.y_maxs[make_pair("_cutdR", "h_leadingLepton_Pt")] = 1000;
  m.y_maxs[make_pair("_cutdR", "h_nVertices")] = 500;
  m.y_maxs[make_pair("_cutdR", "h_osllmass")] = 2000;
  m.y_maxs[make_pair("_cutdR", "h_PFMET")] = 500;
  m.y_maxs[make_pair("_cutdR", "h_secondLepton_dXY")] = 500;
  m.y_maxs[make_pair("_cutdR", "h_secondLepton_dZ")] = 100;
  m.y_maxs[make_pair("_cutdR", "h_secondLepton_Eta")] = 800;
  m.y_maxs[make_pair("_cutdR", "h_secondLepton_GlobalChi2")] = 2000;
  m.y_maxs[make_pair("_cutdR", "h_secondLepton_LeptonRelIso")] = 2000;
  m.y_maxs[make_pair("_cutdR", "h_secondLepton_Pt")] = 1000;
  m.y_maxs[make_pair("_cutdR", "h_thirdLepton_dXY")] = 500;
  m.y_maxs[make_pair("_cutdR", "h_thirdLepton_dZ")] = 100;
  m.y_maxs[make_pair("_cutdR", "h_thirdLepton_Eta")] = 800;
  m.y_maxs[make_pair("_cutdR", "h_thirdLepton_GlobalChi2")] = 2000;
  m.y_maxs[make_pair("_cutdR", "h_thirdLepton_LeptonRelIso")] = 2000;
  m.y_maxs[make_pair("_cutdR", "h_thirdLepton_Pt")] = 2000;
  m.y_maxs[make_pair("_cutdR", "HN_mass_class1")] = 1000;
  m.y_maxs[make_pair("_cutdR", "HN_mass_class2")] = 1000;
  m.y_maxs[make_pair("_cutdR", "HN_mass_class3")] = 1000;
  m.y_maxs[make_pair("_cutdR", "HN_mass_class4")] = 1000;
  m.y_maxs[make_pair("_cutdR", "n_events")] = 10000;
  m.y_maxs[make_pair("_cutdR", "n_jets")] = 2000;
  m.y_maxs[make_pair("_cutdR", "W_pri_lowmass_mass")] = 400;
  m.y_maxs[make_pair("_cutdR", "W_pri_highmass_mass")] = 1000;
  m.y_maxs[make_pair("_cutdR", "z_candidate_mass")] = 1000;
  m.y_maxs[make_pair("_cutdR_cutW", "deltaR_OS_min")] = 40;
  m.y_maxs[make_pair("_cutdR_cutW", "gamma_star_mass")] = 40;
  m.y_maxs[make_pair("_cutdR_cutW", "h_leadingLepton_dXY")] = 30;
  m.y_maxs[make_pair("_cutdR_cutW", "h_leadingLepton_dZ")] = 20;
  m.y_maxs[make_pair("_cutdR_cutW", "h_leadingLepton_Eta")] = 50;
  m.y_maxs[make_pair("_cutdR_cutW", "h_leadingLepton_GlobalChi2")] = 150;
  m.y_maxs[make_pair("_cutdR_cutW", "h_leadingLepton_LeptonRelIso")] = 200;
  m.y_maxs[make_pair("_cutdR_cutW", "h_leadingLepton_Pt")] = 100;
  m.y_maxs[make_pair("_cutdR_cutW", "h_nVertices")] = 30;
  m.y_maxs[make_pair("_cutdR_cutW", "h_osllmass")] = 60;
  m.y_maxs[make_pair("_cutdR_cutW", "h_PFMET")] = 60;
  m.y_maxs[make_pair("_cutdR_cutW", "h_secondLepton_dXY")] = 30;
  m.y_maxs[make_pair("_cutdR_cutW", "h_secondLepton_dZ")] = 20;
  m.y_maxs[make_pair("_cutdR_cutW", "h_secondLepton_Eta")] = 50;
  m.y_maxs[make_pair("_cutdR_cutW", "h_secondLepton_GlobalChi2")] = 150;
  m.y_maxs[make_pair("_cutdR_cutW", "h_secondLepton_LeptonRelIso")] = 200;
  m.y_maxs[make_pair("_cutdR_cutW", "h_secondLepton_Pt")] = 100;
  m.y_maxs[make_pair("_cutdR_cutW", "h_thirdLepton_dXY")] = 30;
  m.y_maxs[make_pair("_cutdR_cutW", "h_thirdLepton_dZ")] = 20;
  m.y_maxs[make_pair("_cutdR_cutW", "h_thirdLepton_Eta")] = 50;
  m.y_maxs[make_pair("_cutdR_cutW", "h_thirdLepton_GlobalChi2")] = 150;
  m.y_maxs[make_pair("_cutdR_cutW", "h_thirdLepton_LeptonRelIso")] = 200;
  m.y_maxs[make_pair("_cutdR_cutW", "h_thirdLepton_Pt")] = 150;
  m.y_maxs[make_pair("_cutdR_cutW", "HN_mass_class1")] = 100;
  m.y_maxs[make_pair("_cutdR_cutW", "HN_mass_class2")] = 100;
  m.y_maxs[make_pair("_cutdR_cutW", "n_events")] = 200;
  m.y_maxs[make_pair("_cutdR_cutW", "n_jets")] = 150;
  m.y_maxs[make_pair("_cutdR_cutW", "W_pri_lowmass_mass")] = 150;
  m.y_maxs[make_pair("_cutdR_cutW", "z_candidate_mass")] = 40;
  
  
  
  
  
  
 
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






