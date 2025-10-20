#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>
using namespace std;

typedef struct VarElem{
    string var;
    double val;
} *VarElemType;

typedef struct {
    VarElemType item;
    int len;
}VarList;

double EvaluateExpression(string line);
string ReplaceVariable(string line, VarList &varlist);
void DealExpression();

#endif
