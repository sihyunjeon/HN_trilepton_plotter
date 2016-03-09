#ifndef trilepton_mumumu_h
#define trilepton_mumumu_h

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
  // constructors
  trilepton_mumumu();
  ~trilepton_mumumu();

  // functions
  void draw_hist();
  void make_bkglist();
  TString find_MCsector(int index);
  void clear_legend_info();
  void fill_legend(TLegend* lg, TH1F* hist, int index);
  void draw_legend(TLegend* lg);
  int n_rebin(TString cut, TString var);
  double y_max(TString cut, TString var);

  // variables
  TString filename_prefix, filename_suffix;
  vector<TString> histname_suffix, bkglist, samples_to_use, histname, x_title;
  map< TString, vector<TString> > map_sample_string_to_list;
  map< TString, pair<TString, Color_t> > map_sample_string_to_legendinfo;
  vector<int> MCsector_first_index;
  map<TString, bool> MCsector_survive;
  TFile *outputfile;
  vector<TH1F*> hist_for_legend;


};
#endif
