# include "analysis.h"


Looper::looper(std::string fileName)
{
    TFile *file = new TFile(fileName.c_str(),"RECREATE");
}

void Looper::readChain()
{
    ch = new TChain("Events");
    ch->Add("/nfs-7/userdata/balaji/DY_VertexFit/ntuple.root");
}

void Looper::loop()
{
    unsigned int nEventsTotal = 0;
    unsigned int nEventsChain = ch->GetEntries();
    
    cms3.Init(ch);

    for(unsigned int event = 0;event<nEventsChain;event++)
    {
        cms3.GetEntry(event);
        nEventsTotal++;
        
    } 
}

int main(int argc,char* argv[])
{
    Looper l("outputHists.root");
    l.readChain();
    l.loop();
}
