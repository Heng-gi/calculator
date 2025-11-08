#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>
#include <vector>
#include "BiTree.h"
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
vector<string> GetPostfix(string line);
BiTree<string>* PostfixToBiTree(vector<string> Postfix);
void DealExpression();
#endif
