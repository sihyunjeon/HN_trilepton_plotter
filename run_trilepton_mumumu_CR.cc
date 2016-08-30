#include "trilepton_mumumu.cc"
#include <fstream>

void run_trilepton_mumumu_CR(int XXX){
  
  //==== decalre class
  trilepton_mumumu m;
  
  //==== set data class
  m.data_class =
  //"dXY_0p01_dZ_0p5/CR";
  "dXY_0p01_dZ_0p5_leadpt_20/CR/";
  
  //==== set prefixes and suffixes
  m.filename_prefix = "trilepton_mumumu_CR_SK";
  m.filename_suffix =
  //"_5_3_14.root";
  "_5_3_20.root";
  
  //==== set sample mapping
  m.map_sample_string_to_list["DY"] = {"DY10to50", "DY50plus"};
  m.map_sample_string_to_list["VV"] = {"WW_mg", "WZtollln_mg", "WZtollqq_mg", "WZtoqqln_mg", "ZZtollll_mg", "ZZtollnn_mg", "ZZtollqq_mg"};
  m.map_sample_string_to_list["VV_2prompt"] = {"WW_mg", "WZtollln_mg", "ZZtollll_mg", "ZZtollnn_mg", "ZZtollqq_mg"};
  m.map_sample_string_to_list["VV_3prompt"] = {"WZtollln_mg", "ZZtollll_mg"};
  m.map_sample_string_to_list["others"] = {"TTWW",  "WWW", "WWZ", "WZZ", "ZZZ", "ttZ"};
  m.map_sample_string_to_list["others_2prompt"] = {"TTWW", "ttW", "WWW", "WWZ", "WZZ", "ZZZ", "ttZ"};
  m.map_sample_string_to_list["others_3prompt"] = {"TTG", "ttW", "TTWW",  "WWW", "WWZ", "WZZ", "ZZZ", "ttZ"};
  m.map_sample_string_to_list["Higgs"] = {"HtoWW", "ggHtoZZ"};
  m.map_sample_string_to_list["Wgamma"] = {"Wtollln_new"};
  m.map_sample_string_to_list["Vbb"] = {"Wbb", "Zbb"};
  m.map_sample_string_to_list["Wjets"] = {"Wjets"};
  m.map_sample_string_to_list["ttbar"] = {"ttbar"};
  m.map_sample_string_to_list["SSWW"] = {"SSWpWp", "SSWmWm"};
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
  
  m.map_sample_string_to_legendinfo["DY"] = make_pair("DY", kAzure-9);
  m.map_sample_string_to_legendinfo["VV"] = make_pair("VV", kGreen);
  m.map_sample_string_to_legendinfo["VV_2prompt"] = make_pair("VV", kGreen);
  m.map_sample_string_to_legendinfo["VV_3prompt"] = make_pair("VV", kGreen);
  m.map_sample_string_to_legendinfo["others"] = make_pair("others", kRed-7);
  m.map_sample_string_to_legendinfo["others_2prompt"] = make_pair("others", kRed-7);
  m.map_sample_string_to_legendinfo["others_3prompt"] = make_pair("others", kRed-7);
  m.map_sample_string_to_legendinfo["Higgs"] = make_pair("Higgs", kYellow);
  m.map_sample_string_to_legendinfo["Wgamma"] = make_pair("W#gamma", kOrange);
  m.map_sample_string_to_legendinfo["Vbb"] = make_pair("V+bb", kRed+3);
  m.map_sample_string_to_legendinfo["Wjets"] = make_pair("Wjets", kGray);
  m.map_sample_string_to_legendinfo["ttbar"] = make_pair("ttbar", kGray);
  m.map_sample_string_to_legendinfo["SSWW"] = make_pair("WpWp/WmWm", kGray);
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
  if(XXX==0) m.samples_to_use = {"others", "Wjets", "Wgamma", "Higgs", "VV", "DY"};
  if(XXX==1){
    m.histname_suffix = {"_SS_0jet_vetoLowRes", "_SS_AL1bjet_vetoLowRes", "_SS_AL2bjet_vetoLowRes"};
    m.samples_to_use = {"others_2prompt", "Wgamma", "Higgs", "VV_2prompt", "SSWW", "fake_HighdXY"};
  }
  if(XXX==2){
    m.histname_suffix = {"_WZ"};
    m.samples_to_use = {"others_3prompt", "Wgamma", "Higgs", "VV_3prompt", "fake_HighdXY"};
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
    "m_Z_candidate",
    "mt_W_candidate"
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
    "onebin",
    "m(Z) [GeV]",
    "m_{T}(W) [GeV]"
  };

  //==== cut-var skips
  for(unsigned int i=0; i<m.histname.size(); i++){
    TString this_var = m.histname.at(i);
    if(this_var.Contains("third")){
      m.CutVarSkips.push_back( make_pair("_SS_0jet_vetoLowRes", this_var) );
      m.CutVarSkips.push_back( make_pair("_SS_AL1bjet_vetoLowRes", this_var) );
      m.CutVarSkips.push_back( make_pair("_SS_AL2bjet_vetoLowRes", this_var) );
    }
  }
  m.CutVarSkips.push_back( make_pair("_SS_0jet_vetoLowRes", "m_Z_candidate") );
  m.CutVarSkips.push_back( make_pair("_SS_0jet_vetoLowRes", "mt_W_candidate") );
  m.CutVarSkips.push_back( make_pair("_SS_AL1bjet_vetoLowRes", "m_Z_candidate") );
  m.CutVarSkips.push_back( make_pair("_SS_AL1bjet_vetoLowRes", "mt_W_candidate") );
  m.CutVarSkips.push_back( make_pair("_SS_AL2bjet_vetoLowRes", "m_Z_candidate") );
  m.CutVarSkips.push_back( make_pair("_SS_AL2bjet_vetoLowRes", "mt_W_candidate") );
  m.CutVarSkips.push_back( make_pair("_WZ", "mll") ); 

  //==== set signal mass points
  m.signal_mass = {40, 50, 60, 150, 700};
  m.signal_color = {kRed, kBlack, kBlue, kYellow+3, kViolet};
  
  //==== set signal coupling constants
  m.coupling_constants[make_pair("_SS_0jet_vetoLowRes", 40)] = 0.01;
  m.coupling_constants[make_pair("_SS_0jet_vetoLowRes", 50)] = 0.01;
  m.coupling_constants[make_pair("_SS_0jet_vetoLowRes", 60)] = 0.01;
  m.coupling_constants[make_pair("_SS_0jet_vetoLowRes", 150)] = 0.01;
  m.coupling_constants[make_pair("_SS_0jet_vetoLowRes", 700)] = 0.01;
  m.coupling_constants[make_pair("_SS_AL1bjet_vetoLowRes", 40)] = 0.1;
  m.coupling_constants[make_pair("_SS_AL1bjet_vetoLowRes", 50)] = 0.1;
  m.coupling_constants[make_pair("_SS_AL1bjet_vetoLowRes", 60)] = 0.1;
  m.coupling_constants[make_pair("_SS_AL1bjet_vetoLowRes", 150)] = 0.1;
  m.coupling_constants[make_pair("_SS_AL1bjet_vetoLowRes", 700)] = 0.1;
  m.coupling_constants[make_pair("_SS_AL2bjet_vetoLowRes", 40)] = 0.1;
  m.coupling_constants[make_pair("_SS_AL2bjet_vetoLowRes", 50)] = 0.1;
  m.coupling_constants[make_pair("_SS_AL2bjet_vetoLowRes", 60)] = 0.1;
  m.coupling_constants[make_pair("_SS_AL2bjet_vetoLowRes", 150)] = 0.1;
  m.coupling_constants[make_pair("_SS_AL2bjet_vetoLowRes", 700)] = 0.1;
  m.coupling_constants[make_pair("_WZ", 40)] = 0.01;
  m.coupling_constants[make_pair("_WZ", 50)] = 0.01;
  m.coupling_constants[make_pair("_WZ", 60)] = 0.01;
  m.coupling_constants[make_pair("_WZ", 150)] = 0.01;
  m.coupling_constants[make_pair("_WZ", 700)] = 0.01;
  
  //==== set signal mass for each class
  m.map_class_to_signal_mass[trilepton_mumumu::class1] = {40, 50};
  m.map_class_to_signal_mass[trilepton_mumumu::class2] = {60};
  m.map_class_to_signal_mass[trilepton_mumumu::lowmass] = {40, 50, 60};
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
  m.rebins[make_pair("_WZ", "m_Z_candidate")] = 5;
  m.rebins[make_pair("_WZ", "mt_W_candidate")] = 5;
  m.rebins[make_pair("_WZ", "PFMET")] = 10;
  
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
  m.default_y_max = 100000;
  m.y_maxs[make_pair("_SS_0jet_vetoLowRes", "leadingLepton_Pt")] = 1000;
  m.y_maxs[make_pair("_SS_0jet_vetoLowRes", "leadingLepton_Eta")] = 1000;
  m.y_maxs[make_pair("_SS_0jet_vetoLowRes", "leadingLepton_Chi2")] = 1000;
  m.y_maxs[make_pair("_SS_0jet_vetoLowRes", "leadingLepton_RelIso")] = 2000;
  m.y_maxs[make_pair("_SS_0jet_vetoLowRes", "secondLepton_Pt")] = 1500;
  m.y_maxs[make_pair("_SS_0jet_vetoLowRes", "secondLepton_Eta")] = 1000;
  m.y_maxs[make_pair("_SS_0jet_vetoLowRes", "secondLepton_Chi2")] = 1000;
  m.y_maxs[make_pair("_SS_0jet_vetoLowRes", "secondLepton_RelIso")] = 2000;
  m.y_maxs[make_pair("_SS_0jet_vetoLowRes", "mll")] = 1000;
  m.y_maxs[make_pair("_SS_0jet_vetoLowRes", "n_events")] = 3000;
  m.y_maxs[make_pair("_SS_0jet_vetoLowRes", "PFMET")] = 1000;
  m.y_maxs[make_pair("_SS_0jet_vetoLowRes", "n_bjets")] = 3000;
  m.y_maxs[make_pair("_SS_AL1bjet_vetoLowRes", "leadingLepton_Pt")] = 300;
  m.y_maxs[make_pair("_SS_AL1bjet_vetoLowRes", "leadingLepton_Eta")] = 300;
  m.y_maxs[make_pair("_SS_AL1bjet_vetoLowRes", "leadingLepton_Chi2")] = 300;
  m.y_maxs[make_pair("_SS_AL1bjet_vetoLowRes", "leadingLepton_RelIso")] = 600;
  m.y_maxs[make_pair("_SS_AL1bjet_vetoLowRes", "secondLepton_Pt")] = 500;
  m.y_maxs[make_pair("_SS_AL1bjet_vetoLowRes", "secondLepton_Eta")] = 300;
  m.y_maxs[make_pair("_SS_AL1bjet_vetoLowRes", "secondLepton_Chi2")] = 300;
  m.y_maxs[make_pair("_SS_AL1bjet_vetoLowRes", "secondLepton_RelIso")] = 600;
  m.y_maxs[make_pair("_SS_AL1bjet_vetoLowRes", "mll")] = 200;
  m.y_maxs[make_pair("_SS_AL1bjet_vetoLowRes", "n_events")] = 2000;
  m.y_maxs[make_pair("_SS_AL1bjet_vetoLowRes", "PFMET")] = 300;
  m.y_maxs[make_pair("_SS_AL1bjet_vetoLowRes", "n_bjets")] = 1500;
  m.y_maxs[make_pair("_WZ", "leadingLepton_Pt")] = 200;
  m.y_maxs[make_pair("_WZ", "leadingLepton_Eta")] = 200;
  m.y_maxs[make_pair("_WZ", "leadingLepton_Chi2")] = 200;
  m.y_maxs[make_pair("_WZ", "leadingLepton_RelIso")] = 500;
  m.y_maxs[make_pair("_WZ", "secondLepton_Pt")] = 200;
  m.y_maxs[make_pair("_WZ", "secondLepton_Eta")] = 200;
  m.y_maxs[make_pair("_WZ", "secondLepton_Chi2")] = 200;
  m.y_maxs[make_pair("_WZ", "secondLepton_RelIso")] = 500;
  m.y_maxs[make_pair("_WZ", "thirdLepton_Pt")] = 200;
  m.y_maxs[make_pair("_WZ", "thirdLepton_Eta")] = 200;
  m.y_maxs[make_pair("_WZ", "thirdLepton_Chi2")] = 200;
  m.y_maxs[make_pair("_WZ", "thirdLepton_RelIso")] = 500;
  m.y_maxs[make_pair("_WZ", "m_Z_candidate")] = 500;
  m.y_maxs[make_pair("_WZ", "mt_W_candidate")] = 100;
  m.y_maxs[make_pair("_WZ", "n_events")] = 1500;
  m.y_maxs[make_pair("_WZ", "PFMET")] = 300;
  m.y_maxs[make_pair("_WZ", "n_bjets")] = 1000;
  
  
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
  m.x_maxs[make_pair("_WZ", "PFMET")] = 200.;
  
  //==== k-factor
  m.k_factor = 1.34;
  
  //==== mixing at generation level
  m.log_of_generation_mixing = 0.;
  
  //==== prepare plot directories
  m.make_plot_directory();
  
  //==== declare output rootfiles
  m.outputfile = new TFile(m.plotpath+"/hists.root", "RECREATE");
  
  //==== draw in logy
  m.UseSetLogy = false;
  
  //==== finally, draw plots
  m.draw_hist();
  
}






