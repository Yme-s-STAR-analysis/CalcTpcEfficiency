#include <iostream>
#include <fstream>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TEfficiency.h"
#include "TNtuple.h"
#include "TString.h"

#include "EffTool.h"

TpcEffMaker:: TpcEffMaker(const char* fout_name) {
    // init. TFiles
    // tf_in_p = TFile::Open(fin_name_p);
    // tf_in_a = TFile::Open(fin_name_a);
    // v5.0: now we will read a file list
    // and the initialization is moved to TpcEffMaker::make()

    tf_out = new TFile(fout_name, "recreate");
    // init. cuts
    mCut_dca = 1.0;
    mCut_nHitsFit = 20;

    // init. TH1F and TH2F arrays
    const char* pname[2] = {"Pro", "Pbar"};
    for (int ptype=0; ptype<2; ptype++) {
        for (int i=0; i<nCent; i++) {
            for (int ivz=0; ivz<nVz; ivz++) {

            #ifdef __FULL_GRAPH__
                teff_eta[i][ivz][ptype] = new TEfficiency(
                    Form("TpcEff_eta_cent%d_vz%d_%s", i, ivz, pname[ptype]),
                    ";#eta;Efficiency", 30, -1.5, 1.5
                );
                teff_y[i][ivz][ptype] = new TEfficiency(
                    Form("TpcEff_y_cent%d_vz%d_%s", i, ivz, pname[ptype]),
                    ";y;Efficiency", 30, -1.5, 1.5
                );
            #endif

                teff_y_pt[i][ivz][ptype] = new TEfficiency(
                    Form("TpcEff_y_pt_cent%d_vz%d_%s", i, ivz, pname[ptype]), 
                    ";y;p_{T} [GeV/c];Efficiency", 30, -1.5, 1.5, 21, 0.0, 2.1
                );
            }
        }
    }
}

int TpcEffMaker::vz_split(double val) {
    // split vz into nVz bins
    if (-30 < val && val < -10) {
        return 0;
    } else if (-10 < val && val < 10) {
        return 1;
    } else if (10 < val && val < 30) {
        return 2;
    } else if (-50 < val && val < -30) {
        return 3;
    } else if (30 < val && val < 50) {
        return 4;
    } else {
        return -1;
    }
}

void TpcEffMaker::make(const char* input_list, int ptype){
    std::ifstream fin;
    std::string strtmp;
    TChain* tree = new TChain("fDstTree");

    fin.open(input_list);
    while (std::getline(fin, strtmp)) {
        tree->Add(strtmp.c_str());
        std::cout << "[LOG] Now adding new TFile: " << strtmp << std::endl;
    }
    fin.close();

    if (ptype == 0) { // proton
        std::cout << "[LOG] Now calculate Proton.\n";
    } else if (ptype == 1) { // antiproton
        std::cout << "[LOG] Now calculate Antiproton.\n";
    }

    Float_t cent, vz;
    Float_t match, pt, eta, y;
    Float_t nHitsFit, nHitsDedx, nHitsRatio, dca;

    // additional variables
    Int_t ntrk = tree->GetEntries();
    int cent_int = 0;
    int vzBin = 0;

    // set branch address
    // tree->SetBranchAddress("RefMult3", ref3); // if need to correct the cent definition
    tree->SetBranchAddress("cent", &cent);
    tree->SetBranchAddress("vz", &vz);
    tree->SetBranchAddress("match", &match);
    tree->SetBranchAddress("pT", &pt);
    tree->SetBranchAddress("eta", &eta);
    tree->SetBranchAddress("y", &y);
    tree->SetBranchAddress("nHitsFit", &nHitsFit);
    tree->SetBranchAddress("nHitsDedx", &nHitsDedx);
    tree->SetBranchAddress("nHitsRatio", &nHitsRatio);
    tree->SetBranchAddress("dca", &dca);

    std::cout << "[LOG] Start reading tree, " << ntrk << " tracks there.\n";
    for (Int_t i=0; i<ntrk; i++){
        if (i%50000 == 0) {
            std::cout << i << " tracks read (" << i << "/" << ntrk << ")\n";
        }
        tree->GetEntry(i);
        // event cut here
        vzBin = vz_split(vz);

        if (vzBin < 0) {
            continue;
        }
        cent_int = (Int_t)cent;
        if (cent_int < 0 || cent_int > 8){
            continue;
        }
        if (fabs(vz) > 50 || vz < -900){
            continue;
        }

        // track cuts here
        bool acc = match > 0 ? true : false; // (bool)match
        acc = acc && (nHitsFit >= mCut_nHitsFit) && (nHitsRatio >= 0.52) && (nHitsDedx >= 5) && (dca < mCut_dca);

        teff_y_pt[cent_int][vzBin][ptype]->Fill(acc, y, pt);

        // fill detailed histograms
        #ifdef __FULL_GRAPH__
            if (pt > 0.4 && pt < 2.0) {
                teff_eta[cent_int][vzBin][ptype]->Fill(acc, eta);
                teff_y[cent_int][vzBin][ptype]->Fill(acc, y);
            }
        #endif

    } // track loops
    std::cout << "[LOG] All tracks looped.\n";
}

void TpcEffMaker::write(){
    std::cout << "[LOG] Saving efficiency results.\n";
    tf_out->cd();
    const char* pname[2] = {"Pro", "Pbar"};
    for (int ptype=0; ptype<2; ptype++) {
        for (int i=0; i<nCent; i++) {
            for (int ivz=0; ivz<nVz; ivz++) {
            #ifdef __FULL_GRAPH__
                teff_eta[i][ivz][ptype]->Write();
                teff_y[i][ivz][ptype]->Write();
            #endif
                teff_y_pt[i][ivz][ptype]->Write();
            }
        }
    }
    tf_out->Close();
}
