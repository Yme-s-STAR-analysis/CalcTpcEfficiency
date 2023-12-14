#ifndef __TPC_CALC_UTILS_HEAD__
#define __TPC_CALC_UTILS_HEAD__

// if you just want the TH2F efficiency heatmap, cancel this macro
// #define __FULL_GRAPH__

class TH2F;
class TFile;
class TEfficiency;

class TpcEffMaker{
    private:
        // tfiles to readin tracks and dump efficiencies
        TFile* tf_in_p;
        TFile* tf_in_a;
        TFile* tf_out;

        // quality cut limitations
        double mCut_dca;
        int mCut_nHitsFit;

        // histograms -> origin
        static const int nCent = 9;
        // as for the vz index, 0 for -30 to -10, 1 for pm 10, and 2 for 10 to 30
        // v3.1 new: now 3 for -50 to -30, 4 for 30 to 50
        static const int nVz = 5; 

    #ifdef __FULL_GRAPH__

        // THist
        TH1F* th1_eta_mc[nCent][nVz][2];
        TH1F* th1_y_mc[nCent][nVz][2];
        TH2F* th2_y_pt_mc[nCent][nVz][2];

        TH1F* th1_eta_rc[nCent][nVz][2];
        TH1F* th1_y_rc[nCent][nVz][2];
        TH2F* th2_y_pt_rc[nCent][nVz][2];

        // TEfficiency
        // centrality 0 ~ 9 from central to peripheral
        // last dim., 0 for proton and 1 for antiproton
        TEfficiency* teff_eta[nCent][nVz][2];
        TEfficiency* teff_y[nCent][nVz][2];
        // TEfficiency* teff_y_pt[nCent][nVz][2];

    #endif

        TEfficiency* teff_y_pt[nCent][nVz][2];
        TH2F* th2_y_pt[nCent][nVz][2];


    public:
        TpcEffMaker(const char* fin_name_p, const char* fin_name_a, const char* fout_name);
        ~TpcEffMaker(){}

        void make(int ptype);
        void write();
        int vz_split(double val);
        
        // cut setters
        void set_cut_dca(double value) { mCut_dca = value; }
        void set_cut_nHitsFit(int value) { mCut_nHitsFit = value; }
};

#endif
