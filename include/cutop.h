//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Oct 31 12:17:24 2016 by ROOT version 6.06/00
// from TTree cutop/cutop
// found on file: trilepton_mumumu_data_cat_v8-0-1.root
//////////////////////////////////////////////////////////

#ifndef cutop_h
#define cutop_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class cutop {
  public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain
  
  // Fixed size dimensions of array or collections stored in the TTree if any.
  
  // Declaration of leaf types
  Double_t        first_pt;
  Double_t        second_pt;
  Double_t        third_pt;
  Double_t        PFMET;
  Double_t        HN_1_mass;
  Double_t        HN_2_mass;
  Double_t        HN_3_mass;
  Double_t        HN_4_mass;
  Double_t        W_pri_lowmass_mass;
  Double_t        W_pri_highmass_mass;
  Double_t        weight;

  // List of branches
  TBranch        *b_first_pt;   //!
  TBranch        *b_second_pt;   //!
  TBranch        *b_third_pt;   //!
  TBranch        *b_PFMET;   //!
  TBranch        *b_HN_1_mass;   //!
  TBranch        *b_HN_2_mass;   //!
  TBranch        *b_HN_3_mass;   //!
  TBranch        *b_HN_4_mass;   //!
  TBranch        *b_W_pri_lowmass_mass;   //!
  TBranch        *b_W_pri_highmass_mass;   //!
  TBranch        *b_weight;   //!
  
  double TotalEvent;
  double n_weighted;
  Long64_t n_unweighted;
  double cut_first_pt;
  double cut_second_pt;
  double cut_third_pt;
  double cut_PFMET;
  double cut_W_pri_mass;
  int signalclass;
  double min_HN_mass;
  
  cutop(TString sample, TString whichSyst);
  virtual ~cutop();
  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop();
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
  
  Double_t HN_mass_by_signalclass();
  
};

#endif

#ifdef cutop_cxx
cutop::cutop(TString sample, TString whichSyst) : fChain(0),
TotalEvent(0), n_weighted(0.), n_unweighted(0), cut_first_pt(20.), cut_second_pt(10.), cut_third_pt(10.), cut_PFMET(9999.), cut_W_pri_mass(9999.), signalclass(1), min_HN_mass(0.)
{
  TString fname = sample;
  TTree *tree;
  TFile *f = new TFile(fname);
  TH1D *cutflow = (TH1D*)f->Get("cutflow");
  TotalEvent = cutflow->GetBinContent(1);
  f->GetObject(whichSyst, tree);
    
  Init(tree);
}

cutop::~cutop()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t cutop::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t cutop::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
    Notify();
  }
  return centry;
}

void cutop::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).
  
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);
  
  fChain->SetBranchAddress("first_pt", &first_pt, &b_first_pt);
  fChain->SetBranchAddress("second_pt", &second_pt, &b_second_pt);
  fChain->SetBranchAddress("third_pt", &third_pt, &b_third_pt);
  fChain->SetBranchAddress("HN_1_mass", &HN_1_mass, &b_HN_1_mass);
  fChain->SetBranchAddress("HN_2_mass", &HN_2_mass, &b_HN_2_mass);
  fChain->SetBranchAddress("HN_3_mass", &HN_3_mass, &b_HN_3_mass);
  fChain->SetBranchAddress("HN_4_mass", &HN_4_mass, &b_HN_4_mass);
  fChain->SetBranchAddress("PFMET", &PFMET, &b_PFMET);
  fChain->SetBranchAddress("W_pri_lowmass_mass", &W_pri_lowmass_mass, &b_W_pri_lowmass_mass);
  fChain->SetBranchAddress("W_pri_highmass_mass", &W_pri_highmass_mass, &b_W_pri_highmass_mass);
  fChain->SetBranchAddress("weight", &weight, &b_weight);

  Notify();
}

Bool_t cutop::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.
  
  return kTRUE;
}

void cutop::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}
Int_t cutop::Cut(Long64_t entry)
{
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}
#endif // #ifdef cutop_cxx
