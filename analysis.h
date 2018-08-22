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
# include "CMS3.h"


class Looper
{
    private:
        TChain *ch;
        TH1F *hCovxx,*hCovxy,*hCovxz,*hCovyy,*hCovyz,*hCovzz;
        TFile *outputHists;

    public:
        Looper(std::string fileName); //Creates the histogram file
        template <typename T> T* createHists(std::string histName,std::string histTitle,int nbins,float lower,float upper); //try to do this in a template form
        void readChain(std::string FileName);
        void loop();
        ~Looper(); //Write histograms to file        
};

#endif
