# include "analysis.h"

int main(int argc,char* argv[])
{
    if(argc < 3)
    {
        std::cout<<"./looper filename index"<<std::endl;
        return 1;
    }
    
    std::string outputHistFileName("outputHists_");
    std::string suffix(".root");
    std::string index(argv[2]);
    outputHistFileName = outputHistFileName + index + suffix;
    std::string dataFileName(argv[1]);
    Looper l(outputHistFileName);
    l.readChain(dataFileName);
    l.loop();
    return 0;
}
