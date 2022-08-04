//
//  main.cpp
//  ENGR 50 Project
//
//  Created by Yassin Kortam on 12/10/21.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>
#include "linode.h"
#include "linode_input.h"
#include "project_case.h"

using namespace std;

int main(int argc, const char * argv[]) {
    //vector <double> myconditions = {0,9.858,11.397};
    bool inputting = true;
    
    while (inputting){
        vector <double> myconditions;
        vector <double> mysolution;
        string myequation, output;
        double h = 0.00001;
        double input;
        int solution_size;
        
        cout<<"\n********* Inputs *********"<<endl;
        cout<<"\nEnter a linear nth order differential equation in the form Cnvariable(order) +....= B"<<endl;
        //save the equation to be worked with
        cin.clear();
        getline(cin, myequation);
        linode_input myinput(myequation);
        cout<<"\nEnter initial conditions (roughly equivalent for small h):"<<endl;
        for(int i=0; i<myinput.order; i++){
            cout<<myinput.variable<<"("<<i*h<<") = ";
            cin>>input;
            myconditions.push_back(input);
        }
        cout<<"\nWhat should the solution span?"<<endl<<"0<x<";
        cin>>solution_size;
        cout<<"\nEnter output location:"<<endl;
        cin>>output;
        
        linode solution(myinput, myconditions, h, solution_size);
        mysolution = solution.f;
        
        if (solution.solved){
            cout<<"\n********* Simple Solution *********\n"<<endl;
            cout<<setw(10)<<"x"<<setw(10)<<myinput.variable<<"(x)"<<endl;
            for (int i=0; i<mysolution.size(); i += 1/h){
                cout<<setw(10)<<myinput.variable<<"("<<round(i*h)<<")"<<setw(10)<<mysolution[i]<<endl;
            }
            cout<<"\n******************"<<endl;
            cout<<"Max: "<<solution.max<<endl;
            cout<<"Min: "<<solution.min<<endl;

            inputting = false;
        }
        else{
            cout<<"\n********* Input error, try again *********"<<endl;
            continue;
        }
        
        //for project given case only
        if (matching(myinput.coeffecients, {1,2,5,50}) && matchingint(myinput.orders,{2,1,0})){
            project_case(myinput,solution,myconditions,h,solution_size,output);
        }
        else{
            ofstream write(output.c_str());
            write<<setw(5)<<"X"<<","<<setw(5)<<"F"<<endl;
            for (int i=0; i<mysolution.size(); i += 0.1/h){
                write<<setw(5)<<i*h<<","<<setw(5)<<mysolution[i]<<endl;
            }
            write.close();
        }
    }
    return 0;
}


