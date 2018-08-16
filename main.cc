# include "looper.cc"
# include "analysis.h"

int main(int argc,char* argv[])
{
    std::string outputHistFileName("outputHists.root");
    std::string dataFileName("/nfs-7/userdata/balaji/DY_VertexFit/ntuple.root");
    Looper l(outputHistFileName);
    l.readChain(dataFileName);
    l.loop();
}
