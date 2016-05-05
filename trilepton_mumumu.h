#ifndef trilepton_mumumu_h
#define trilepton_mumumu_h

#include "TSystem.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TString.h"
#include "THStack.h"
#include "TLegend.h"
#include "TStyle.h"
#include "canvas_margin.h"
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class trilepton_mumumu{
public:
  //==== constructors
  trilepton_mumumu();
  ~trilepton_mumumu();

  enum signal_class{
    no_class = 0,
    class1 = 1,
    class2 = 2,
    lowmass = 12,
    class3 = 3,
    class4 = 4,
    highmass = 34,
  };
  
  //==== functions
  void draw_hist();
  void make_bkglist();
  TString find_MCsector();
  void clear_legend_info();
  double get_coupling_constant(int mass);
  void fill_legend(TLegend* lg, TH1F* hist);
  void draw_legend(TLegend* lg, signal_class sc);
  void draw_canvas(THStack* mc_stack, TH1F* mc_error, TH1F* hist_data, map<int, TH1F*> hist_signal, TLegend* legend);
  int n_rebin();
  double y_max();
  void SetXaxisRangeBoth(THStack* mc_stack, TH1F* hist, float xmin, float xmax);
  void mkdir(TString path);
  void make_plot_directory();
  TString legend_coupling_label(int mass);
  
  //==== variables
  unsigned int i_cut, i_var, i_file;
  bool UseSetLogy=false;
  TString filename_prefix, filename_suffix, data_class, plotpath;
  vector<TString> histname_suffix, bkglist, samples_to_use, histname, x_title;
  map< TString, vector<TString> > map_sample_string_to_list;
  map< TString, pair<TString, Color_t> > map_sample_string_to_legendinfo;
  map<int, int> signal_survive_index;
  vector<int> MCsector_first_index;
  vector<int> signal_mass;
  vector<Color_t> signal_color;
  vector<double> coupling_const;
  map<TString, bool> MCsector_survive;
  TFile *outputfile;
  vector<TH1F*> hist_for_legend;
  map< pair<TString, TString>, int > rebins;
  map< pair<TString, TString>, double > y_maxs;
  double default_y_max = 1000;
  double k_factor;
  double log_of_generation_mixing;
  


};
#endif
