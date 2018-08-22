# include "analysis.h"
 
Looper::Looper(std::string fileName)
{
    outputHists = new TFile(fileName.c_str(),"RECREATE");
    outputHists->cd();
}
Looper::~Looper()
{
    outputHists->Write();
    outputHists->Close();
}

template <typename T> T* Looper::createHists(std::string histName,std::string histTitle,int nbins, float lower, float upper)
{
    T *tempHist = new TH1F(histName.c_str(),histTitle.c_str(),nbins,lower,upper); //check format
    tempHist->SetDirectory(outputHists);
    return tempHist;
}


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

    for(unsigned int event = 0;event<nEventsChain;event++)
    {
        cms3.GetEntry(event);
        nEventsTotal++;
        std::cout<<"Event number="<<event<<std::endl;

        /*Start the cuts*/
                
    } 
}

