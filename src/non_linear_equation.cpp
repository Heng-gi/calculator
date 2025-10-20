#include "../include/non_linear_equation.h"

vector<vector<double>> Jacobian(const vector<function<double(const vector<double>&)>> &F,const vector<double> &x, double h){
    size_t m=F.size();
    size_t n=x.size();
    vector<vector<double>> J(m,vector<double>(n));
    for(int j=0;j<n;j++){
        vector<double> xh=x;
        xh[j]+=h;
        for(int i=0;i<m;i++){
            J[i][j]=(F[i](xh)-F[i](x))/h;
        }
    }
    return J;
}

//顺便ExtractVar map
vector<function<double(const vector<double>&)>> BuildFuncVector(const vector<string> lines, map<string,double> &varlist){
    vector<function<double(const vector<double>&)>> F;
    vector<string> ss;
    for(auto line:lines){
        string s=NormalizeEquation(line);
        ExtractVar(s,varlist);
        ss.push_back(s);
    }
    vector<string> keys;
    for (auto &[k, v] : varlist)
        keys.push_back(k);
    for (auto &s : ss) {
        F.push_back([s,keys](const vector<double> &x) {
            map<string,double> local_var;
            for (int i = 0; i < keys.size(); i++)
                local_var[keys[i]] = x[i];
            return EvaluateExpressionMap(s, local_var);
        });
    }
    return F;
}

vector<double> NewtonRaphson(const vector<function<double(const vector<double>&)>> &F, vector<double> x0, double eps, int max_iter){
    for(int iter=0;iter<max_iter;iter++){
        vector<double> Fx;
        double diff=0;
        for(int i=0;i<F.size();i++){
            Fx.push_back(F[i](x0));
            diff+=Fx.back()*Fx.back();
        }
        if(sqrt(diff)<eps){
            return x0;
        }
        vector<vector<double>> f;
        f.push_back(Fx);
        Matrix fm(f);
        vector<vector<double>> J=Jacobian(F,x0);
        Matrix j(J);
        Matrix dx=j.inverse()*fm.transpose();
        for(int i=0;i<x0.size();i++){
            x0[i]-=dx.a[i][0];
        }
    }
    cout<<"警告：未收敛，最后迭代值为："<<endl;
    return x0;
}

void DealNonLinearEquation(){
    vector<string> lines;
    while(1){
        string line;
        getline(cin,line);
        if(line.empty()){
            break;
        }
        lines.push_back(line);
    }
    map<string,double> varlist;
    vector<function<double(const vector<double>&)>> F=BuildFuncVector(lines,varlist);
    int n=varlist.size();
    vector<double> x0(n,4);
    vector<double> res(n);
    res=NewtonRaphson(F,x0);
    int i=0;
    for(auto &[key,val]:varlist){
        cout<<key<<"\t"<<res[i]<<endl;
        i++;
    }
}