#include "trilepton_mumumu.cc"
#include <fstream>

void run_trilepton_mumumu_CR_2015(int XXX){
  
  //==== decalre class
  trilepton_mumumu m;
  
  //==== set data class
  m.data_class =
  "v7-6-6.2/CR";
  
  //==== set prefixes and suffixes
  m.filename_prefix = "trilepton_mumumu_CR";
  m.filename_suffix =
  "_cat_v7-6-6.root";
  
  //==== set sample mapping
  m.map_sample_string_to_list["DY_MCatNLO"] = {"DY10to50_MCatNLO", "DY50plus_MCatNLO"};
  m.map_sample_string_to_list["DY_madgraph"] = {"DY50plus_madgraph"};
  m.map_sample_string_to_list["WJets_MCatNLO"] = {"WJets_MCatNLO"};
  m.map_sample_string_to_list["VV_excl_MCatNLO"] = {"WZ_lllnu_MCatNLO", "WZ_llqq_MCatNLO", "ZZ_llqq_MCatNLO", "ZZ_llll_MCatNLO"};
  m.map_sample_string_to_list["VV_excl"] = {"WZ_lllnu_powheg", "WW_llnn_powheg", "ZZ_llnunu_powheg", "ZZ_llll_powheg"};
  m.map_sample_string_to_list["VV_incl"] = {"WZ_pythia8", "WW_pythia8", "ZZ_pythia8"};
  m.map_sample_string_to_list["VV_2prompt"] = {"WZ_lllnu_MCatNLO", "WZ_llqq_MCatNLO", "ZZ_llqq_MCatNLO", "ZZ_llll_MCatNLO"};
  m.map_sample_string_to_list["VV_3prompt_MCatNLO"] = {"WZ_lllnu_MCatNLO", "ZZ_llll_MCatNLO"};
  m.map_sample_string_to_list["VV_3prompt_powheg"] = {"WZ_lllnu_powheg", "ZZ_llll_powheg"};
  m.map_sample_string_to_list["WZ"] = {"WZ_lllnu_powheg"};
  m.map_sample_string_to_list["ZZ"] = {"ZZ_llll_MCatNLO"};
  m.map_sample_string_to_list["VVV_MCatNLO"] = {"WZZ_MCatNLO", "WWZ_MCatNLO", "ZZZ_MCatNLO"};
  m.map_sample_string_to_list["t"] = {"singletop_s_MCatNLO", "singletop_tbar_Powheg", "singletop_t_Powheg", "singletop_tbarW_Powheg", "singletop_tW_Powheg"};
  m.map_sample_string_to_list["ttbar"] = {"TT_MCatNLO"};
  m.map_sample_string_to_list["DoubleW"] = {"WW_doublescattering"};
  m.map_sample_string_to_list["ttV"] = {"ttWJetsToLNu_MCatNLO", "ttZToLLNuNu_MCatNLO", "TTG_MCatNLO"};
  m.map_sample_string_to_list["ttH"] = {"ttHnobb_Powheg"};
  m.map_sample_string_to_list["Wgamma"] = {"WG_lnuG_madgraph"};
  m.map_sample_string_to_list["Zgamma"] = {"ZG_llG_MCatNLO"};
  m.map_sample_string_to_list["others"] = {"WZZ_MCatNLO", "ttWJetsToLNu_MCatNLO"};
  m.map_sample_string_to_list["fake_HighdXY"] = {"fake_HighdXY"};
  m.map_sample_string_to_list["fake_sfed_HighdXY"] = {"fake_sfed_HighdXY"};
  m.map_sample_string_to_list["fake_pt_sfed_HighdXY"] = {"fake_pt_sfed_HighdXY"};
  m.map_sample_string_to_list["fake_DiMuon_HighdXY"] = {"fake_HighdXY"};
  
  m.map_sample_string_to_legendinfo["DY_MCatNLO"] = make_pair("DY", kAzure+8);
  m.map_sample_string_to_legendinfo["DY_madgraph"] = make_pair("DY", kAzure+8);
  m.map_sample_string_to_legendinfo["WJets_MCatNLO"] = make_pair("WJets", kOrange);
  m.map_sample_string_to_legendinfo["VV_excl_MCatNLO"] = make_pair("VV", kGreen);
  m.map_sample_string_to_legendinfo["VV_excl"] = make_pair("VV", kGreen);
  m.map_sample_string_to_legendinfo["VV_incl"] = make_pair("VV", kGreen);
  m.map_sample_string_to_legendinfo["VV_2prompt"] = make_pair("VV", kGreen);
  m.map_sample_string_to_legendinfo["VV_3prompt_MCatNLO"] = make_pair("VV", kGreen);
  m.map_sample_string_to_legendinfo["VV_3prompt_powheg"] = make_pair("VV", kGreen);
  m.map_sample_string_to_legendinfo["WZ"] = make_pair("WZ", kGreen);
  m.map_sample_string_to_legendinfo["ZZ"] = make_pair("ZZ", kRed-7);
  m.map_sample_string_to_legendinfo["VVV_MCatNLO"] = make_pair("VVV", kOrange-7);
  m.map_sample_string_to_legendinfo["t"] = make_pair("top", kRed);
  m.map_sample_string_to_legendinfo["ttbar"] = make_pair("ttbar", kRed);
  m.map_sample_string_to_legendinfo["DoubleW"] = make_pair("DoubleW", kGray);
  m.map_sample_string_to_legendinfo["ttV"] = make_pair("ttV", kCyan+3);
  m.map_sample_string_to_legendinfo["ttH"] = make_pair("ttH", kViolet);
  m.map_sample_string_to_legendinfo["Wgamma"] = make_pair("W#gamma", kOrange);
  m.map_sample_string_to_legendinfo["Zgamma"] = make_pair("Z#gamma", kOrange);
  m.map_sample_string_to_legendinfo["others"] = make_pair("others", kGray);
  m.map_sample_string_to_legendinfo["fake_HighdXY"] = make_pair("Misd", kAzure+8);
  m.map_sample_string_to_legendinfo["fake_sfed_HighdXY"] = make_pair("Misd", kAzure+8);
  m.map_sample_string_to_legendinfo["fake_pt_sfed_HighdXY"] = make_pair("Misd", kAzure+8);
  m.map_sample_string_to_legendinfo["fake_DiMuon_HighdXY"] = make_pair("Misd", kAzure+8);
  
  //==== set and make sample list
  if(XXX==0) m.samples_to_use = {"DY_MCatNLO", "WJets_MCatNLO", "VV_excl_MCatNLO", "t", "ttbar", "DoubleW"};
  if(XXX==1) m.samples_to_use = {"DY_MCatNLO", "WJets_MCatNLO", "VV_excl", "t"};
  if(XXX==2){
    m.histname_suffix = {"_SS_0jet_vetoLowRes", "_SS_AL1bjet_vetoLowRes", "_SS_AL2bjet_vetoLowRes"};
    m.samples_to_use = {"fake_HighdXY", "VV_2prompt", "DoubleW", "Wgamma", "VVV", "ttV", "ttH"};
  }
  if(XXX==3){
    m.histname_suffix = {"_WZ"};
    //m.samples_to_use = {"fake_HighdXY", "VV_3prompt_powheg", "Zgamma", "VVV", "ttV", "ttH"};
    m.samples_to_use = {"fake_HighdXY", "WZ", "ZZ", "Wgamma", "VVV", "ttV", "ttH"};
  }
  if(XXX==4){
    m.histname_suffix = {"_SS_0jet_vetoLowRes", "_SS_AL1bjet_vetoLowRes", "_SS_AL2bjet_vetoLowRes"};
    m.samples_to_use = {"fake_sfed_HighdXY", "VV_2prompt", "DoubleW", "Wgamma", "VVV", "ttV", "ttH"};
  }
  if(XXX==5){
    m.histname_suffix = {"_WZ"};
    //m.samples_to_use = {"fake_sfed_HighdXY", "VV_3prompt_powheg", "Zgamma", "VVV", "ttV", "ttH"};
    m.samples_to_use = {"fake_sfed_HighdXY", "WZ", "ZZ", "Wgamma", "VVV", "ttV", "ttH"};
  }
  if(XXX==6){
    m.histname_suffix = {"_SS_0jet_vetoLowRes", "_SS_AL1bjet_vetoLowRes", "_SS_AL2bjet_vetoLowRes"};
    m.samples_to_use = {"fake_pt_sfed_HighdXY", "VV_2prompt", "DoubleW", "Wgamma", "VVV", "ttV", "ttH"};
  }
  if(XXX==7){
    m.histname_suffix = {"_WZ"};
    //m.samples_to_use = {"fake_sfed_HighdXY", "VV_3prompt_powheg", "Zgamma", "VVV", "ttV", "ttH"};
    m.samples_to_use = {"fake_pt_sfed_HighdXY", "WZ", "ZZ", "Wgamma", "VVV", "ttV", "ttH"};
  }
  
  m.make_bkglist();

  
  //==== set variables to draw
  m.histname = {
    "leadingLepton_Pt",
    "leadingLepton_Eta",
    "leadingLepton_RelIso",
    "leadingLepton_Chi2",
    "secondLepton_Pt",
    "secondLepton_Eta",
    "secondLepton_RelIso",
    "secondLepton_Chi2",
    "thirdLepton_Pt",
    "thirdLepton_Eta",
    "thirdLepton_RelIso",
    "thirdLepton_Chi2",
    "mll",
    "n_events",
    "PFMET",
    "n_bjets",
    "m_Z_candidate_before_cut",
    "m_lll_before_cut",
    "PFMET_before_cut",
    "n_electrons_before_cut",
    "n_bjets_before_cut",
    "m_Z_candidate",
    "mt_W_candidate",
    "osllmass",
    "m_lll",
    "WMuon_Pt",
    "Z_candidate_Pt",
    "W_candidate_Pt",
    "dRZMuonWMuon",
    "N1_Z_mass",
    "N1_mlll",
    "N1_n_bjets",
    "N1_PFMET",
    "n_vertices_before_cut",
    "n_vertices"
  };

  m.x_title = {
    "p_{T} [GeV]",
    "|#eta|",
    "LeptonRelIso",
    "GlobalChi2",
    "p_{T} [GeV]",
    "|#eta|",
    "LeptonRelIso",
    "GlobalChi2",
    "p_{T} [GeV]",
    "|#eta|",
    "LeptonRelIso",
    "GlobalChi2",
    "m(#mu#mu) [GeV]",
    "onebin",
    "PFMET [GeV]",
    "# of b-tagged jets",
    "m(Z) [GeV]",
    "m(lll) [GeV]",
    "PFMET [GeV]",
    "# of electrons",
    "# of bjets",
    "m(Z) [GeV]",
    "m_{T}(W) [GeV]",
    "m(OS) [GeV]",
    "m(lll) [GeV]",
    "p_{T}^{W Lepton} [GeV]",
    "p_{T}^{Z} [GeV]",
    "p_{T}^{W} [GeV]",
    "#DeltaR(#mu^{W Lepton}#mu^{Z Leptons})",
    "|m(ll)-m(Z)| [GeV]",
    "m(lll) [GeV]",
    "# of bjets",
    "PFMET [GeV]",
    "# of vertices",
    "# of vertices"
  };

  //==== cut-var skips
  for(unsigned int i=0; i<m.histname.size(); i++){
    TString this_var = m.histname.at(i);
    if(this_var.Contains("third") ||
       this_var == "m_Z_candidate_before_cut" ||
       this_var == "m_lll_before_cut" ||
       this_var == "PFMET_before_cut" ||
       this_var == "n_electrons_before_cut" ||
       this_var == "n_bjets_before_cut" ||
       this_var == "m_Z_candidate" ||
       this_var == "mt_W_candidate" ||
       this_var == "osllmass" ||
       this_var == "m_lll" ||
       this_var == "WMuon_Pt" ||
       this_var == "Z_candidate_Pt" ||
       this_var == "W_candidate_Pt" ||
       this_var == "dRZMuonWMuon" ||
       this_var == "N1_Z_mass" ||
       this_var == "N1_mlll" ||
       this_var == "N1_n_bjets" ||
       this_var == "N1_PFMET" ||
       this_var == "n_vertices_before_cut" ||
       this_var == "n_vertices"
      ){
      m.CutVarSkips.push_back( make_pair("_SS_0jet_vetoLowRes", this_var) );
      m.CutVarSkips.push_back( make_pair("_SS_AL1bjet_vetoLowRes", this_var) );
      m.CutVarSkips.push_back( make_pair("_SS_AL2bjet_vetoLowRes", this_var) );
    }
  }
  m.CutVarSkips.push_back( make_pair("_WZ", "mll") );
 
  //==== set signal mass points
  m.signal_mass = {40, 60, 150, 700};
  m.signal_color = {kRed, kBlack, kBlue, kYellow+3, kViolet};
  
  //==== set signal coupling constants
  m.coupling_constants[make_pair("_SS_0jet_vetoLowRes", 40)] = 0.1;
  m.coupling_constants[make_pair("_SS_0jet_vetoLowRes", 60)] = 0.1;
  m.coupling_constants[make_pair("_SS_0jet_vetoLowRes", 150)] = 0.1;
  m.coupling_constants[make_pair("_SS_0jet_vetoLowRes", 700)] = 0.1;
  m.coupling_constants[make_pair("_SS_AL1bjet_vetoLowRes", 40)] = 0.1;
  m.coupling_constants[make_pair("_SS_AL1bjet_vetoLowRes", 60)] = 0.1;
  m.coupling_constants[make_pair("_SS_AL1bjet_vetoLowRes", 150)] = 0.1;
  m.coupling_constants[make_pair("_SS_AL1bjet_vetoLowRes", 700)] = 0.1;
  m.coupling_constants[make_pair("_SS_AL2bjet_vetoLowRes", 40)] = 0.1;
  m.coupling_constants[make_pair("_SS_AL2bjet_vetoLowRes", 60)] = 0.1;
  m.coupling_constants[make_pair("_SS_AL2bjet_vetoLowRes", 150)] = 0.1;
  m.coupling_constants[make_pair("_SS_AL2bjet_vetoLowRes", 700)] = 0.1;
  m.coupling_constants[make_pair("_WZ", 40)] = 100.;
  m.coupling_constants[make_pair("_WZ", 60)] = 1.;
  m.coupling_constants[make_pair("_WZ", 150)] = 100.;
  m.coupling_constants[make_pair("_WZ", 700)] = 100.;
  
  //==== set signal mass for each class
  m.map_class_to_signal_mass[trilepton_mumumu::class1] = {40};
  m.map_class_to_signal_mass[trilepton_mumumu::class2] = {60};
  m.map_class_to_signal_mass[trilepton_mumumu::lowmass] = {40, 60};
  m.map_class_to_signal_mass[trilepton_mumumu::class3] = {150};
  m.map_class_to_signal_mass[trilepton_mumumu::class4] = {700};
  m.map_class_to_signal_mass[trilepton_mumumu::highmass] = {150, 700};
  
  //==== rebins
  //ofstream skeleton_rebins("./txt/CR_skeleton_rebins.txt", ios::trunc);
  //for(unsigned int i=0; i<m.histname_suffix.size(); i++){
  //  for(unsigned int j=0; j<m.histname.size(); j++){
  //    skeleton_rebins
  //    << "m.rebins[make_pair(\""+m.histname_suffix.at(i)+"\", \""+m.histname.at(j)+"\")] = 1;" << endl;
  //  }
  //}
  //skeleton_rebins.close();
  //return;
  m.rebins[make_pair("_SS_0jet_vetoLowRes", "leadingLepton_Pt")] = 5;
  m.rebins[make_pair("_SS_0jet_vetoLowRes", "leadingLepton_Eta")] = 5;
  m.rebins[make_pair("_SS_0jet_vetoLowRes", "secondLepton_Pt")] = 5;
  m.rebins[make_pair("_SS_0jet_vetoLowRes", "secondLepton_Eta")] = 5;
  m.rebins[make_pair("_SS_0jet_vetoLowRes", "mll")] = 5;
  m.rebins[make_pair("_SS_0jet_vetoLowRes", "PFMET")] = 10;
  m.rebins[make_pair("_SS_AL1bjet_vetoLowRes", "leadingLepton_Pt")] = 5;
  m.rebins[make_pair("_SS_AL1bjet_vetoLowRes", "leadingLepton_Eta")] = 5;
  m.rebins[make_pair("_SS_AL1bjet_vetoLowRes", "secondLepton_Pt")] = 5;
  m.rebins[make_pair("_SS_AL1bjet_vetoLowRes", "secondLepton_Eta")] = 5;
  m.rebins[make_pair("_SS_AL1bjet_vetoLowRes", "mll")] = 5;
  m.rebins[make_pair("_SS_AL1bjet_vetoLowRes", "PFMET")] = 10;
  m.rebins[make_pair("_SS_AL2bjet_vetoLowRes", "leadingLepton_Pt")] = 5;
  m.rebins[make_pair("_SS_AL2bjet_vetoLowRes", "leadingLepton_Eta")] = 5;
  m.rebins[make_pair("_SS_AL2bjet_vetoLowRes", "secondLepton_Pt")] = 5;
  m.rebins[make_pair("_SS_AL2bjet_vetoLowRes", "secondLepton_Eta")] = 5;
  m.rebins[make_pair("_SS_AL2bjet_vetoLowRes", "mll")] = 5;
  m.rebins[make_pair("_SS_AL2bjet_vetoLowRes", "PFMET")] = 10;
  m.rebins[make_pair("_WZ", "leadingLepton_Pt")] = 5;
  m.rebins[make_pair("_WZ", "leadingLepton_Eta")] = 5;
  m.rebins[make_pair("_WZ", "secondLepton_Pt")] = 5;
  m.rebins[make_pair("_WZ", "secondLepton_Eta")] = 5;
  m.rebins[make_pair("_WZ", "thirdLepton_Pt")] = 5;
  m.rebins[make_pair("_WZ", "thirdLepton_Eta")] = 5;
  m.rebins[make_pair("_WZ", "PFMET")] = 10;
  m.rebins[make_pair("_WZ", "m_Z_candidate_before_cut")] = 5;
  m.rebins[make_pair("_WZ", "m_lll_before_cut")] = 20;
  m.rebins[make_pair("_WZ", "PFMET_before_cut")] = 10;
  m.rebins[make_pair("_WZ", "m_Z_candidate")] = 5;
  m.rebins[make_pair("_WZ", "mt_W_candidate")] = 10;
  m.rebins[make_pair("_WZ", "osllmass")] = 5;
  m.rebins[make_pair("_WZ", "m_lll")] = 20;
  m.rebins[make_pair("_WZ", "WMuon_Pt")] = 10;
  m.rebins[make_pair("_WZ", "Z_candidate_Pt")] = 20;
  m.rebins[make_pair("_WZ", "W_candidate_Pt")] = 20;


  //==== y_maxs
  //ofstream skeleton_y_maxs("./txt/CR_skeleton_y_maxs.txt", ios::trunc);
  //for(unsigned int i=0; i<m.histname_suffix.size(); i++){
  //  for(unsigned int j=0; j<m.histname.size(); j++){
  //    skeleton_y_maxs
  //    << "  m.y_maxs[make_pair(\""+m.histname_suffix.at(i)+"\", \""+m.histname.at(j)+"\")] = 1;" << endl;
  //  }
  //}
  //skeleton_y_maxs.close();
  //return;
  m.default_y_max = 50;
  m.y_maxs[make_pair("_SS_0jet_vetoLowRes", "leadingLepton_Pt")] = 150;
  m.y_maxs[make_pair("_SS_0jet_vetoLowRes", "leadingLepton_Eta")] = 100;
  m.y_maxs[make_pair("_SS_0jet_vetoLowRes", "leadingLepton_Chi2")] = 100;
  m.y_maxs[make_pair("_SS_0jet_vetoLowRes", "leadingLepton_RelIso")] = 100;
  m.y_maxs[make_pair("_SS_0jet_vetoLowRes", "secondLepton_Pt")] = 150;
  m.y_maxs[make_pair("_SS_0jet_vetoLowRes", "secondLepton_Eta")] = 100;
  m.y_maxs[make_pair("_SS_0jet_vetoLowRes", "secondLepton_Chi2")] = 100;
  m.y_maxs[make_pair("_SS_0jet_vetoLowRes", "secondLepton_RelIso")] = 100;
  m.y_maxs[make_pair("_SS_0jet_vetoLowRes", "mll")] = 50;
  m.y_maxs[make_pair("_SS_0jet_vetoLowRes", "n_events")] = 500;
  m.y_maxs[make_pair("_SS_0jet_vetoLowRes", "PFMET")] = 100;
  m.y_maxs[make_pair("_SS_0jet_vetoLowRes", "n_bjets")] = 500;
  m.y_maxs[make_pair("_SS_AL1bjet_vetoLowRes", "leadingLepton_Pt")] = 20;
  m.y_maxs[make_pair("_SS_AL1bjet_vetoLowRes", "leadingLepton_Eta")] = 30;
  m.y_maxs[make_pair("_SS_AL1bjet_vetoLowRes", "leadingLepton_Chi2")] = 30;
  m.y_maxs[make_pair("_SS_AL1bjet_vetoLowRes", "leadingLepton_RelIso")] = 50;
  m.y_maxs[make_pair("_SS_AL1bjet_vetoLowRes", "secondLepton_Pt")] = 50;
  m.y_maxs[make_pair("_SS_AL1bjet_vetoLowRes", "secondLepton_Eta")] = 30;
  m.y_maxs[make_pair("_SS_AL1bjet_vetoLowRes", "secondLepton_Chi2")] = 30;
  m.y_maxs[make_pair("_SS_AL1bjet_vetoLowRes", "secondLepton_RelIso")] = 30;
  m.y_maxs[make_pair("_SS_AL1bjet_vetoLowRes", "mll")] = 20;
  m.y_maxs[make_pair("_SS_AL1bjet_vetoLowRes", "n_events")] = 100;
  m.y_maxs[make_pair("_SS_AL1bjet_vetoLowRes", "PFMET")] = 30;
  m.y_maxs[make_pair("_SS_AL1bjet_vetoLowRes", "n_bjets")] = 100;
  m.y_maxs[make_pair("_WZ", "leadingLepton_Pt")] = 20;
  m.y_maxs[make_pair("_WZ", "leadingLepton_Eta")] = 50;
  m.y_maxs[make_pair("_WZ", "leadingLepton_Chi2")] = 30;
  m.y_maxs[make_pair("_WZ", "leadingLepton_RelIso")] = 100;
  m.y_maxs[make_pair("_WZ", "secondLepton_Pt")] = 50;
  m.y_maxs[make_pair("_WZ", "secondLepton_Eta")] = 50;
  m.y_maxs[make_pair("_WZ", "secondLepton_Chi2")] = 30;
  m.y_maxs[make_pair("_WZ", "secondLepton_RelIso")] = 100;
  m.y_maxs[make_pair("_WZ", "thirdLepton_Pt")] = 50;
  m.y_maxs[make_pair("_WZ", "thirdLepton_Eta")] = 50;
  m.y_maxs[make_pair("_WZ", "thirdLepton_Chi2")] = 30;
  m.y_maxs[make_pair("_WZ", "thirdLepton_RelIso")] = 100;
  m.y_maxs[make_pair("_WZ", "n_events")] = 300;
  m.y_maxs[make_pair("_WZ", "PFMET")] = 50;
  m.y_maxs[make_pair("_WZ", "n_bjets")] = 300;
  m.y_maxs[make_pair("_WZ", "m_Z_candidate_before_cut")] = 150;
  m.y_maxs[make_pair("_WZ", "m_lll_before_cut")] = 80;
  m.y_maxs[make_pair("_WZ", "PFMET_before_cut")] = 100;
  m.y_maxs[make_pair("_WZ", "n_electrons_before_cut")] = 400;
  m.y_maxs[make_pair("_WZ", "n_bjets_before_cut")] = 400;
  m.y_maxs[make_pair("_WZ", "m_Z_candidate")] = 80;
  m.y_maxs[make_pair("_WZ", "mt_W_candidate")] = 20;
  m.y_maxs[make_pair("_WZ", "osllmass")] = 150;
  m.y_maxs[make_pair("_WZ", "m_lll")] = 30;
  m.y_maxs[make_pair("_WZ", "WMuon_Pt")] = 40;
  m.y_maxs[make_pair("_WZ", "Z_candidate_Pt")] = 40;
  m.y_maxs[make_pair("_WZ", "W_candidate_Pt")] = 40;
  m.y_maxs[make_pair("_WZ", "N1_Z_mass")] = 40;
  m.y_maxs[make_pair("_WZ", "N1_mlll")] = 40;
  m.y_maxs[make_pair("_WZ", "N1_n_bjets")] = 100;
  m.y_maxs[make_pair("_WZ", "N1_PFMET")] = 40;
  m.y_maxs[make_pair("_WZ", "n_vertices_before_cut")] = 100;
  m.y_maxs[make_pair("_WZ", "n_vertices")] = 40;


  //==== x_mins
  //ofstream skeleton_x_mins("./txt/CR_skeleton_x_mins.txt", ios::trunc);
  //for(unsigned int i=0; i<m.histname_suffix.size(); i++){
  //  for(unsigned int j=0; j<m.histname.size(); j++){
  //    skeleton_x_mins
  //    << "  m.x_mins[make_pair(\""+m.histname_suffix.at(i)+"\", \""+m.histname.at(j)+"\")] = 1;" << endl;
  //  }
  //}
  //skeleton_x_mins.close();
  //return;
  m.x_maxs[make_pair("_SS_0jet_vetoLowRes", "mll")] = 200.;
  m.x_maxs[make_pair("_SS_0jet_vetoLowRes", "PFMET")] = 200.;
  m.x_maxs[make_pair("_SS_AL1bjet_vetoLowRes", "mll")] = 200.;
  m.x_maxs[make_pair("_SS_AL1bjet_vetoLowRes", "PFMET")] = 200.;
  m.x_maxs[make_pair("_SS_AL2bjet_vetoLowRes", "mll")] = 200.;
  m.x_maxs[make_pair("_SS_AL2bjet_vetoLowRes", "PFMET")] = 200.;
  m.x_maxs[make_pair("_WZ", "mll")] = 200.;
  m.x_maxs[make_pair("_WZ", "PFMET_before_cut")] = 200.;
  m.x_maxs[make_pair("_WZ", "PFMET")] = 200.;
  m.x_maxs[make_pair("_WZ", "osllmass")] = 150.;
  
  //==== k-factor
  m.k_factor = 1.34;
  
  //==== mixing at generation level
  m.log_of_generation_mixing = -2.;
  
  //==== prepare plot directories
  m.make_plot_directory();
  
  //==== declare output rootfiles
  m.outputfile = new TFile(m.plotpath+"/hists.root", "RECREATE");
  
  //==== draw in logy
  m.UseSetLogy = false;
  
  //==== finally, draw plots
  m.draw_hist();
  
}






