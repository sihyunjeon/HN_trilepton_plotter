#include "trilepton_mumumu.cc"
#include <fstream>

void run_trilepton_mumumu(int XXX){
  
  //==== decalre class
  trilepton_mumumu m;
  
  //==== set data class
  m.data_class =
  //"dXY_0p2_dZ_0p5/TTT";
  //"dXY_0p01_dZ_0p5/TTT_cluster";
  "dXY_0p01_dZ_0p5_leadpt_20/SR";
  //"dXY_0p01_dZ_0p5/TTT_snucms_old_dilep";
  //"dXY_0p005_dZ_0p1/TTT";
  
  //==== set prefixes and suffixes
  m.filename_prefix = "trilepton_mumumu_SK";
  m.filename_suffix =
  //"_5_3_14.root";
  "_5_3_20.root";
  m.histname_suffix = {"_cut0", "_cutdR", "_cutdR_cutW"};

  //==== set sample mapping
  m.map_sample_string_to_list["DY"] = {"DY10to50", "DY50plus"};
  m.map_sample_string_to_list["VV"] = {"WZtollln_mg", "WZtollqq_mg", "WZtoqqln_mg", "ZZtollll_mg", "ZZtollnn_mg", "ZZtollqq_mg", "WW_mg"};
  m.map_sample_string_to_list["VV_prompt"] = {"WZtollln_mg", "ZZtollll_mg"};
  m.map_sample_string_to_list["others"] = {"TTG", "TTWW", "WWG", "WWW", "WWZ", "WZZ", "ZZZ", "ttZ", "ttW"};
  m.map_sample_string_to_list["Higgs"] = {"HtoWW", "ggHtoZZ"};
  m.map_sample_string_to_list["Higgs_prompt"] = {"ggHtoZZ"};
  m.map_sample_string_to_list["Wgamma"] = {"Wtollln_new"};
  m.map_sample_string_to_list["Vbb"] = {"Wbb", "Zbb"};
  m.map_sample_string_to_list["Wjets"] = {"Wjets"};
  m.map_sample_string_to_list["ttbar"] = {"ttbar"};
  m.map_sample_string_to_list["fake_dijet_topology"] = {"fake_dijet_topology"};
  m.map_sample_string_to_list["fake_MCTruth_ttbar_central"] = {"fake_MCTruth_ttbar_central"};
  m.map_sample_string_to_list["fake_HighdXY"] = {"fake_HighdXY"};
  m.map_sample_string_to_list["fake_DiMuon_HighdXY"] = {"fake_DiMuon_HighdXY"};
  m.map_sample_string_to_list["fake_DiMuon_HighdXY_n_jets"] = {"fake_DiMuon_HighdXY_n_jets"};
  m.map_sample_string_to_list["fake_sfed_dijet_topology"] = {"fake_sfed_dijet_topology"};
  m.map_sample_string_to_list["fake_sfed_MCTruth_ttbar_central"] = {"fake_sfed_MCTruth_ttbar_central"};
  m.map_sample_string_to_list["fake_sfed_HighdXY"] = {"fake_sfed_HighdXY"};
  m.map_sample_string_to_list["fake_sfed_DiMuon_HighdXY"] = {"fake_sfed_DiMuon_HighdXY"};
  m.map_sample_string_to_list["fake_sfed_DiMuon_HighdXY_n_jets"] = {"fake_sfed_DiMuon_HighdXY_n_jets"};
  
  m.map_sample_string_to_legendinfo["DY"] = make_pair("DY", kAzure+8);
  m.map_sample_string_to_legendinfo["VV"] = make_pair("VV", kGreen);
  m.map_sample_string_to_legendinfo["VV_prompt"] = make_pair("VV", kGreen);
  m.map_sample_string_to_legendinfo["others"] = make_pair("others", kRed-7);
  m.map_sample_string_to_legendinfo["Higgs"] = make_pair("Higgs", kYellow);
  m.map_sample_string_to_legendinfo["Higgs_prompt"] = make_pair("Higgs", kYellow);
  m.map_sample_string_to_legendinfo["Wgamma"] = make_pair("W#gamma", kOrange);
  m.map_sample_string_to_legendinfo["Vbb"] = make_pair("V+bb", kRed+3);
  m.map_sample_string_to_legendinfo["Wjets"] = make_pair("Wjets", kGray);
  m.map_sample_string_to_legendinfo["ttbar"] = make_pair("ttbar", kGray);
  m.map_sample_string_to_legendinfo["fake_dijet_topology"] = make_pair("Misd", kAzure+8);
  m.map_sample_string_to_legendinfo["fake_MCTruth_ttbar_central"] = make_pair("Misd", kAzure+8);
  m.map_sample_string_to_legendinfo["fake_HighdXY"] = make_pair("Misd", kAzure+8);
  m.map_sample_string_to_legendinfo["fake_DiMuon_HighdXY"] = make_pair("Misd", kAzure+8);
  m.map_sample_string_to_legendinfo["fake_DiMuon_HighdXY_n_jets"] = make_pair("Misd", kAzure+8);
  m.map_sample_string_to_legendinfo["fake_sfed_dijet_topology"] = make_pair("Misd", kAzure+8);
  m.map_sample_string_to_legendinfo["fake_sfed_MCTruth_ttbar_central"] = make_pair("Misd", kAzure+8);
  m.map_sample_string_to_legendinfo["fake_sfed_HighdXY"] = make_pair("Misd", kAzure+8);
  m.map_sample_string_to_legendinfo["fake_sfed_DiMuon_HighdXY"] = make_pair("Misd", kAzure+8);
  m.map_sample_string_to_legendinfo["fake_sfed_DiMuon_HighdXY_n_jets"] = make_pair("Misd", kAzure+8);
  
  //==== set and make sample list
  if(XXX==0) m.samples_to_use = {"DY", "VV", "Higgs", "Wgamma", "Vbb", "Wjets", "others"};
  if(XXX==1) m.samples_to_use = {"fake_dijet_topology", "VV_prompt", "Higgs_prompt", "Wgamma"};
  if(XXX==2) m.samples_to_use = {"fake_HighdXY", "VV_prompt", "Higgs_prompt", "Wgamma"};
  if(XXX==3) m.samples_to_use = {"fake_DiMuon_HighdXY", "VV_prompt", "Higgs_prompt", "Wgamma"};
  if(XXX==4) m.samples_to_use = {"fake_DiMuon_HighdXY_n_jets", "VV_prompt", "Higgs_prompt", "Wgamma"};
  if(XXX==5) m.samples_to_use = {"fake_sfed_dijet_topology", "VV_prompt", "Higgs_prompt", "Wgamma"};
  if(XXX==6) m.samples_to_use = {"fake_sfed_HighdXY", "VV_prompt", "Higgs_prompt", "Wgamma"};
  if(XXX==7) m.samples_to_use = {"fake_sfed_DiMuon_HighdXY", "VV_prompt", "Higgs_prompt", "Wgamma"};
  if(XXX==8) m.samples_to_use = {"fake_sfed_DiMuon_HighdXY_n_jets", "VV_prompt", "Higgs_prompt", "Wgamma"};

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
    "h_HT",
    "h_nVertices",
    "h_Nbjets",
    "h_TTL_mTT",
    "h_TLL_mTL_Z"
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
    "H_{T} [GeV]",
    "# of Vertices",
    "# of b-tagged jets",
    "m(TT) [GeV]",
    "m(TL) [GeV]"
  };

  //==== cut-var skips
  for(unsigned int i=0; i<m.histname.size(); i++){
    TString this_var = m.histname.at(i);
    if( this_var.Contains("class3") || this_var.Contains("class4") || this_var.Contains("highmass") ) m.CutVarSkips.push_back( make_pair("_cutdR_cutW", this_var) );
  }
  
  //==== set signal mass points
  m.signal_mass = {40, 50, 60, 150, 700};
  m.signal_color = {kRed, kBlack, kBlue, kYellow+3, kViolet};
  
  //==== set signal coupling constants
  m.coupling_constants[make_pair("_cut0", 40)] = 0.001;
  m.coupling_constants[make_pair("_cut0", 50)] = 0.001;
  m.coupling_constants[make_pair("_cut0", 60)] = 0.001;
  m.coupling_constants[make_pair("_cut0", 150)] = 1.;
  m.coupling_constants[make_pair("_cut0", 700)] = 1000.;
  m.coupling_constants[make_pair("_cutdR", 40)] = 0.001;
  m.coupling_constants[make_pair("_cutdR", 50)] = 0.001;
  m.coupling_constants[make_pair("_cutdR", 60)] = 0.001;
  m.coupling_constants[make_pair("_cutdR", 150)] = 1.;
  m.coupling_constants[make_pair("_cutdR", 700)] = 1000.;
  m.coupling_constants[make_pair("_cutdR_cutW", 40)] = 0.0001;
  m.coupling_constants[make_pair("_cutdR_cutW", 50)] = 0.0001;
  m.coupling_constants[make_pair("_cutdR_cutW", 60)] = 0.0001;
  m.coupling_constants[make_pair("_cutdR_cutW", 150)] = 1.;
  m.coupling_constants[make_pair("_cutdR_cutW", 700)] = 1000.;
  
  
  //==== set signal mass for each class
  m.map_class_to_signal_mass[trilepton_mumumu::class1] = {40, 50};
  m.map_class_to_signal_mass[trilepton_mumumu::class2] = {60};
  m.map_class_to_signal_mass[trilepton_mumumu::lowmass] = {40, 50, 60};
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
  m.y_maxs[make_pair("_cut0", "HN_mass_class1")] = 300;
  m.y_maxs[make_pair("_cut0", "HN_mass_class2")] = 300;
  m.y_maxs[make_pair("_cut0", "HN_mass_class3")] = 300;
  m.y_maxs[make_pair("_cut0", "HN_mass_class4")] = 300;
  m.y_maxs[make_pair("_cut0", "W_pri_lowmass_mass")] = 400;
  m.y_maxs[make_pair("_cut0", "W_pri_highmass_mass")] = 300;
  m.y_maxs[make_pair("_cut0", "deltaR_OS_min")] = 300;
  m.y_maxs[make_pair("_cut0", "gamma_star_mass")] = 300;
  m.y_maxs[make_pair("_cut0", "n_jets")] = 1500;
  m.y_maxs[make_pair("_cut0", "z_candidate_mass")] = 300;
  m.y_maxs[make_pair("_cut0", "h_PFMET")] = 300;
  m.y_maxs[make_pair("_cut0", "h_leadingLepton_Pt")] = 300;
  m.y_maxs[make_pair("_cut0", "h_secondLepton_Pt")] = 400;
  m.y_maxs[make_pair("_cut0", "h_thirdLepton_Pt")] = 600;
  m.y_maxs[make_pair("_cut0", "h_leadingLepton_Eta")] = 1000;
  m.y_maxs[make_pair("_cut0", "h_secondLepton_Eta")] = 1000;
  m.y_maxs[make_pair("_cut0", "h_thirdLepton_Eta")] = 1000;
  m.y_maxs[make_pair("_cut0", "h_leadingLepton_LeptonRelIso")] = 2000;
  m.y_maxs[make_pair("_cut0", "h_secondLepton_LeptonRelIso")] = 2000;
  m.y_maxs[make_pair("_cut0", "h_thirdLepton_LeptonRelIso")] = 2000;
  m.y_maxs[make_pair("_cut0", "h_leadingLepton_dXY")] = 200;
  m.y_maxs[make_pair("_cut0", "h_secondLepton_dXY")] = 200;
  m.y_maxs[make_pair("_cut0", "h_thirdLepton_dXY")] = 200;
  m.y_maxs[make_pair("_cut0", "h_leadingLepton_dZ")] = 100;
  m.y_maxs[make_pair("_cut0", "h_secondLepton_dZ")] = 100;
  m.y_maxs[make_pair("_cut0", "h_thirdLepton_dZ")] = 100;
  m.y_maxs[make_pair("_cut0", "h_leadingLepton_GlobalChi2")] = 2000;
  m.y_maxs[make_pair("_cut0", "h_secondLepton_GlobalChi2")] = 2000;
  m.y_maxs[make_pair("_cut0", "h_thirdLepton_GlobalChi2")] = 2000;
  m.y_maxs[make_pair("_cut0", "h_HT")] = 1500;
  m.y_maxs[make_pair("_cut0", "n_events")] = 5000;
  m.y_maxs[make_pair("_cut0", "h_nVertices")] = 300;
  m.y_maxs[make_pair("_cut0", "h_Nbjets")] = 3000;
  m.y_maxs[make_pair("_cutdR", "HN_mass_class1")] = 350;
  m.y_maxs[make_pair("_cutdR", "HN_mass_class2")] = 350;
  m.y_maxs[make_pair("_cutdR", "HN_mass_class3")] = 700;
  m.y_maxs[make_pair("_cutdR", "HN_mass_class4")] = 700;
  m.y_maxs[make_pair("_cutdR", "W_pri_lowmass_mass")] = 300;
  m.y_maxs[make_pair("_cutdR", "W_pri_highmass_mass")] = 500;
  m.y_maxs[make_pair("_cutdR", "deltaR_OS_min")] = 200;
  m.y_maxs[make_pair("_cutdR", "gamma_star_mass")] = 200;
  m.y_maxs[make_pair("_cutdR", "n_jets")] = 1500;
  m.y_maxs[make_pair("_cutdR", "z_candidate_mass")] = 500;
  m.y_maxs[make_pair("_cutdR", "h_PFMET")] = 400;
  m.y_maxs[make_pair("_cutdR", "h_leadingLepton_Pt")] = 400;
  m.y_maxs[make_pair("_cutdR", "h_secondLepton_Pt")] = 400;
  m.y_maxs[make_pair("_cutdR", "h_thirdLepton_Pt")] = 1500;
  m.y_maxs[make_pair("_cutdR", "h_leadingLepton_Eta")] = 1000;
  m.y_maxs[make_pair("_cutdR", "h_secondLepton_Eta")] = 1000;
  m.y_maxs[make_pair("_cutdR", "h_thirdLepton_Eta")] = 1000;
  m.y_maxs[make_pair("_cutdR", "h_leadingLepton_LeptonRelIso")] = 2000;
  m.y_maxs[make_pair("_cutdR", "h_secondLepton_LeptonRelIso")] = 2000;
  m.y_maxs[make_pair("_cutdR", "h_thirdLepton_LeptonRelIso")] = 2000;
  m.y_maxs[make_pair("_cutdR", "h_leadingLepton_dXY")] = 200;
  m.y_maxs[make_pair("_cutdR", "h_secondLepton_dXY")] = 200;
  m.y_maxs[make_pair("_cutdR", "h_thirdLepton_dXY")] = 200;
  m.y_maxs[make_pair("_cutdR", "h_leadingLepton_dZ")] = 100;
  m.y_maxs[make_pair("_cutdR", "h_secondLepton_dZ")] = 100;
  m.y_maxs[make_pair("_cutdR", "h_thirdLepton_dZ")] = 100;
  m.y_maxs[make_pair("_cutdR", "h_leadingLepton_GlobalChi2")] = 2000;
  m.y_maxs[make_pair("_cutdR", "h_secondLepton_GlobalChi2")] = 2000;
  m.y_maxs[make_pair("_cutdR", "h_thirdLepton_GlobalChi2")] = 2000;
  m.y_maxs[make_pair("_cutdR", "h_HT")] = 1000;
  m.y_maxs[make_pair("_cutdR", "n_events")] = 3000;
  m.y_maxs[make_pair("_cutdR", "h_nVertices")] = 300;
  m.y_maxs[make_pair("_cutdR", "h_Nbjets")] = 3000;
  m.y_maxs[make_pair("_cutdR_cutW", "HN_mass_class1")] = 50;
  m.y_maxs[make_pair("_cutdR_cutW", "HN_mass_class2")] = 50;
  m.y_maxs[make_pair("_cutdR_cutW", "W_pri_lowmass_mass")] = 100;
  m.y_maxs[make_pair("_cutdR_cutW", "deltaR_OS_min")] = 15;
  m.y_maxs[make_pair("_cutdR_cutW", "gamma_star_mass")] = 20;
  m.y_maxs[make_pair("_cutdR_cutW", "n_jets")] = 50;
  m.y_maxs[make_pair("_cutdR_cutW", "z_candidate_mass")] = 40;
  m.y_maxs[make_pair("_cutdR_cutW", "h_PFMET")] = 50;
  m.y_maxs[make_pair("_cutdR_cutW", "h_leadingLepton_Pt")] = 100;
  m.y_maxs[make_pair("_cutdR_cutW", "h_secondLepton_Pt")] = 100;
  m.y_maxs[make_pair("_cutdR_cutW", "h_thirdLepton_Pt")] = 100;
  m.y_maxs[make_pair("_cutdR_cutW", "h_leadingLepton_Eta")] = 30;
  m.y_maxs[make_pair("_cutdR_cutW", "h_secondLepton_Eta")] = 30;
  m.y_maxs[make_pair("_cutdR_cutW", "h_thirdLepton_Eta")] = 30;
  m.y_maxs[make_pair("_cutdR_cutW", "h_leadingLepton_LeptonRelIso")] = 100;
  m.y_maxs[make_pair("_cutdR_cutW", "h_secondLepton_LeptonRelIso")] = 100;
  m.y_maxs[make_pair("_cutdR_cutW", "h_thirdLepton_LeptonRelIso")] = 100;
  m.y_maxs[make_pair("_cutdR_cutW", "h_leadingLepton_dXY")] = 50;
  m.y_maxs[make_pair("_cutdR_cutW", "h_secondLepton_dXY")] = 50;
  m.y_maxs[make_pair("_cutdR_cutW", "h_thirdLepton_dXY")] = 50;
  m.y_maxs[make_pair("_cutdR_cutW", "h_leadingLepton_dZ")] = 50;
  m.y_maxs[make_pair("_cutdR_cutW", "h_secondLepton_dZ")] = 50;
  m.y_maxs[make_pair("_cutdR_cutW", "h_thirdLepton_dZ")] = 50;
  m.y_maxs[make_pair("_cutdR_cutW", "h_leadingLepton_GlobalChi2")] = 200;
  m.y_maxs[make_pair("_cutdR_cutW", "h_secondLepton_GlobalChi2")] = 200;
  m.y_maxs[make_pair("_cutdR_cutW", "h_thirdLepton_GlobalChi2")] = 200;
  m.y_maxs[make_pair("_cutdR_cutW", "h_HT")] = 150;
  m.y_maxs[make_pair("_cutdR_cutW", "n_events")] = 300;
  m.y_maxs[make_pair("_cutdR_cutW", "h_nVertices")] = 50;
  m.y_maxs[make_pair("_cutdR_cutW", "h_Nbjets")] = 100;

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
  m.log_of_generation_mixing = 0.;
  
  //==== prepare plot directories
  m.make_plot_directory();
  
  //==== declare output rootfiles
  m.outputfile = new TFile(m.plotpath+"/hists.root", "RECREATE");
  
  //==== finally, draw plots
  m.draw_hist();

}






