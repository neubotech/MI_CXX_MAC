//
//  main.cpp
//  MI
//
//  Created by Nan Tian on 6/19/15.
//  Copyright (c) 2015 Nan Tian. All rights reserved.
//
// support signal of "float" and "double"

//#include <iostream>
//#include <vector>
//#include <stdio.h>
//#include <algorithm>
//#include <math.h> //for "floor"
//#include <random> //for testing using random number generator
#include <complex>
#include "filtfilt.h"
#include "hilbert.h"
using namespace std;

template <typename T>
void print_vec(vector<T>& a){
    for (int i = 0; i<a.size(); i++){
        cout << i << '\t' << a.at(i) << "\n";
    }
    cout << endl << endl;
}

template <typename T>
vector<T> irange(T start, T end, T increment){
    int elements = floor((end-start)/increment);
    vector<T> v(elements);
    for (int i = 0; i < elements; i++) {
        v.at(i) = start + i*increment;
    }
    return v;
}

int main(){
    double a[] = {1, -2.6861574, 2.41965511, -0.73016535};
    double b[] = {0.00041655, 0.00124964, 0.00124964, 0.00041655};
    
    vector<double> vec_a(a, a+sizeof(a)/sizeof(a[0]));
    vector<double> vec_b(b, b+sizeof(b)/sizeof(a[0]));
    vector<double> vec_t = irange(-1.0, 1.0, 0.001);
    vector<double> vec_x(vec_t.size());
    vector<double> vec_xn(vec_t.size());
    vector<double> vec_z(vec_b.size(),0);
    
//    default_random_engine eng;
//    normal_distribution<double> randn(0.0, 1.0);
    for (int i = 0; i < vec_t.size(); i++) {
        vec_x.at(i) = sin(2* M_PI *vec_t.at(i)*.5 + 2);
//        vec_xn.at(i) = randn(eng) * 0.5 + vec_x.at(i);
    }
    
//    vector<double> vec_y = my_lfilter(vec_b, vec_a, vec_x, vec_z);
//    for (int i = 0; i < 10000; i++) {
//        filtfilt(vec_b, vec_a, vec_x, vec_z);
//    }
    
    vector<double> vec_xh(vec_x.size());
//    int test[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};//, 9, 10};
//    vector<double> vec_test(test, test+sizeof(test)/sizeof(test[0]));
//    for (int i = 0; i < 9; i++) {
//        vec_test[i] = sin(test[i]);
//    }
//    vector<double> vec_test=irange(0.0, 2048.0, 1.0);
//    for (int i = 0; i < 10000; i++){
//        vec_xh = hilbert_DFT(vec_x);
//    }
//    print_vec(vec_xh);
    
    vector<complex<double>> H(vec_x.size());
    for (int i = 0; i < 10000; i++) {
        hilbert_FFTW(vec_x, H);
    }
    print_vec(H);
    

    
//    
//    cout << "vec_t:\t";
////    print_vec(vec_t);
//    cout << "vec_x:\t";
////    print_vec(vec_x);
//    cout << "vec_xn:\t";
////    print_vec(vec_xn);
//
//    cout << "size fo a:\t" << (sizeof(a)/sizeof(a[0])) << endl << endl;
//    
//    cout << "vec_a";
//    print_vec(vec_a);
//    cout << "vec_b";
////    print_vec((vec_b));
    
}
