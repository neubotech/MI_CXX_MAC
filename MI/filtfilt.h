//
//  filtfilt.h
//  MI
//
//  Created by Nan Tian on 6/22/15.
//  Copyright (c) 2015 Nan Tian. All rights reserved.
//

#ifndef MI_filtfilt_h
#define MI_filtfilt_h

//
//  main.cpp
//  MI
//
//  Created by Nan Tian on 6/19/15.
//  Copyright (c) 2015 Nan Tian. All rights reserved.
//
// support signal of "float" and "double"

#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <math.h> //for "floor"
//#include <random> //for testing using random number generator
#include <complex>
using namespace std;

//#include "transform.h"

template <typename T>
vector<T> filtfilt(vector<T>& b, vector<T>& a, vector<T>& X, vector<T>& z){
    if (b.size() != z.size()) {
        perror("my_lfilter:\t the size of z (inital value) were different from the size of b");
        exit(0);
    }
    z.push_back(0.0);
    for (int i = 0; i < a.size(); i++) {
        a.at(i) = a.at(i)/a.at(0);
    }
    for (int i = 0; i < b.size(); i++) {
        b.at(i) = b.at(i)/a.at(0);
    }
    vector<T> Y(X.size(),0);
    for (int m = 0; m < Y.size(); m++) {
        Y.at(m) = b.at(0) * X.at(m) + z.at(0);
        for (int i = 1; i < b.size(); i++) {
            z.at(i - 1) = b.at(i) * X.at(m) + z.at(i) - a.at(i) * Y.at(m);
        }
    }
    z.pop_back();
    return Y;
}

//template <typename T>
//void print_vec(vector<T>& a){
//    for (int i = 0; i<a.size(); i++){
//        cout << '\t' << a.at(i);
//    }
//    cout << endl << endl;
//}
//
//template <typename T>
//vector<T> irange(T start, T end, T increment){
//    int elements = floor((end-start)/increment);
//    vector<T> v(elements);
//    for (int i = 0; i < elements; i++) {
//        v.at(i) = start + i*increment;
//    }
//    return v;
//}

//int main(){
//    double a[] = {1, -2.6861574, 2.41965511, -0.73016535};
//    double b[] = {0.00041655, 0.00124964, 0.00124964, 0.00041655};
//    
//    vector<double> vec_a(a, a+sizeof(a)/sizeof(a[0]));
//    vector<double> vec_b(b, b+sizeof(b)/sizeof(a[0]));
//    vector<double> vec_t = irange(-1.0, 1.0, 0.001);
//    vector<double> vec_x(vec_t.size());
//    vector<double> vec_xn(vec_t.size());
//    vector<double> vec_z(vec_b.size(),0);
//    
//    default_random_engine eng;
//    normal_distribution<double> randn(0.0, 1.0);
//    for (int i = 0; i < vec_t.size(); i++) {
//        vec_x.at(i) = sin(2* M_PI *vec_t.at(i)*.5 + 2);
//        vec_xn.at(i) = randn(eng) * 0.5 + vec_x.at(i);
//    }
//    
//    //    vector<double> vec_y = my_lfilter(vec_b, vec_a, vec_x, vec_z);
//    for (int i = 0; i < 1000; i++) {
//        my_filtfilt(vec_b, vec_a, vec_x, vec_z);
//    }
//    //    print_vec(vec_y);
//    
//    //
//    //    cout << "vec_t:\t";
//    ////    print_vec(vec_t);
//    //    cout << "vec_x:\t";
//    ////    print_vec(vec_x);
//    //    cout << "vec_xn:\t";
//    ////    print_vec(vec_xn);
//    //
//    //    cout << "size fo a:\t" << (sizeof(a)/sizeof(a[0])) << endl << endl;
//    //
//    //    cout << "vec_a";
//    //    print_vec(vec_a);
//    //    cout << "vec_b";
//    ////    print_vec((vec_b));
//    
//}

#endif
