# include "analysis.h"
 


void Looper::readChain(std::string FileName)
{
    ch = new TChain("Events");
    ch->Add(FileName.c_str());
}

void Looper::loop()
{
    unsigned int nEventsTotal = 0;
    unsigned int nEventsChain = ch->GetEntries();
    cms3.Init(ch);

    //create the histograms
    hCovxx = createHists("hCovxx","Covariance-XX",1000,log10(1e-6),log10(1));
    hCovyy = createHists("hCovyy","Covariance-YY",1000,log10(1e-6),log10(1));
    hCovzz = createHists("hCovzz","Covariance-ZZ",1000,log10(1e-6),log10(1));
    hCovxy = createHists("hCovxy","Covariance-XY",1000,-1e-4,1e-4);
    hCovyz = createHists("hCovyz","Covariance-YZ",1000,-1e-4,1e-4);
    hCovxz = createHists("hCovxz","Covariance-XZ",1000,-1e-4,1e-4);

    for(unsigned int event = 0;event<nEventsChain;event++)
    {
        cms3.GetEntry(event);
        nEventsTotal++;
        std::cout<<"Event number="<<event<<std::endl;

        /*Start the cuts*/
        for(int i=0;i<cms3.hyp_FVFit_status().size();i++)
        {
            if(cms3.hyp_FVFit_status()[i] != 0)
            {
                continue;
            }
            hCovxx->Fill(log10(cms3.hyp_FVFit_v4cxx()[i]));
            hCovyy->Fill(log10(cms3.hyp_FVFit_v4cyy()[i]));
            hCovzz->Fill(log10(cms3.hyp_FVFit_v4czz()[i]));
            hCovxy->Fill(cms3.hyp_FVFit_v4cxy()[i]);
            hCovxz->Fill(cms3.hyp_FVFit_v4czx()[i]);
            hCovyz->Fill(cms3.hyp_FVFit_v4czy()[i]);

        } 
        
    } 
}

