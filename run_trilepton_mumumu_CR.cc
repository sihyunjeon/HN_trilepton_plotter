#include "trilepton_mumumu.cc"
#include <fstream>

void run_trilepton_mumumu_CR(){
  
  //==== decalre class
  trilepton_mumumu m;
  
  //==== set data class
  m.data_class =
  //"dXY_0p01_dZ_0p5/CR";
  "dXY_0p01_dZ_0p5_leadpt_20/CR2";
  
  //==== set prefixes and suffixes
  m.filename_prefix = "trilepton_mumumu_CR_SK";
  m.filename_suffix =
  //"_5_3_14.root";
  "_5_3_20.root";
  m.histname_suffix = {"_control"};
  
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
  m.map_sample_string_to_list["fake_DiMuon_HighdXY"] = {"fake_DiMuon_HighdXY"};
  m.map_sample_string_to_list["fake_DiMuon_HighdXY_n_jets"] = {"fake_DiMuon_HighdXY_n_jets"};
  
  m.map_sample_string_to_legendinfo["DY"] = make_pair("DY", kAzure-9);
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
  
  //==== set and make sample list
  m.samples_to_use =
  {"DY", "VV", "Higgs", "Wgamma", "Vbb", "Wjets", "others"};
  //{"fake_dijet_topology", "VV_prompt", "Higgs_prompt", "Wgamma"};
  //{"fake_HighdXY", "VV_prompt", "Higgs_prompt", "Wgamma"};
  //{"fake_DiMuon_HighdXY", "VV_prompt", "Higgs_prompt", "Wgamma"};
  //{"fake_DiMuon_HighdXY_n_jets", "VV_prompt", "Higgs_prompt", "Wgamma"};
  //{"fake_MCTruth_ttbar_central", "VV_prompt", "Higgs_prompt", "Wgamma"};
  //{"fake", "VV", "Higgs", "Wgamma", "Wjets", "ttbar"};
  //{"fake", "VV_prompt", "Wgamma"};
  //{"fake"};
  m.make_bkglist();
  
  //==== set variables to draw
  m.histname = {
    "n_loose_muons",
    "n_tight_muons",
    "n_jets",
    "n_bjets",
    "TT_leadingLepton_Pt",
    "TT_secondLepton_Pt",
    "TT_leadingLepton_Eta",
    "TT_secondLepton_Eta",
    "TT_leadingLepton_RelIso",
    "TT_secondLepton_RelIso",
    "TT_leadingLepton_Chi2",
    "TT_secondLepton_Chi2",
    "TT_mll",
    "TT_n_events"
  };
  m.x_title = {
    "onebin",
    "onebin",
    "onebin",
    "onebin",
    "p_{T} [GeV]",
    "p_{T} [GeV]",
    "|#eta|",
    "|#eta|",
    "LeptonRelIso",
    "LeptonRelIso",
    "GlobalChi2",
    "GlobalChi2",
    "m(#mu#mu) [GeV]",
    "onebin"
  };
  
  //==== set signal mass points
  m.signal_mass = {40, 50, 60, 150, 700};
  m.signal_color = {kRed, kBlack, kBlue, kYellow+3, kViolet};
  
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
  m.rebins[make_pair("_control", "TT_leadingLepton_Pt")] = 5;
  m.rebins[make_pair("_control", "TT_leadingLepton_Eta")] = 5;
  m.rebins[make_pair("_control", "TT_secondLepton_Pt")] = 5;
  m.rebins[make_pair("_control", "TT_secondLepton_Eta")] = 5;
  m.rebins[make_pair("_control", "TT_mll")] = 10;
  
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
  m.default_y_max = 100000000;
  
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

  //==== k-factor
  m.k_factor = 1.34;
  
  //==== mixing at generation level
  m.log_of_generation_mixing = 0.;
  
  //==== prepare plot directories
  m.make_plot_directory();
  
  //==== declare output rootfiles
  m.outputfile = new TFile(m.plotpath+"/hists.root", "RECREATE");
  
  //==== draw in logy
  m.UseSetLogy = true;
  
  //==== finally, draw plots
  m.draw_hist();
  
}






