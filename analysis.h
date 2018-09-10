#ifndef ANALYSIS_H
#define ANALYSIS_H

# include <iostream>
# include <vector>
# include <set>
# include <tuple>
# include <utility>
# include <fstream>
# include <cmath>

//ROOT
# include "TBenchmark.h"
# include "TChain.h"
# include "TDirectory.h"
# include "TFile.h"
# include "TROOT.h"
# include "TTreeCache.h"
# include "TEfficiency.h"
# include "TH1.h"
# include "TH2.h"
# include "TH3.h"

//CMS3
# include "BsBd.h"


class Looper
{
    private:
        TChain *ch;
        TH1F *hCovxx,*hCovxy,*hCovxz,*hCovyy,*hCovyz,*hCovzz;
        TH1F *hllMuonPt, *hllMuonEta, *hltMuonPt, *hltMuonEta,*hMll[5];
        TH1F *hPVx, *hPVy, *hPVz, *hl3D, *hSigmal3D;
        TH1F *hLVx, *hLVy, *hLVz;
        TH1F *hBsL;
        TH1F *resX, *resY, *resZ;
        TH1F *resPx,*resPy,*resPz,*resM; //not differentiating between the muons

        TH2F *muonEta;
        //Pull histograms
        TH1F *hPullX, *hPullY, *hPullZ;
        TH1F *hPullL3D;

        TFile *outputHists;

    public:
        Looper(std::string fileName); //Creates the histogram file
        template <typename T> T* createHists(std::string histName,std::string histTitle,int nbins,float lower,float upper); //try to do this in a template form
        template <typename T> T* createHists(std::string histName,std::string histTitle, std::vector<float> bins);

        template <typename T> T* create2DHists(std::string histName, std::string histTitle, int nbinsx, float xlow, float xup, int nbinsy, float ylow, float yup);
        void readChain(std::string FileName);
        void loop();
        ~Looper(); //Write histograms to file        
};

#endif
