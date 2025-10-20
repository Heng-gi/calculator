#ifndef LINEAR_EQUATION_H
#define LINEAR_EQUATION_H

#include "func.h"
#include "expression.h"
#include "matrix.h"
#include <iostream>
#include <string>
#include <map>
#include <regex>
using namespace std;

string NormalizeEquation(const string &line);
void ExtractVar(const string &line, map<string,double> &varlist);
//函数EvaluateExpression的map变量映射版本
double EvaluateExpressionMap(const string &line, const map<string,double> &varlist);
void GetCoef(const string &line, map<string,double> &varlist);
void DealLinearEquation();

#endif