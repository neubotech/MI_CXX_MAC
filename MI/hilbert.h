//
//  hilbert.h
//  MI
//
//  Created by Nan Tian on 6/22/15.
//  Copyright (c) 2015 Nan Tian. All rights reserved.
//

#ifndef MI_hilbert_h
#define MI_hilbert_h


//#include <vector>
//#include <math.h> //for "floor"
//
//#include <Accelerate/Accelerate.h>
//#include <stdio.h>
//#include <stdlib.h>

#include <complex>
#include <fftw3.h>
using namespace std;

template<typename T>
void print_pointer(T &x, int N){
    for (int i = 0 ; i < N; i++) {
        cout << i << "\t" << x[i] << "\n";
    }
    cout << endl;
}

void print_complex(fftw_complex* x, int N){
    for (int i = 0; i < N; i++){
        cout << i << "\t" << x[i][0] << "\t" << x[i][1] << "\n";
    }
    cout << endl;
}

//hilbert Transform implemented using FFTW, good for variable size of real signal vector<double>
void hilbert_FFTW(vector<double> &X, vector<complex<double>> &H){
    fftw_complex *F_out;
//    fftw_complex *B_out;
    fftw_plan F, B;
    int N = X.size();
    
    F_out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)* N);
//    B_out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)* N);
    
//    cout << "input of the forward:\t";
//    print_pointer(&X[0], N);
    
    // setup the real to complex foward fftw call
    F = fftw_plan_dft_r2c_1d(N, reinterpret_cast<double*>(&X[0]), F_out, FFTW_ESTIMATE);
    // setup the complex to complex backward fftw call
    B = fftw_plan_dft_1d(N, F_out, reinterpret_cast<fftw_complex*>(&H[0]), FFTW_BACKWARD, FFTW_ESTIMATE);
//    B = fftw_plan_dft_1d(N, F_out, B_out, FFTW_BACKWARD, FFTW_ESTIMATE);
    
    fftw_execute(F);
    
//    cout << "output of the forward:\t";
//    print_complex(F_out, N);
    
    if(N%2==0){
        F_out[0][0] *= 0.5; F_out[N/2][0] *= 0.5;
        F_out[0][1] *= 0.5; F_out[N/2][1] *= 0.5;
    }
    else {
        F_out[0][0] *= 0.5;
        F_out[0][1] *= 0.5;
    }
    // normalize the effect of inverse FFT
    double scale = 2.0/N;
    for (int i = 0; i < N; i++){
        F_out[i][0] *= scale;
        F_out[i][1] *= scale;
    }
//    cout << "output of the forward after normalize: \t"
//    print_complex(F_out, N);
    
    fftw_execute(B);
//    cout << "output of the backward:\n";
//    print_complex(reinterpret_cast<fftw_complex*>(&H[0]), N);
    
    fftw_destroy_plan(F);
    fftw_destroy_plan(B);
    
//    for (int i = 0; i < N; i++){
//        H[i].real = B_out[i][0];
//        H[i].imag = B_out[i][1];
//    }
    fftw_free(F_out);
//    fftw_free(B_out);
}

////TODO: Need to make hilbert_DFT correct for non 2048 size case
////The number of complex elements to be transformed. This length must be one of:
////2**n
////f * 2**n, where f is 3, 5, or 15 and n is at least 3.
//const vDSP_Length n = 2048;//2048;  //should change at some point
//
//vector<double> hilbert_DFT(vector<double>& x){
//    
//    double even[n/2] = {}, odd[n/2] = {}, real[n] = {}, imag[n] = {};
//    for (int i = 0; i < floor(x.size()/2); i++){
//        even[i] = x.at(i*2);
//        odd[i] = x.at(i*2+1);
//        //        cout <<i<<'\t'<<even[i]<<'\t'<<x[2*i]<<endl;
//    }
//    //    cout << even[0] << endl;
//    
//    //setup DFT and inverse DFT
//    vDSP_DFT_SetupD forward = vDSP_DFT_zrop_CreateSetupD(NULL, n, vDSP_DFT_FORWARD);
//    vDSP_DFT_SetupD inverse = vDSP_DFT_zop_CreateSetupD(forward, n, vDSP_DFT_INVERSE);
//    //    //perform DFT
//    vDSP_DFT_ExecuteD(forward, even, odd, real, imag);
//    //zeroing for hilbert transform from results of DFT
//    real[0] *= 0.5; real[n/2] *= 0.5; imag[0] *= 0.5; imag[n/2] *= 0.5;
//    
//    double hilbertreal[n] = {}, hilbertimag[n] = {};
//    
//    vDSP_DFT_ExecuteD(inverse, real, imag, hilbertreal, hilbertimag);
//    double scale = 1.0/n; vDSP_vsmulD(hilbertimag, 1, &scale, hilbertimag, 1, 2*n);
//    vDSP_DFT_DestroySetupD(inverse);
//    vDSP_DFT_DestroySetupD(forward);
//    //    vector<double> xh(hilbertimag, hilbertimag + sizeof(hilbertimag)/sizeof(hilbertimag[0]));
//    vector<double> xh(hilbertimag, hilbertimag + x.size());
//    return xh;
//}
//
//

#endif
