#include "trilepton_mumumu.cc"
#include <fstream>

void run_trilepton_mumumu(){
  
  //==== decalre class
  trilepton_mumumu m;
  
  //==== set data class
  m.data_class =
  //"dXY_0p2_dZ_0p5/TTT";
  "dXY_0p01_dZ_0p5/TTT_cluster";
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
  m.map_sample_string_to_list["others"] = {"Wbb", "topDIL", "TTG", "TTWW", "WWG", "WWW", "WWZ", "WZZ", "ZZZ", "ttZ"};
  m.map_sample_string_to_list["Higgs"] = {"HtoWW", "ggHtoZZ"};
  m.map_sample_string_to_list["Higgs_prompt"] = {"ggHtoZZ"};
  m.map_sample_string_to_list["Wgamma"] = {"Wtollln_new"};
  m.map_sample_string_to_list["Vbb"] = {"Wbb", "Zbb"};
  m.map_sample_string_to_list["Wjets"] = {"Wjets"};
  m.map_sample_string_to_list["ttbar"] = {"ttbar"};
  m.map_sample_string_to_list["fake_dijet_topology"] = {"fake_dijet_topology"};
  m.map_sample_string_to_list["fake_MCTruth_ttbar_central"] = {"fake_MCTruth_ttbar_central"};
  m.map_sample_string_to_list["fake_HighdXY"] = {"fake_HighdXY"};
  
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
  
  //==== set and make sample list
  m.samples_to_use =
  //{"DY", "VV", "Higgs", "Wgamma", "Vbb", "Wjets", "others"};
  {"fake_dijet_topology", "VV_prompt", "Higgs_prompt", "Wgamma"};
  //{"fake_HighdXY", "VV_prompt", "Higgs_prompt", "Wgamma"};
  //{"fake_MCTruth_ttbar_central", "VV_prompt", "Higgs_prompt", "Wgamma"};
  //{"fake", "VV", "Higgs", "Wgamma", "Wjets", "ttbar"};
  //{"fake", "VV_prompt", "Wgamma"};
  //{"fake"};
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
    "h_HT"
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
    "H_{T} [GeV]"
  };
  
  //==== set signal mass points
  m.signal_mass = {40, 50, 60, 150, 700};
  m.signal_color = {kRed, kBlack, kBlue, kYellow+3, kViolet};
  
  //==== rebins
  //ofstream skeleton_rebins("./txt/skeleton_rebins.txt", ios::trunc);
  //for(unsigned int i=0; i<m.histname_suffix.size(); i++){
  //  for(unsigned int j=0; j<m.histname.size(); j++){
  //    skeleton_rebins
  //    << "m.rebins[make_pair(\""+m.histname_suffix.at(i)+"\", \""+m.histname.at(j)+"\")] = 1;" << endl;
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
  //    << "m.y_maxs[make_pair(\""+m.histname_suffix.at(i)+"\", \""+m.histname.at(j)+"\")] = 1;" << endl;
  //  }
  //}
  //skeleton_y_maxs.close();
  //return;
  m.default_y_max = 1000;
  m.y_maxs[make_pair("_cut0", "HN_mass_class1")] = 500;
  m.y_maxs[make_pair("_cut0", "HN_mass_class2")] = 500;
  m.y_maxs[make_pair("_cut0", "HN_mass_class3")] = 800;
  m.y_maxs[make_pair("_cut0", "HN_mass_class4")] = 800;
  m.y_maxs[make_pair("_cut0", "W_pri_lowmass_mass")] = 2000;
  m.y_maxs[make_pair("_cut0", "W_pri_highmass_mass")] = 600;
  m.y_maxs[make_pair("_cut0", "deltaR_OS_min")] = 600;
  m.y_maxs[make_pair("_cut0", "gamma_star_mass")] = 600;
  m.y_maxs[make_pair("_cut0", "n_jets")] = 1500;
  m.y_maxs[make_pair("_cut0", "z_candidate_mass")] = 600;
  m.y_maxs[make_pair("_cut0", "h_PFMET")] = 600;
  m.y_maxs[make_pair("_cut0", "h_leadingLepton_Pt")] = 600;
  m.y_maxs[make_pair("_cut0", "h_secondLepton_Pt")] = 2000;
  m.y_maxs[make_pair("_cut0", "h_thirdLepton_Pt")] = 3000;
  m.y_maxs[make_pair("_cut0", "h_leadingLepton_Eta")] = 1000;
  m.y_maxs[make_pair("_cut0", "h_secondLepton_Eta")] = 1000;
  m.y_maxs[make_pair("_cut0", "h_thirdLepton_Eta")] = 1000;
  m.y_maxs[make_pair("_cut0", "h_leadingLepton_LeptonRelIso")] = 2000;
  m.y_maxs[make_pair("_cut0", "h_secondLepton_LeptonRelIso")] = 2000;
  m.y_maxs[make_pair("_cut0", "h_thirdLepton_LeptonRelIso")] = 2000;
  m.y_maxs[make_pair("_cut0", "h_HT")] = 1500;
  m.y_maxs[make_pair("_cutdR", "HN_mass_class1")] = 350;
  m.y_maxs[make_pair("_cutdR", "HN_mass_class2")] = 350;
  m.y_maxs[make_pair("_cutdR", "HN_mass_class3")] = 700;
  m.y_maxs[make_pair("_cutdR", "HN_mass_class4")] = 700;
  m.y_maxs[make_pair("_cutdR", "W_pri_lowmass_mass")] = 600;
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
  m.y_maxs[make_pair("_cutdR", "h_HT")] = 1000;
  m.y_maxs[make_pair("_cutdR_cutW", "HN_mass_class1")] = 100;
  m.y_maxs[make_pair("_cutdR_cutW", "HN_mass_class2")] = 150;
  m.y_maxs[make_pair("_cutdR_cutW", "W_pri_lowmass_mass")] = 200;
  m.y_maxs[make_pair("_cutdR_cutW", "deltaR_OS_min")] = 50;
  m.y_maxs[make_pair("_cutdR_cutW", "gamma_star_mass")] = 60;
  m.y_maxs[make_pair("_cutdR_cutW", "n_jets")] = 120;
  m.y_maxs[make_pair("_cutdR_cutW", "z_candidate_mass")] = 50;
  m.y_maxs[make_pair("_cutdR_cutW", "h_PFMET")] = 80;
  m.y_maxs[make_pair("_cutdR_cutW", "h_leadingLepton_Pt")] = 100;
  m.y_maxs[make_pair("_cutdR_cutW", "h_secondLepton_Pt")] = 100;
  m.y_maxs[make_pair("_cutdR_cutW", "h_thirdLepton_Pt")] = 200;
  m.y_maxs[make_pair("_cutdR_cutW", "h_leadingLepton_Eta")] = 100;
  m.y_maxs[make_pair("_cutdR_cutW", "h_secondLepton_Eta")] = 100;
  m.y_maxs[make_pair("_cutdR_cutW", "h_thirdLepton_Eta")] = 100;
  m.y_maxs[make_pair("_cutdR_cutW", "h_HT")] = 150;

  
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






