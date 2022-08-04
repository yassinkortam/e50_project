//
//  linode_input.h
//  ENGR 50 Project
//
//  Created by Yassin Kortam on 12/12/21.
//

#include <iostream>
#include <vector>
#include <string>


using namespace std;


#ifndef linode_input_h
#define linode_input_h

class linode_input{
public:
    string raw_equation;
    string variable;
    vector <double> coeffecients;
    vector <int> orders;
    int order;
    
    linode_input(string my_equation);
    
private:
    void input_equation(string raw_equation);
    bool is_in(char thing, string list);
    void clean_vector(vector <string> &myvector);
    int max(vector <int> myvector);
};

linode_input::linode_input(string my_equation){
    raw_equation = my_equation;
    input_equation(my_equation);
    order = max(orders);
}

void linode_input::input_equation(string raw_equation){
    
    string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string numbers = "0123456789";
    
    vector <string> equation;
    vector <string> clean_equation;
    
    string term = "";
    string input;
    string coeffecient;
    string order;
    string prevvar;
    
    int highest_order;
    
    long number_of_terms;
    
    for(int i=0; i<raw_equation.length(); i++){
        if(raw_equation[i] != '+' && !isspace(raw_equation[i])){
            term += raw_equation[i];
            if(i == raw_equation.length() -1){
                equation.push_back(term);
            }
        }
        else{
            equation.push_back(term);
            term = "";
        }
    }
        
    number_of_terms = equation.size();
    
    //find the dependent variable name
    int i=0;
    while (!is_in(raw_equation[i],letters)){
        i++;
    };
    if (is_in(raw_equation[i],letters)){
        while (is_in(raw_equation[i],letters)){
            variable += raw_equation[i];
            i++;
        }
    }
    
    //remove equal sign and variables from the equation
    for (int i=0; i<number_of_terms; i++){
        for(int j=0; j<equation[i].length(); j++){
            if (equation[i][j] == '='){
                equation[i].erase(equation[i].begin() + j);
                cout<<equation[i]<<endl;
            }
            if (is_in(equation[i][j], letters)){
                equation[i].erase(equation[i].begin() + j);
            }
        }
    }
    
    //removing all the empty vector cells
    clean_vector(equation);

    //creating a vector with all the coeffecients
    for (int i=0; i<equation.size(); i++){
        if (equation[i] != "-"){
            for(int j=0; j<equation[i].length(); j++){
                if (is_in(equation[i][j],numbers)){
                    coeffecient += equation[i][j];
                }
                else{
                    while(equation[i][j] != ')' && j<equation[i].length()){
                        if (is_in(equation[i][j],numbers)){
                            order += equation[i][j];
                        }
                        j++;
                    }
                }
                
            }
            if(equation[i-1] == "-"){
                coeffecients.push_back(-1*stod(coeffecient));
            }
            else{
                if (coeffecient != ""){
                    coeffecients.push_back(stod(coeffecient));
                }
                else{
                    coeffecients.push_back(1);
                }
            }
            
            if(order != ""){
                orders.push_back(stoi(order));
            }
            coeffecient = "";
            order = "";
        }
    }
    
    highest_order = max(orders);
    
    cout<<"\n*****************************"<<endl;
    cout<<"Coeffecients:"<<endl;
    for(int i=0; i<coeffecients.size(); i++){
        cout<<coeffecients[i]<<endl;
    }
    cout<<"\n*****************************"<<endl;
    cout<<"Orders:"<<endl;
    for(int i=0; i<orders.size(); i++){
        cout<<orders[i]<<endl;
    }
    

}
    

bool linode_input::is_in(char thing, string list){
    for (int i=0; i<list.length(); i++){
        if (thing == list[i]){
            return true;
        }
    }
    return false;
}

void linode_input::clean_vector(vector <string> &myvector){
    vector <string> clean_vector;
    for (int i=0; i<myvector.size(); i++){
        if(myvector[i] != ""){
            clean_vector.push_back(myvector[i]);
        }
    }
    
    myvector = clean_vector;
}

int linode_input::max(vector <int> myvector){
    if (myvector.size() > 0){
        int max = myvector[0];
        for(int i=1; i<myvector.size(); i++){
            if (myvector[i] >= max){
                max = myvector[i];
            }
        }
        return max;
    }
    else{
        return 0;
    }
    
}

#endif /* linode_input_h */

