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


template <typename T> T* Looper::createHists(std::string histName,std::string histTitle,std::vector<float> bins)
{
    T* tempHist = new TH1F(histName.c_str(),histTitle.c_str(),bins.size()-1,&bins[0]);
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
    hCovxx = createHists<TH1F>("hCovxx","Covariance-XX",1000,log10(1e-6),log10(1));
    hCovyy = createHists<TH1F>("hCovyy","Covariance-YY",1000,log10(1e-6),log10(1));
    hCovzz = createHists<TH1F>("hCovzz","Covariance-ZZ",1000,log10(1e-6),log10(1));
    hCovxy = createHists<TH1F>("hCovxy","Covariance-XY",1000,-1e-4,1e-4);
    hCovyz = createHists<TH1F>("hCovyz","Covariance-YZ",1000,-1e-4,1e-4);
    hCovxz = createHists<TH1F>("hCovxz","Covariance-XZ",1000,-1e-4,1e-4);

    hllMuonPt = createHists<TH1F>("hllMuonPt","Leading Muon Pt",200,4,100);
    hltMuonPt = createHists<TH1F>("hltMuonPt","Trailing Muon Pt",200,4,100);
    hllMuonEta = createHists<TH1F>("hllMuonEta","Leading Muon Eta",100,-3,3);
    hltMuonEta = createHists<TH1F>("hltMuonEta","Trailing Muon Eta",100,-3,3);
    hMll = createHists<TH1F>("hMll","Dilepton mass",100,2,6);

    hPVx = createHists<TH1F>("hPVx","Primary Vertex X",100,0,1);
    hPVy = createHists<TH1F>("hPVy","Primary Vertex Y",100,0,1);
    hPVz = createHists<TH1F>("hPVz","Primary vertex Z",100,0,1);

    
//float l3Dbins[] = {};
    std::vector<float>l3Dbins;
    for(float i=0;i<=20;i+=0.01)
        l3Dbins.push_back(i);
    for(float i=20;i<=50;i+=1)
        l3Dbins.push_back(i);
    for(float i=50;i<=100;i+=5)
        l3Dbins.push_back(i);

    hl3D = createHists<TH1F>("hl3D","Drift Length",l3Dbins);

    std::vector<float> sigmal3DBins;
    for(float i=0;i<=1;i+=0.0001)
        sigmal3DBins.push_back(i);
    for(float i=1;i<5;i+=0.01)
        sigmal3DBins.push_back(i);
    for(float i=5;i<10;i+=0.1)
        sigmal3DBins.push_back(i);

    hSigmal3D = createHists<TH1F>("hSigmal3D","Error in Drift Length",sigmal3DBins);

    hLVx = createHists<TH1F>("hLVx","Lepton Vertex X",1000,0,100);
    hLVy = createHists<TH1F>("hLVy","Lepton Vertex Y",1000,0,100);
    hLVz = createHists<TH1F>("hLVz","Lepton vertex Z",1000,0,100);


    float l3D,lvX,lvY,lvZ,pvX,pvY,pvZ,sigmal3D,var3D;        

    for(unsigned int event = 0;event<nEventsChain;event++)
    {
        cms3.GetEntry(event);
        nEventsTotal++;

        /*Start the cuts*/

        pvX = cms3.vtxs_position().at(0).X();
        pvY = cms3.vtxs_position().at(0).Y();
        pvZ = cms3.vtxs_position().at(0).Z();

        hPVx->Fill(pvX);
        hPVy->Fill(pvY);
        hPVz->Fill(pvZ);
        for(size_t i=0;i<cms3.hyp_FVFit_status().size();i++)
        {
            if(!(cms3.hyp_ll_id().at(i) * cms3.hyp_lt_id().at(i) == -169))
            {
                continue;
            }
            
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

            
            lvX = cms3.hyp_FVFit_v4().at(i).X();
            lvY = cms3.hyp_FVFit_v4().at(i).Y();
            lvZ = cms3.hyp_FVFit_v4().at(i).Z();
            
            
            hLVx->Fill(lvX);
            hLVy->Fill(lvY);
            hLVz->Fill(lvZ);

            l3D = sqrt((lvX - pvX)*(lvX - pvX) + (lvY - pvY) * (lvY - pvY) + (lvZ - pvZ) * (lvZ - pvZ));



            hl3D->Fill(l3D);

            var3D = ((pvX - lvX) * (pvX - lvX) * (cms3.hyp_FVFit_v4cxx()[i] + cms3.vtxs_covMatrix()[0][0]) + (pvY - lvY) * (pvY - lvY) * (cms3.hyp_FVFit_v4cyy()[i] + cms3.vtxs_covMatrix()[0][4]) + (pvZ - lvZ) * (pvZ - lvZ) * (cms3.hyp_FVFit_v4czz()[i] + cms3.vtxs_covMatrix()[0][8]) + 2*(pvX - lvX)*(pvY - lvY) * (cms3.hyp_FVFit_v4cxy()[i] + cms3.vtxs_covMatrix()[0][1]) + 2*(pvX - lvX)*(pvZ - lvZ)*(cms3.hyp_FVFit_v4czx()[i] + cms3.vtxs_covMatrix()[0][2]) + 2*(pvY - lvY)*(pvZ - lvZ) * (cms3.hyp_FVFit_v4czy()[i] + cms3.vtxs_covMatrix()[0][5]))/(l3D * l3D);

            sigmal3D = sqrt(var3D);
            
            hSigmal3D->Fill(sigmal3D);




            //Muon parameters

            hllMuonPt->Fill(cms3.hyp_ll_p4().at(i).Pt());
            hltMuonPt->Fill(cms3.hyp_lt_p4().at(i).Pt());
            hllMuonEta->Fill(cms3.hyp_ll_p4().at(i).Eta());
            hltMuonEta->Fill(cms3.hyp_lt_p4().at(i).Eta());
            hMll->Fill((cms3.hyp_ll_p4().at(i) + cms3.hyp_lt_p4().at(i)).M());
        } 
        
    } 
}

