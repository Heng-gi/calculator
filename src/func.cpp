#include "../include/expression.h"
#include "../include/stack.h"
#include "../include/utils.h"
#include "../include/func.h"
#include "../include/linklist.h"
#include <cctype>
#include <string>
#include <list>
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

//初始化操作，约定第0个索引为空串（便于插入第一个func）
Status InitFuncList(FuncList &funclist){
    funclist.item=new FuncType[MaxFuncNum+1];
    if(!funclist.item) return ERROR;
    funclist.len=0;
    funclist.item[0].funcname="";
    funclist.item[0].expression="";
    return OK;
}

void DestoryFunclist(FuncList &funclist){
    if(funclist.item){
        delete[] funclist.item;
        funclist.item=nullptr;
    }
    funclist.len=0;
}

void ClearFuncList(FuncList &funclist){
    if(funclist.item){
        for(int i=1;i<=funclist.len;i++){
            funclist.item[i].funcname="";
            funclist.item[i].expression="";
            funclist.item[i].variable.clear();
        }
    }
    funclist.len=0;
}

//查询是否存在funcname，若存在，返回其索引值，且b取值TRUE；否则返回插入位置，且b取值FALSE
int LocateFunc(const FuncList &funclist, string func, bool &b){
    int i,m;
    for(i=funclist.len; (m=funclist.item[i].funcname.compare(func))>0; i--);
    if(m==0){
        b=true;
        return i;
    }
    else{
        b=false;
        return i+1;
    }
}

//在funclist的第i项上插入func, expression, variable
void InsertNewFunc(FuncList &funclist, int i, string func, string expression, const vector<string> &var){
    for(int j=funclist.len; j>=i; j--){
        funclist.item[j+1]=funclist.item[j];
    }
    funclist.item[i].funcname=func;
    funclist.item[i].expression=expression;
    funclist.item[i].variable=var;
    funclist.len++;
}

string SplitTwo(const string &line, string &second, char OPTR){
    string current;
    int i=0;
    for(char c:line){
        i++;
        if(OPTR!=' '){
            if(isspace(c)) continue;
        }
        if(c==OPTR){
            if(!current.empty()){
                break;
            }
        }
        else current+=c;
    }
    second=line.substr(i);
    return current;
}

string ToLower(const string &line){
    string str;
    for(char c:line){
        str+=tolower(c);
    }
    return str;
}

//result:DEF/RUN  func  variable  expression
//return 1 if DEF, 0 if run, -1 if other key words, -2 if error
Status SplitLine(const string &line, vector <string> &result){
    string temp;
    result.push_back(SplitTwo(line, temp, ' '));
    string instruct=ToLower(result[0]);
    if(instruct=="exit"||instruct=="clear"||instruct=="list"){
        return -1;
    }
    if(instruct=="run"){
        result.push_back(temp);
        return 0;
    }
    string temp2;
    result.push_back(SplitTwo(temp, temp2, '('));
    temp.clear();
    result.push_back(SplitTwo(temp2, temp, ')'));
    string expression;
    for(char c:temp){
        if(isspace(c)||c=='='||c==';') continue;
        else expression+=c;
    }
    if(!expression.empty()){
        result.push_back(expression);
        return 1;
    }
    return -2;
}

//划分变量或变量取值
void SplitVar(string vargroup, vector <string> &var){
    string current;
    int paren_num=0;
    for(char c:vargroup){
        if(isspace(c)) continue;
        if(c=='('){
            paren_num++;
            current+=c;
        }
        else if(c==')'){
            paren_num--;
            current+=c;
        }
        else if(c==',' && paren_num==0){
            if(!current.empty()){
                var.push_back(current);
                current.clear();
            }
        }
        else{
            current+=c;
        }
    }
    if(!current.empty()){
        var.push_back(current);
        current.clear();
    }
}

//expression应为创建的副本
void ReplaceValue(string &expression, const vector <string> &var, const vector <string> &replace){
    for(int i=0;i<var.size();i++){
        string replace_with_paren="("+replace[i]+')';
        expression=replaceAll(expression, var[i], replace_with_paren);
    }
}

