#ifndef EXTREME_POINT_H
#define EXTREME_POINT_H

#include "../include/non_linear_equation.h"
#include <vector>
#include <string>
#include <iostream>
#include <functional>

using namespace std;

vector<double> Gradient(const function<double(const vector<double>&)> &F, const vector<double> &x, double h=1e-6);
void DealExtremePoint();

#endif