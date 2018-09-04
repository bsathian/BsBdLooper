// -*- C++ -*-
#ifndef BsBd_H
#define BsBd_H
#include "Math/LorentzVector.h"
#include "Math/Point3D.h"
#include "TMath.h"
#include "TBranch.h"
#include "TTree.h"
#include "TH1F.h"
#include "TFile.h"
#include "TBits.h"
#include <vector>
#include <unistd.h>
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

// Generated with file: /nfs-7/userdata/bsathian/BsToMuMuBabies/baby_1.root

using namespace std;
class BsBd {
private:
protected:
  unsigned int index;
  vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *lt_muon_p4_;
  TBranch *lt_muon_p4_branch;
  bool lt_muon_p4_isLoaded;
  ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *PV_;
  TBranch *PV_branch;
  bool PV_isLoaded;
  vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *gen_muon_v4_;
  TBranch *gen_muon_v4_branch;
  bool gen_muon_v4_isLoaded;
  vector<int> *lt_id_;
  TBranch *lt_id_branch;
  bool lt_id_isLoaded;
  vector<vector<float> > *lep_vtx_cov_;
  TBranch *lep_vtx_cov_branch;
  bool lep_vtx_cov_isLoaded;
  vector<int> *ll_id_;
  TBranch *ll_id_branch;
  bool ll_id_isLoaded;
  vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *lep_vtx_;
  TBranch *lep_vtx_branch;
  bool lep_vtx_isLoaded;
  vector<float> *PV_cov_;
  TBranch *PV_cov_branch;
  bool PV_cov_isLoaded;
  vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *ll_muon_p4_;
  TBranch *ll_muon_p4_branch;
  bool ll_muon_p4_isLoaded;
  vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *gen_muon_p4_;
  TBranch *gen_muon_p4_branch;
  bool gen_muon_p4_isLoaded;
public:
  void Init(TTree *tree);
  void GetEntry(unsigned int idx);
  void LoadAllBranches();
  const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &lt_muon_p4();
  const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &PV();
  const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &gen_muon_v4();
  const vector<int> &lt_id();
  const vector<vector<float> > &lep_vtx_cov();
  const vector<int> &ll_id();
  const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &lep_vtx();
  const vector<float> &PV_cov();
  const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &ll_muon_p4();
  const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &gen_muon_p4();
  static void progress( int nEventsTotal, int nEventsChain );
};

#ifndef __CINT__
extern BsBd bsbd;
#endif

namespace tas {

  const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &lt_muon_p4();
  const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &PV();
  const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &gen_muon_v4();
  const vector<int> &lt_id();
  const vector<vector<float> > &lep_vtx_cov();
  const vector<int> &ll_id();
  const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &lep_vtx();
  const vector<float> &PV_cov();
  const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &ll_muon_p4();
  const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &gen_muon_p4();
}
#endif