//替换expression中的funcname,参数var为expression中的初始定义的变量名
//若expression有未知变量，则返回ERROR
Status ReplaceFunc(string &expression, const vector <string> &var, const FuncList &funclist){
    vector <string> original;
    vector <string> replaced;
    for(int i=0;i<expression.size();i++){
        char c=expression[i];
        string current;
        if(isspace(c)) continue;
        if ((c=='e'||c=='E') && i>0 && i<(expression.size()-1) && isdigit(expression[i-1]))
            continue;
        else if(isalpha(c)||c=='_'){
            current+=c;
            c=expression[++i];
            while(isalpha(c)||isdigit(c)||c=='_'){
                current+=c;
                c=expression[++i];
            }
            if(c=='('){ //current为funcname
                int index;
                bool b;
                index=LocateFunc(funclist,current,b);
                if(b){ //当前funcname存在于funclist中
                    string vargroup;
                    c=expression[++i];
                    int paren_num=1;
                    while (i<expression.size()){
                        vargroup+=c;
                        if(c=='('){
                            paren_num++;
                        }
                        else if(c==')'){
                            paren_num--;
                        }
                        if(!paren_num) break;
                        else c=expression[++i];
                    }
                    if(!vargroup.empty() && vargroup.back()==')') vargroup.pop_back();
                    original.push_back(current+'('+vargroup+')');
                    current.clear();
                    vector <string> replace;
                    SplitVar(vargroup, replace);
                    string funcexpression=funclist.item[index].expression;
                    ReplaceValue(funcexpression, funclist.item[index].variable, replace);
                    replaced.push_back('('+funcexpression+')');
                }
                else{
                    cout<<"错误：当前函数"<<current<<"未定义"<<endl;
                    current.clear();
                    return ERROR;
                }
            }
            else{
                i--;
                bool varhave=false;
                for(int j=0;j<var.size();j++){
                    if(current==var[j]){
                        varhave=true;
                        break;
                    }
                }
                if(varhave){
                    current.clear();
                    continue;
                }
                else{
                    cout<<"错误：当前变量"<<current<<"未定义"<<endl;
                    current.clear();
                    return ERROR;
                }
            }
        }
    }
    ReplaceValue(expression,original,replaced);
    return OK;
}

void printAllFunctions(const FuncList &funclist) {
    if (funclist.len == 0) {
        printf("当前没有定义任何函数\n");
        return;
    }
    printf("\n===== 已定义函数列表 =====\n");
    for (int i = 1; i <= funclist.len; i++) {
        const FuncType &func = funclist.item[i];
        printf("%d. %s(", i, func.funcname.c_str());
        for (size_t j = 0; j < func.variable.size(); j++) {
            if (j > 0) printf(",");
            printf("%s", func.variable[j].c_str());
        }
        printf(") = %s\n", func.expression.c_str());
    }
    printf("==========================\n");
}

Status ReplaceFuncStop(const string &str){
    bool havealp=true;
    for(int i=0;i<str.size();i++){
        if ((str[i]=='e'||str[i]=='E') && i>0 && i<(str.size()-1) && isdigit(str[i-1])) continue;
        if (isalpha(str[i])||str[i]=='_'){
            havealp=false;
            break;
        }
    }
    return havealp;
}

void DealFunc(FuncList &funclist){
    while(1){
        string line;
        getline(cin, line);
        vector <string> split_result;
        int instruct=SplitLine(line, split_result);
        if(instruct<0){  
            string keywords=ToLower(split_result[0]);
            if(keywords=="clear"){
                ClearFuncList(funclist);
            }
            else if(keywords=="list"){
                printAllFunctions(funclist);
            }
            else if(keywords=="exit"){
                cout<<"已退出函数编程模式"<<endl;
                break;
            }
            else{
                cout<<"命令错误，请重新输入"<<endl;
            }
        }
        else if(instruct>0){  //def
            vector <string> var;
            SplitVar(split_result[2],var);
            bool func_exist;
            int index=LocateFunc(funclist, split_result[1], func_exist);
            if(func_exist){
                funclist.item[index].expression=split_result[3];
                funclist.item[index].variable=var;
            }
            else{
                InsertNewFunc(funclist, index, split_result[1], split_result[3], var);
            }
        }
        else{
            vector <string> var;
            bool undefined_var=false;
            while(1){
                int t=ReplaceFunc(split_result[1],var,funclist);
                if(t==ERROR){
                    undefined_var=true;
                    break;
                }
                if(ReplaceFuncStop(split_result[1])){
                    break;
                }
            }
            if(undefined_var) continue;
            double result=EvaluateExpression(split_result[1]);
            cout<<"运算结果为："<<result<<endl;
        }
    }
}