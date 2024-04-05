#ifndef __TPC_CALC_UTILS_HEAD__
#define __TPC_CALC_UTILS_HEAD__

// in case you want to store eta or y dependence of efficiency, uncomment this
// #define __FULL_GRAPH__

class TFile;
class TEfficiency;

class TpcEffMaker{
    private:
        // tfiles to readin tracks and dump efficiencies
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
        // centrality 0 ~ 9 from central to peripheral
        // last dim., 0 for proton and 1 for antiproton
        TEfficiency* teff_eta[nCent][nVz][2];
        TEfficiency* teff_y[nCent][nVz][2];
    #endif

        TEfficiency* teff_y_pt[nCent][nVz][2];


    public:
        TpcEffMaker(const char* fout_name);
        ~TpcEffMaker(){}

        void make(const char* input_list, int ptype);
        void write();
        int vz_split(double val);
        
        // cut setters
        void set_cut_dca(double value) { mCut_dca = value; }
        void set_cut_nHitsFit(int value) { mCut_nHitsFit = value; }
};

#endif
