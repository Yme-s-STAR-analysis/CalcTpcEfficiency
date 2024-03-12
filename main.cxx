#include <iostream>
#include "EffTool.h"

using std::cout;
using std::endl;

int main(int argc, char* argv[]){
    cout << "[LOG] Welcome to TPC tracking efficiency histogram generator!" << endl;
    cout << "[LOG] Arguments:" << endl;
    cout << "[LOG]  -> File list fDst tree: " << argv[1] << endl;
    cout << "[LOG]  -> Proton type: " << argv[2] << endl;
    cout << "[LOG]  -> Output file name: " << argv[3] << endl;
    cout << "[LOG]  -> DCA cut " << argv[4] << endl;
    cout << "[LOG]  -> nHitsFit " << argv[5] << endl;
    int mode = atoi(argv[2]);
    TpcEffMaker* maker = new TpcEffMaker(argv[3]);
    double mDcaCut = atof(argv[4]);
    double mNhitsCut = atoi(argv[5]);
    maker->set_cut_dca(mDcaCut);
    maker->set_cut_nHitsFit(mNhitsCut);
    maker->make(argv[1], mode); 
    maker->write();
    return 0;
}
