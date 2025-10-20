#ifndef NON_LINEAR_EQUATION_H
#define NON_LINEAR_EQUATION_H

#include "linear_equation.h"
#include "matrix.h"
#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

vector<vector<double>> Jacobian(const vector<function<double(const vector<double>&)>> &F,const vector<double> &x, double h=1e-6);
vector<function<double(const vector<double>&)>> BuildFuncVector(const vector<string> lines, map<string,double> &varlist);
vector<double> NewtonRaphson(const vector<function<double(const vector<double>&)>> &F, vector<double> x0, double eps=1e-5, int max_iter=100);
void DealNonLinearEquation();


#endif