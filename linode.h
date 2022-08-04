//
//  linode.h
//  ENGR 50 Project
//
//  Created by Yassin Kortam on 12/12/21.
//

#ifndef linode_h
#define linode_h

#include <cmath>
#include <string>
#include <vector>
#include "linode_input.h"

using namespace std;

class linode{
public:
    bool solved;
    int solution_size;
    double h;
    double min;
    double max;
    //Lin ODE Properties
    vector <double> coeffecients;
    vector <int> orders;
    vector <double> conditions;
    linode(linode_input myequation, vector<double> myconditions, double myh, int mysize);
    
    //Lin ODE Solution
    vector <double> f;
    
private:
    void clean_vector(vector <int> &myvector);
    double yassin_derivative(int i);
    double derivative(int order, int i);
    double yd_correction(int order, int point);
    void find_min();
    void find_max();
    bool solve();
};

linode::linode(linode_input myequation, vector<double> myconditions, double myh, int mysize){
    coeffecients = myequation.coeffecients;
    orders = myequation.orders;
    conditions = myconditions;
    h = myh;
    solution_size = (1/h)*mysize;
    for (int i=0; i<conditions.size(); i++){
        f.push_back(conditions[i]);
    }
    solved = solve();
    find_min();
    find_max();
}

bool linode::solve(){
    double ydcorrection, numerator, denominator, b=coeffecients[coeffecients.size() -1], c0=0;
    
    for (int i=0; i<orders.size(); i++){
        if (orders[i] == 0){
            c0 = coeffecients[i];
        }
        else{
            c0 = 0;
        }
    }
    
    if (coeffecients.size() - 1 != orders.size()){
        return false;
    }
    
    clean_vector(orders);
    coeffecients.pop_back();
    
    //loop that creates the solution vector
    for (int i=conditions.size(); i<solution_size; i++){
        
        ydcorrection = 0;
        numerator = b;
        denominator = c0;
        //loop that finds the yd correction for each entry of solution vector
        for(int j=0; j<orders.size(); j++){
            ydcorrection += coeffecients[j]*yd_correction(orders[j], i)/pow(h,orders[j]);
            //constructing the numerator part 1
            numerator -= coeffecients[j]*derivative(orders[j], i)/pow(h,orders[j]);
            //reconstructing denominator based on yd corrections
            denominator += coeffecients[j]/pow(h,orders[j]);
        }
        //final numerator;
        numerator -= ydcorrection;
        //cout<<numerator<<"/"<<denominator<<endl;
        if(denominator != 0){
            f.push_back(numerator/denominator);
        }
        else{
            f.push_back(NULL);
        }
    }
    
    return true;
}

double linode::yassin_derivative(int i){
    double yd;
    if (i >= 1){
        yd = -f[i-1];
    }
    else{
        yd = NULL;
    }
    return yd;
}

double linode::derivative(int order, int i){
    vector<double> d;
    vector<double> d2;
    vector<double> yd;
    
    for (int j=order; j>0; j--){
        yd.push_back(yassin_derivative(i-j));
    }
            
    if (order > 1){
        if (i >= order){
            d = yd;
            for(int j=0; j<order-1; j++){
                for(int k=1; k<d.size(); k++){
                    d2.push_back((d[k] - d[k-1]));
                }
                d = d2;
                d2 = {};
            }
            return d[0];
        }
        else{
            return NULL;
        }
        
    }
    else{
        return yassin_derivative(i);
    }
}

double linode::yd_correction(int order, int point){
    double ydcorrection=0;
    for(int j=1; j<order; j++){
        ydcorrection += pow(-1,j)*(order - j)*f[point - j];
    }
    return ydcorrection;
}

void linode::clean_vector(vector <int> &myvector){
    vector <int> clean_vector;
    for (int i=0; i<myvector.size(); i++){
        if(myvector[i] != 0){
            clean_vector.push_back(myvector[i]);
        }
    }
    myvector = clean_vector;
}

void linode::find_min(){
    double tempmin = f[0];
    for (int i=1; i<f.size(); i++){
        if (f[i] < tempmin){
            tempmin = f[i];
        }
    }
    min = tempmin;
}

void linode::find_max(){
    double tempmax = f[0];
    for (int i=1; i<f.size(); i++){
        if (f[i] > tempmax){
            tempmax = f[i];
        }
    }
    max = tempmax;
}

#endif /* linode_h */



