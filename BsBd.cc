#include "BsBd.h"
BsBd bsbd;

void BsBd::Init(TTree *tree) {
  lt_muon_p4_branch = 0;
  if (tree->GetBranch("lt_muon_p4") != 0) {
    lt_muon_p4_branch = tree->GetBranch("lt_muon_p4");
    if (lt_muon_p4_branch) { lt_muon_p4_branch->SetAddress(&lt_muon_p4_); }
  }
  PV_branch = 0;
  if (tree->GetBranch("PV") != 0) {
    PV_branch = tree->GetBranch("PV");
    if (PV_branch) { PV_branch->SetAddress(&PV_); }
  }
  gen_muon_v4_branch = 0;
  if (tree->GetBranch("gen_muon_v4") != 0) {
    gen_muon_v4_branch = tree->GetBranch("gen_muon_v4");
    if (gen_muon_v4_branch) { gen_muon_v4_branch->SetAddress(&gen_muon_v4_); }
  }
  lep_vtx_branch = 0;
  if (tree->GetBranch("lep_vtx") != 0) {
    lep_vtx_branch = tree->GetBranch("lep_vtx");
    if (lep_vtx_branch) { lep_vtx_branch->SetAddress(&lep_vtx_); }
  }
  ll_muon_p4_branch = 0;
  if (tree->GetBranch("ll_muon_p4") != 0) {
    ll_muon_p4_branch = tree->GetBranch("ll_muon_p4");
    if (ll_muon_p4_branch) { ll_muon_p4_branch->SetAddress(&ll_muon_p4_); }
  }
  gen_muon_p4_branch = 0;
  if (tree->GetBranch("gen_muon_p4") != 0) {
    gen_muon_p4_branch = tree->GetBranch("gen_muon_p4");
    if (gen_muon_p4_branch) { gen_muon_p4_branch->SetAddress(&gen_muon_p4_); }
  }
  tree->SetMakeClass(1);
  muon_pixelhits_branch = 0;
  if (tree->GetBranch("muon_pixelhits") != 0) {
    muon_pixelhits_branch = tree->GetBranch("muon_pixelhits");
    if (muon_pixelhits_branch) { muon_pixelhits_branch->SetAddress(&muon_pixelhits_); }
  }
  lt_id_branch = 0;
  if (tree->GetBranch("lt_id") != 0) {
    lt_id_branch = tree->GetBranch("lt_id");
    if (lt_id_branch) { lt_id_branch->SetAddress(&lt_id_); }
  }
  lep_vtx_cov_branch = 0;
  if (tree->GetBranch("lep_vtx_cov") != 0) {
    lep_vtx_cov_branch = tree->GetBranch("lep_vtx_cov");
    if (lep_vtx_cov_branch) { lep_vtx_cov_branch->SetAddress(&lep_vtx_cov_); }
  }
  ll_id_branch = 0;
  if (tree->GetBranch("ll_id") != 0) {
    ll_id_branch = tree->GetBranch("ll_id");
    if (ll_id_branch) { ll_id_branch->SetAddress(&ll_id_); }
  }
  PV_cov_branch = 0;
  if (tree->GetBranch("PV_cov") != 0) {
    PV_cov_branch = tree->GetBranch("PV_cov");
    if (PV_cov_branch) { PV_cov_branch->SetAddress(&PV_cov_); }
  }
  muon_mother_id_branch = 0;
  if (tree->GetBranch("muon_mother_id") != 0) {
    muon_mother_id_branch = tree->GetBranch("muon_mother_id");
    if (muon_mother_id_branch) { muon_mother_id_branch->SetAddress(&muon_mother_id_); }
  }
  muon_hits_branch = 0;
  if (tree->GetBranch("muon_hits") != 0) {
    muon_hits_branch = tree->GetBranch("muon_hits");
    if (muon_hits_branch) { muon_hits_branch->SetAddress(&muon_hits_); }
  }
  tree->SetMakeClass(0);
}
void BsBd::GetEntry(unsigned int idx) {
  index = idx;
  muon_pixelhits_isLoaded = false;
  lt_muon_p4_isLoaded = false;
  PV_isLoaded = false;
  gen_muon_v4_isLoaded = false;
  lt_id_isLoaded = false;
  lep_vtx_cov_isLoaded = false;
  ll_id_isLoaded = false;
  lep_vtx_isLoaded = false;
  PV_cov_isLoaded = false;
  ll_muon_p4_isLoaded = false;
  gen_muon_p4_isLoaded = false;
  muon_mother_id_isLoaded = false;
  muon_hits_isLoaded = false;
}
void BsBd::LoadAllBranches() {
  if (muon_pixelhits_branch != 0) muon_pixelhits();
  if (lt_muon_p4_branch != 0) lt_muon_p4();
  if (PV_branch != 0) PV();
  if (gen_muon_v4_branch != 0) gen_muon_v4();
  if (lt_id_branch != 0) lt_id();
  if (lep_vtx_cov_branch != 0) lep_vtx_cov();
  if (ll_id_branch != 0) ll_id();
  if (lep_vtx_branch != 0) lep_vtx();
  if (PV_cov_branch != 0) PV_cov();
  if (ll_muon_p4_branch != 0) ll_muon_p4();
  if (gen_muon_p4_branch != 0) gen_muon_p4();
  if (muon_mother_id_branch != 0) muon_mother_id();
  if (muon_hits_branch != 0) muon_hits();
}
const vector<int> &BsBd::muon_pixelhits() {
  if (not muon_pixelhits_isLoaded) {
    if (muon_pixelhits_branch != 0) {
      muon_pixelhits_branch->GetEntry(index);
    } else {
      printf("branch muon_pixelhits_branch does not exist!\n");
      exit(1);
    }
    muon_pixelhits_isLoaded = true;
  }
  return *muon_pixelhits_;
}
const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &BsBd::lt_muon_p4() {
  if (not lt_muon_p4_isLoaded) {
    if (lt_muon_p4_branch != 0) {
      lt_muon_p4_branch->GetEntry(index);
    } else {
      printf("branch lt_muon_p4_branch does not exist!\n");
      exit(1);
    }
    lt_muon_p4_isLoaded = true;
  }
  return *lt_muon_p4_;
}
const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &BsBd::PV() {
  if (not PV_isLoaded) {
    if (PV_branch != 0) {
      PV_branch->GetEntry(index);
    } else {
      printf("branch PV_branch does not exist!\n");
      exit(1);
    }
    PV_isLoaded = true;
  }
  return *PV_;
}
const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &BsBd::gen_muon_v4() {
  if (not gen_muon_v4_isLoaded) {
    if (gen_muon_v4_branch != 0) {
      gen_muon_v4_branch->GetEntry(index);
    } else {
      printf("branch gen_muon_v4_branch does not exist!\n");
      exit(1);
    }
    gen_muon_v4_isLoaded = true;
  }
  return *gen_muon_v4_;
}
const vector<int> &BsBd::lt_id() {
  if (not lt_id_isLoaded) {
    if (lt_id_branch != 0) {
      lt_id_branch->GetEntry(index);
    } else {
      printf("branch lt_id_branch does not exist!\n");
      exit(1);
    }
    lt_id_isLoaded = true;
  }
  return *lt_id_;
}
const vector<vector<float> > &BsBd::lep_vtx_cov() {
  if (not lep_vtx_cov_isLoaded) {
    if (lep_vtx_cov_branch != 0) {
      lep_vtx_cov_branch->GetEntry(index);
    } else {
      printf("branch lep_vtx_cov_branch does not exist!\n");
      exit(1);
    }
    lep_vtx_cov_isLoaded = true;
  }
  return *lep_vtx_cov_;
}
const vector<int> &BsBd::ll_id() {
  if (not ll_id_isLoaded) {
    if (ll_id_branch != 0) {
      ll_id_branch->GetEntry(index);
    } else {
      printf("branch ll_id_branch does not exist!\n");
      exit(1);
    }
    ll_id_isLoaded = true;
  }
  return *ll_id_;
}
const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &BsBd::lep_vtx() {
  if (not lep_vtx_isLoaded) {
    if (lep_vtx_branch != 0) {
      lep_vtx_branch->GetEntry(index);
    } else {
      printf("branch lep_vtx_branch does not exist!\n");
      exit(1);
    }
    lep_vtx_isLoaded = true;
  }
  return *lep_vtx_;
}
const vector<float> &BsBd::PV_cov() {
  if (not PV_cov_isLoaded) {
    if (PV_cov_branch != 0) {
      PV_cov_branch->GetEntry(index);
    } else {
      printf("branch PV_cov_branch does not exist!\n");
      exit(1);
    }
    PV_cov_isLoaded = true;
  }
  return *PV_cov_;
}
const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &BsBd::ll_muon_p4() {
  if (not ll_muon_p4_isLoaded) {
    if (ll_muon_p4_branch != 0) {
      ll_muon_p4_branch->GetEntry(index);
    } else {
      printf("branch ll_muon_p4_branch does not exist!\n");
      exit(1);
    }
    ll_muon_p4_isLoaded = true;
  }
  return *ll_muon_p4_;
}
const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &BsBd::gen_muon_p4() {
  if (not gen_muon_p4_isLoaded) {
    if (gen_muon_p4_branch != 0) {
      gen_muon_p4_branch->GetEntry(index);
    } else {
      printf("branch gen_muon_p4_branch does not exist!\n");
      exit(1);
    }
    gen_muon_p4_isLoaded = true;
  }
  return *gen_muon_p4_;
}
const vector<int> &BsBd::muon_mother_id() {
  if (not muon_mother_id_isLoaded) {
    if (muon_mother_id_branch != 0) {
      muon_mother_id_branch->GetEntry(index);
    } else {
      printf("branch muon_mother_id_branch does not exist!\n");
      exit(1);
    }
    muon_mother_id_isLoaded = true;
  }
  return *muon_mother_id_;
}
const vector<int> &BsBd::muon_hits() {
  if (not muon_hits_isLoaded) {
    if (muon_hits_branch != 0) {
      muon_hits_branch->GetEntry(index);
    } else {
      printf("branch muon_hits_branch does not exist!\n");
      exit(1);
    }
    muon_hits_isLoaded = true;
  }
  return *muon_hits_;
}
void BsBd::progress( int nEventsTotal, int nEventsChain ){
  int period = 1000;
  if(nEventsTotal%1000 == 0) {
    if (isatty(1)) {
      if( ( nEventsChain - nEventsTotal ) > period ){
        float frac = (float)nEventsTotal/(nEventsChain*0.01);
        printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%"
               "\033[0m\033[32m <---\033[0m\015", frac);
        fflush(stdout);
      }
      else {
        printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%"
               "\033[0m\033[32m <---\033[0m\015", 100.);
        cout << endl;
      }
    }
  }
}
namespace tas {
  const vector<int> &muon_pixelhits() { return bsbd.muon_pixelhits(); }
  const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &lt_muon_p4() { return bsbd.lt_muon_p4(); }
  const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &PV() { return bsbd.PV(); }
  const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &gen_muon_v4() { return bsbd.gen_muon_v4(); }
  const vector<int> &lt_id() { return bsbd.lt_id(); }
  const vector<vector<float> > &lep_vtx_cov() { return bsbd.lep_vtx_cov(); }
  const vector<int> &ll_id() { return bsbd.ll_id(); }
  const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &lep_vtx() { return bsbd.lep_vtx(); }
  const vector<float> &PV_cov() { return bsbd.PV_cov(); }
  const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &ll_muon_p4() { return bsbd.ll_muon_p4(); }
  const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &gen_muon_p4() { return bsbd.gen_muon_p4(); }
  const vector<int> &muon_mother_id() { return bsbd.muon_mother_id(); }
  const vector<int> &muon_hits() { return bsbd.muon_hits(); }
}
