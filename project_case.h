//
//  project_case.h
//  ENGR 50 Project
//
//  Created by Yassin Kortam on 12/14/21.
//
//error analysis wrt h for project example only

#ifndef project_case_h
#define project_case_h


#endif /* project_case_h */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>
#include "linode.h"
#include "linode_input.h"

using namespace std;

void project_case(linode_input myinput, linode solution, vector <double> myconditions, double h, int solution_size, string output);
vector <vector<double>> err_of_h(linode_input input, vector <double> cond, double h, int size, int num_terms);
bool matching(vector <double> v1, vector <double> v2);
bool matchingint(vector <int> v1, vector <int> v2);

void project_case(linode_input myinput, linode solution, vector <double> myconditions, double h, int solution_size, string output){
    vector <double> mysolution = solution.f;
    double act, err;
    ofstream write(output.c_str());
    //
    //pointer/heap area example for project. arrays are not practical for my computation use case.
    double *copysolution = new double[mysolution.size()];
    //
    write<<setw(5)<<"X"<<","<<setw(5)<<"F"<<","<<setw(5)<<"Act"<<","<<setw(5)<<"%E"<<endl;
    for (int i=0; i<mysolution.size(); i += 0.1/h){
        
        //Analytic solution for project case only:
        copysolution[i] = mysolution[i];
        act = 10 - exp(-i*h)*(10*cos(2*i*h) + 5*sin(2*i*h));
        err = abs((copysolution[i] - act)/copysolution[i])*100;
        //
        
        write<<setw(5)<<i*h<<","<<setw(5)<<mysolution[i]<<","<<setw(5)<<act<<","<<setw(5)<<err<<endl;
    }
    write.close();
    
    //***********************************************************************************************
    //Error Analysis output for project example
    double err_size;
    
    cout<<"\n*******Error Analysis********"<<endl;
    cout<<"\nHow many terms would you like?"<<endl;
    cin>>err_size;
    cout<<"\nEnter output location:"<<endl;
    cin>>output;
    ofstream write2(output.c_str());
    vector <vector<double>> err_wrt_h = err_of_h(myinput, myconditions, h, solution_size, err_size);
    
    write2<<setw(5)<<"h"<<setw(5)<<","<<"avg%E"<<endl;
    for(int i=0; i<err_wrt_h.size(); i++){
        write2<<setw(5)<<err_wrt_h[i][0]<<setw(5)<<","<<err_wrt_h[i][1]<<endl;
    }
    write2.close();
}


vector <vector<double>> err_of_h(linode_input input, vector <double> cond, double h, int size, int num_terms){
    vector <vector<double>> error_wrt_h;
    vector <double> row;
    double temph = 1.0;
    double act;
    double err=0;
    double increment_h = 1.0/(num_terms);
    for (int j = 0; j<num_terms; j++){
        linode tsolution(input, cond, temph, size);
        for (int i=cond.size(); i<tsolution.f.size(); i += 1/temph){
            act = 10 - exp(-i*temph)*(10*cos(2*i*temph) + 5*sin(2*i*temph));
            err += (100*abs(tsolution.f[i] - act))/tsolution.f[i];
        }
        err = err/tsolution.f.size();
        error_wrt_h.push_back({temph, err});
        temph -= increment_h;
        err = 0;
    }
    return error_wrt_h;
}

bool matching(vector <double> v1, vector <double> v2){
    vector <bool> match;
    if (v1.size() == v2.size()){
        for (int i=0; i<v1.size(); i++){
            for (int j=0; j<v2.size(); j++){
                if (v1[i] == v2[j]){
                    match.push_back(true);
                }
            }
        }
        if (match.size() == v1.size()){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

bool matchingint(vector <int> v1, vector <int> v2){
    vector <bool> match;
    if (v1.size() == v2.size()){
        for (int i=0; i<v1.size(); i++){
            for (int j=0; j<v2.size(); j++){
                if (v1[i] == v2[j]){
                    match.push_back(true);
                }
            }
        }
        if (match.size() == v1.size()){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}
