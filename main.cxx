#include "EffTool.h"

int main(int argc, char* argv[]){
    TpcEffMaker* maker = new TpcEffMaker(argv[1], argv[2], argv[3]);
    maker->set_cut_dca(1);
    maker->set_cut_nHitsFit(20);
    maker->make(0); // proton
    maker->make(1); // antiproton
    maker->write();
    return 0;
}
