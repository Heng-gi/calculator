#ifndef FUNC_H
#define FUNC_H

#include "linklist.h"
#include <string>
#include <cctype>
#include <list>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

#define MaxFuncNum 100

//函数索引项
typedef struct FuncType{
    string funcname;
    string expression;
    vector<string> variable;   
}FuncType;
//函数表（有序表）
typedef struct FuncList{
    FuncType *item;
    int len;
}FuncList;

//初始化操作，约定第0个索引为空串（便于插入第一个func）
Status InitFuncList(FuncList &funclist);
void DestoryFunclist(FuncList &funclist);
void ClearFuncList(FuncList &funclist);
//查询是否存在funcname，若存在，返回其索引值，且b取值TRUE；否则返回插入位置，且b取值FALSE
int LocateFunc(const FuncList &funclist, string func, bool &b);
//在funclist的第i项上插入func, expression, variable
void InsertNewFunc(FuncList &funclist, int i, string func, string expression, const vector<string> &var);
string SplitTwo(const string &line, string &second, char OPTR);
string ToLower(const string &line);
//result:DEF/RUN  func  variable  expression
//return 1 if DEF, 0 if run, -1 if exit, -2 if error
Status SplitLine(const string &line, vector <string> &result);
//划分变量或变量取值
void SplitVar(string vargroup, vector <string> &var);
//expression应为创建的副本
void ReplaceValue(string &expression, const vector <string> &var, const vector <string> &replace);
//替换expression中的funcname,参数var为expression中的初始定义的变量名
//若expression有未知变量，则返回ERROR
Status ReplaceFunc(string &expression, const vector <string> &var, const FuncList &funclist);
void printAllFunctions(const FuncList &funclist);
void DealFunc(FuncList &funclist);


#endif
