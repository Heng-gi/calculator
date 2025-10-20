#include "../include/extreme_point.h"

vector<double> Gradient(const function<double(const vector<double>&)> &F, const vector<double> &x, double h){
    vector<double> g(x.size());
    for(int i=0;i<x.size();i++){
        vector<double> xh=x;
        xh[i]+=h;
        g[i]=(F(xh)-F(x))/h;
    }
    return g;
}

void DealExtremePoint(){
    cout<<"请输入函数："<<endl;
    string line;
    getline(cin,line);
    vector<string> lines;
    lines.push_back(line);
    map<string,double> varlist;
    vector<function<double(const vector<double>&)>> f=BuildFuncVector(lines,varlist);
    cout<<"请输入初始变量值:"<<endl;
    vector<double> x0;
    for(auto &[key,val]:varlist){
        cout<<key<<"：";
        double x;
        scanf("%lf",&x);
        x0.push_back(x);
    }  
    vector<function<double(const vector<double>&)>> F;
    for(int i=0;i<x0.size();i++){
        int idx=i;
        F.push_back([=](const vector<double> &x){
            vector<double> g=Gradient(f[0],x);
            return g[idx];
        });
    }
    vector<double> res(x0.size());
    res=NewtonRaphson(F,x0);
    int i=0;
    for(auto &[key,val]:varlist){
        cout<<key<<"\t"<<res[i]<<endl;
        i++;
    }
    cout<<"函数值为"<<f[0](res)<<endl;
}