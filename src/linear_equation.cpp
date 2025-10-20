#include "../include/linear_equation.h"

string NormalizeEquation(const string &line){
    size_t e=line.find('=');
    string left=(e!=string::npos)? line.substr(0,e):line;
    string right=(e!=string::npos)? line.substr(e+1):"0";
    string expr="("+left+")-("+right+")";
    return expr;
}

void ExtractVar(const string &line, map<string,double> &varlist){
    regex var_pattern("\\b(?!e\\b)[a-zA-Z_][a-zA-Z0-9_]*\\b");
    sregex_iterator iter(line.begin(),line.end(),var_pattern);
    sregex_iterator end;
    while(iter!=end){
        varlist[(*iter)[0]]=0;
        iter++;
    }
}

//函数EvaluateExpression的map变量映射版本
double EvaluateExpressionMap(const string &line, const map<string,double> &varlist){
    string tmp=line;
    vector<string> var;
    vector<string> replace;
    for(auto &[key,value]:varlist){
        var.push_back(key);
        replace.push_back(to_string(value));
    }
    ReplaceValue(tmp, var, replace);
    return EvaluateExpression(tmp);
}

void GetCoef(const string &line, map<string,double> &varlist){
    string tmp=line;
    vector<string> var;
    vector<string> replace;
    for(auto &[key,value]:varlist){
        var.push_back(key);
        replace.push_back("0");
    }
    ReplaceValue(tmp, var, replace);
    double val0 = EvaluateExpression(tmp);
    for(int index = 0; index < var.size(); index++){
        for(int i = 0; i < replace.size(); i++){
            replace[i] = "0";
        }
        replace[index] = "1";
        string tmp2 = line;
        ReplaceValue(tmp2, var, replace);
        double val1 = EvaluateExpression(tmp2);
        varlist[var[index]] = val1 - val0;
    }
    varlist["const"] = val0;
}

void DealLinearEquation(){
    vector<string> lines;
    vector<string> tmp;
    while(1){
        string line;
        getline(cin,line);
        if(line.empty()){
            break;
        }
        lines.push_back(line);
    }
    map<string,double> varlist;
    size_t m=lines.size();
    for(string line:lines){
        string s=NormalizeEquation(line);
        ExtractVar(s,varlist);
        tmp.push_back(s);
    }
    size_t n=varlist.size();
    vector<vector<double>> A;
    vector<double> B;
    for(string s:tmp){
        GetCoef(s,varlist);
        vector<double> row;
        for(auto &[key,value]:varlist){
            if(key!="const"){
                row.push_back(value);
            }
            else{
                B.push_back(-value);
            }
        }
        A.push_back(row);
    }
    Matrix Am(A);
    vector<vector<double>> Bv;
    Bv.push_back(B);
    Matrix Bm(Bv);
    Matrix x(n,1);
    x=Am.inverse()*Bm.transpose();
    int i=0;
    cout<<"方程（组）解为："<<endl;
    for(auto &[key,value]:varlist){
        if(key!="const"){
            cout<<key<<"\t"<<x.a[i][0]<<endl;
            i++;
        }
    }
}