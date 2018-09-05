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


template <typename T> T* Looper::create2DHists(std::string histName,std::string histTitle,int nbinsx,float xlow, float xup, int nbinsy, float ylow, float yup)
{
    T* tempHist = new TH2F(histName.c_str(),histTitle.c_str(),nbinsx,xlow,xup,nbinsy,ylow,yup);
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
    bsbd.Init(ch);

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

    std::string MllName;
    for(int i=0;i<=4;i++)
    {
        MllName = "hMll"+to_string(i);
        hMll[i] = createHists<TH1F>(MllName.c_str(),"Dilepton mass",100,4,7);
    }

    hPVx = createHists<TH1F>("hPVx","Primary Vertex X",100,0,1);
    hPVy = createHists<TH1F>("hPVy","Primary Vertex Y",100,0,1);
    hPVz = createHists<TH1F>("hPVz","Primary vertex Z",100,0,1);

    hBsL = createHists<TH1F>("hBsL","Bs Lifetime (ct)",10000,0,10);
    
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

    resX = createHists<TH1F>("resX","X residual",2000,-10,10);
    resY = createHists<TH1F>("resY","Y residual",1000,-5,5);
    resZ = createHists<TH1F>("resZ","Z residual",4000,-20,20);

    resPx = createHists<TH1F>("resPx","Px residual",1000,-5,5);
    resPy = createHists<TH1F>("resPy","Py residual",1000,-5,5);
    resPz = createHists<TH1F>("resPz","Pz residual",1000,-5,5);
    resM = createHists<TH1F>("resM","M residual",1000,-5,5);

    muonEta = create2DHists<TH2F>("muonEta","muon Eta correlation",100,-3,3,100,-3,3);


    float l3D,lvX,lvY,lvZ,pvX,pvY,pvZ,sigmal3D,var3D;      
    float genlvX,genlvY,genlvZ;

    LorentzVector Bs_p4,Bs_gen_p4;
    float ll_eta, lt_eta, Mll,p;
    float Bs_l; //Bs lifetime

    for(unsigned int event = 0;event<nEventsChain;event++)
    {
        bsbd.GetEntry(event);
        nEventsTotal++;

        /*Start the cuts*/

        pvX = bsbd.PV().X();
        pvY = bsbd.PV().Y();
        pvZ = bsbd.PV().Z();

        hPVx->Fill(pvX);
        hPVy->Fill(pvY);
        hPVz->Fill(pvZ);
        for(size_t i=0;i<bsbd.lep_vtx().size();i++)
        {
            hCovxx->Fill(log10(bsbd.lep_vtx_cov().at(i).at(0)));
            hCovyy->Fill(log10(bsbd.lep_vtx_cov().at(i).at(4)));
            hCovzz->Fill(log10(bsbd.lep_vtx_cov().at(i).at(8)));
            hCovxy->Fill(bsbd.lep_vtx_cov().at(i).at(1));
            hCovxz->Fill(bsbd.lep_vtx_cov().at(i).at(2));
            hCovyz->Fill(bsbd.lep_vtx_cov().at(i).at(5));

            
            if(bsbd.lep_vtx().size() <= 0)
                continue;
            lvX = bsbd.lep_vtx().at(0).X();
            lvY = bsbd.lep_vtx().at(0).Y();
            lvZ = bsbd.lep_vtx().at(0).Z();

            
            
            hLVx->Fill(lvX);
            hLVy->Fill(lvY);
            hLVz->Fill(lvZ);

            l3D = sqrt((lvX - pvX)*(lvX - pvX) + (lvY - pvY) * (lvY - pvY) + (lvZ - pvZ) * (lvZ - pvZ));



            hl3D->Fill(l3D);

            var3D = ((pvX - lvX) * (pvX - lvX) * (bsbd.lep_vtx_cov().at(i).at(0) + bsbd.PV_cov()[0]) + (pvY - lvY) * (pvY - lvY) * (bsbd.lep_vtx_cov()[i][4] + bsbd.PV_cov()[4]) + (pvZ - lvZ) * (pvZ - lvZ) * (bsbd.lep_vtx_cov()[i][8] + bsbd.PV_cov()[8]) + 2*(pvX - lvX)*(pvY - lvY) * (bsbd.lep_vtx_cov().at(i).at(1) + bsbd.PV_cov()[1]) + 2*(pvX - lvX)*(pvZ - lvZ)*(bsbd.lep_vtx_cov().at(i).at(2) + bsbd.PV_cov()[2]) + 2*(pvY - lvY)*(pvZ - lvZ) * (bsbd.lep_vtx_cov().at(i).at(5) + bsbd.PV_cov()[5]))/(l3D * l3D);

            sigmal3D = sqrt(var3D);
            
            hSigmal3D->Fill(sigmal3D);




            //Muon parameters

            ll_eta = bsbd.ll_muon_p4().at(i).Eta();
            lt_eta = bsbd.lt_muon_p4().at(i).Eta();
            Bs_p4 = bsbd.ll_muon_p4().at(i) + bsbd.lt_muon_p4().at(i);
            p = sqrt(Bs_p4.X() * Bs_p4.X() + Bs_p4.Y() * Bs_p4.Y() + Bs_p4.Z() * Bs_p4.Z());
            Mll = (Bs_p4).M();

            Bs_l = l3D*Mll/p;
            hBsL->Fill(Bs_l);

            

            hllMuonPt->Fill(bsbd.ll_muon_p4().at(i).Pt());
            hltMuonPt->Fill(bsbd.lt_muon_p4().at(i).Pt());
            hllMuonEta->Fill(ll_eta);
            hltMuonEta->Fill(lt_eta);
            hMll[4]->Fill(Mll);

            if(abs(ll_eta) < 1 && abs(lt_eta) < 1)
                hMll[0]->Fill(Mll);
            else if(abs(ll_eta) < 1 && abs(lt_eta) < 1.6)
                hMll[1]->Fill(Mll);
            else if(abs(ll_eta) < 1.6 && abs(lt_eta) < 1)
                hMll[2]->Fill(Mll);
            else if(abs(ll_eta) < 1.6 && abs(lt_eta) < 1.6)
                hMll[3]->Fill(Mll);

            //gen - reco histograms
            
            if(bsbd.gen_muon_v4().size() == 0)
                continue;
            genlvX = bsbd.gen_muon_v4().at(0).X();
            genlvY = bsbd.gen_muon_v4().at(0).Y();
            genlvZ = bsbd.gen_muon_v4().at(0).Z();

            resX->Fill(lvX - genlvX);
            resY->Fill(lvY - genlvY);
            resZ->Fill(lvZ - genlvZ);

           if(bsbd.gen_muon_p4().size() < 2)
               continue;
           
           resPx->Fill(bsbd.ll_muon_p4().at(i).X() - bsbd.gen_muon_p4().at(1).X());
           resPx->Fill(bsbd.lt_muon_p4().at(i).X() - bsbd.gen_muon_p4().at(0).X());

           resPy->Fill(bsbd.ll_muon_p4().at(i).Y() - bsbd.gen_muon_p4().at(1).Y());
           resPy->Fill(bsbd.lt_muon_p4().at(i).Y() - bsbd.gen_muon_p4().at(0).Y());

           resPz->Fill(bsbd.ll_muon_p4().at(i).Z() - bsbd.gen_muon_p4().at(1).Z());
           resPz->Fill(bsbd.lt_muon_p4().at(i).Z() - bsbd.gen_muon_p4().at(0).Z());

            
           Bs_gen_p4 = bsbd.gen_muon_p4().at(0) + bsbd.gen_muon_p4().at(1);
           std::cout<<Bs_gen_p4.M()<<" "<<Bs_p4.M()<<std::endl;

           resM->Fill(Bs_p4.M() - Bs_gen_p4.M());

           //Muon Eta
           muonEta->Fill(bsbd.ll_muon_p4().at(i).Eta(),bsbd.lt_muon_p4().at(i).Eta());






            
        } 
        
    } 
}

