#include "../include/expression.h"
#include "../include/stack.h"
#include "../include/utils.h"
#include "../include/BiTree.h"
#include <cctype>
#include <cmath>
#include <stack>
#include <iostream>
#include <vector>
using namespace std;

//显示Operator间的优先级大小
static char Precede(char a, char b) {
    int precedence[8][8] = {
        // +  -  *  / ^ (  )  #
        {1, 1, -1, -1, -1, -1, 1, 1}, // +
        {1, 1, -1, -1, -1, -1, 1, 1}, // -
        {1, 1, 1, 1, -1, -1, 1, 1},   // *
        {1, 1, 1, 1, -1, -1, 1, 1},   // /
        {1, 1, 1, 1, -1, -1, 1, 1},// ^
        {-1, -1, -1, -1, -1, -1, 0, -2}, // (
        {1, 1, 1, 1, -1, -2, 1, 1},   // )
        {-1, -1, -1, -1, -1, -1, -2, 0} // #
    };
    int idx1, idx2;
    switch (a) {
        case '+': idx1 = 0; break;
        case '-': idx1 = 1; break;
        case '*': idx1 = 2; break;
        case '/': idx1 = 3; break;
        case '^': idx1 = 4; break;
        case '(': idx1 = 5; break;
        case ')': idx1 = 6; break;
        case '#': idx1 = 7; break;
        default: idx1 = 7; break;
    }
    switch (b) {
        case '+': idx2 = 0; break;
        case '-': idx2 = 1; break;
        case '*': idx2 = 2; break;
        case '/': idx2 = 3; break;
        case '^': idx2 = 4; break;
        case '(': idx2 = 5; break;
        case ')': idx2 = 6; break;
        case '#': idx2 = 7; break;
        default: idx2 = 7; break;
    }
    int val = precedence[idx1][idx2];
    if (val == 1) return '>';
    else if (val == 0) return '=';
    else if (val == -1) return '<';
    else return '#';
}

//进行四则运算
static double Operate(double a, char theta, double b) {
    switch (theta) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a,b);
    }
    return 0.0;
}

double EvaluateExpression(string line){
    if(line.back()!='#') line.push_back('#');
    SqStack<char> OPTR;
    OPTR.Init();
    OPTR.Push('#');
    SqStack<double> OPND;
    OPND.Init();
    bool possibleminus=true;
    string currentnumber;
    for(int i=0;i<line.size();i++){
        char c=line[i];
        if(c!='#' || OPTR.GetTop()!='#'){
            if((c=='-' || c=='+') && possibleminus){
                OPND.Push(0);
                OPTR.Push(c);
                possibleminus=false;
                continue;
            }
            possibleminus=false;
            if(isdigit(c) || c=='.'){
                currentnumber+=c;
                continue;
            }
            else if(((c=='e' || c=='E') && (!currentnumber.empty()))){
                currentnumber+=c;
                if(i+1<line.size() && line[i+1]=='-'){
                    currentnumber+=line[i+1];
                    i++;
                }
            }
            else{
                if(!currentnumber.empty()){
                    OPND.Push(stod(currentnumber));
                    currentnumber.clear();
                }
                if(c=='(') possibleminus=true;
                switch (Precede(OPTR.GetTop(),c)){
                    case '<':
                        OPTR.Push(c);
                        break;
                    case '=':
                        char x;
                        OPTR.Pop(x);
                        break;
                    case '>':
                        char theta;
                        OPTR.Pop(theta);
                        double a,b;
                        OPND.Pop(b);
                        OPND.Pop(a);
                        OPND.Push(Operate(a,theta,b));
                        i--;
                        break;
                }
            }
        }
        else break;
    }
    double result=OPND.GetTop();
    return result;
}

string ReplaceVariable(string line, VarList &varlist){
    string str=line;
    for(int i=0;i<line.size();i++){
        char c=line[i];
        string variable;
        if(isspace(c)) continue;
        if ((c=='e'||c=='E') && i>0 && i<(line.size()-1) && isdigit(line[i-1]))
            continue;
        else if(isalpha(c)||c=='_'){
            variable+=c;
            c=line[++i];
            while(isalpha(c)||isdigit(c)||c=='_'){
                variable+=c;
                c=line[++i];
            }
            i--;
            bool var_duplicated=false;
            for(int i=0;i<varlist.len;i++){
                if(variable==varlist.item[i].var){
                    variable.clear();
                    var_duplicated=true;
                    break;
                }
            }
            if(var_duplicated){
                continue;
            }
            else {
                varlist.item[varlist.len].var=variable;
                cout<<"检测到变量"<<variable<<",请输入该变量的值："<<endl;
                cin>>varlist.item[varlist.len].val;
                varlist.len++;
                variable.clear();
            } 
        }
    }
    for(int i=0;i<varlist.len;i++){
        string variable_val_with_paren ="(" + to_string(varlist.item[i].val) + ")";
        str=replaceAll(str, varlist.item[i].var, variable_val_with_paren);
    }
    return str;
}

//给定参数line，返回后缀表达式
vector<string> GetPostfix(string line){
    if(line.back()!='#') line.push_back('#');
    vector<string> Postfix;
    SqStack<char> OPTR;
    OPTR.Init();
    OPTR.Push('#');
    bool possibleminus=true;
    bool is_var=false;
    string current;
    for(int i=0;i<line.size();i++){
        char c=line[i];
        if(c!='#' || OPTR.GetTop()!='#'){
            if((c=='-' || c=='+') && possibleminus){
                if(c=='-'){
                    current+=c;
                }
                possibleminus=false;
                continue;
            }
            possibleminus=false;
            if(isdigit(c) || c=='.'){
                current+=c;
                continue;
            }
            else if((c=='e' || c=='E') && (!current.empty()) && !is_var){
                current+=c;
                if(i+1<line.size() && line[i+1]=='-'){
                    current+=line[i+1];
                    i++;
                }
            }
            else if((isalpha(c)||c=='_') && (current.empty() || current=="-")){
                is_var=true;
                current+=c;
                continue;
            }
            else if(is_var && (isalpha(c)||c=='_'||isdigit(c))){
                current+=c;
                continue;
            }
            else{
                if(!current.empty()){
                    Postfix.push_back(current);
                    current.clear();
                    is_var=false;
                }
                if(c=='(') possibleminus=true;
                switch (Precede(OPTR.GetTop(),c)){
                    case '<':
                        OPTR.Push(c);
                        break;
                    case '=':
                        char x;
                        OPTR.Pop(x);
                        break;
                    case '>':
                        char theta;
                        OPTR.Pop(theta);
                        string s;
                        s+=theta;
                        Postfix.push_back(s);
                        i--;
                        break;
                }
            }
        }
        else break;        
    }
    return Postfix;
}

BiTree<string>* PostfixToBiTree(vector<string> Postfix){
    stack<BiTree<string>*> TreePointer;
    for(int i=0;i<Postfix.size();i++){
        if(Postfix[i]=="+" || Postfix[i]=="-" || Postfix[i]=="*" || Postfix[i]=="/" || Postfix[i]=="^"){
            BiTree<string>* right=TreePointer.top();
            TreePointer.pop();
            BiTree<string>* left=TreePointer.top();
            TreePointer.pop();
            BiTree<string>* root = new BiTree<string>();
            root->CreateNode(Postfix[i], left->GetRoot(), right->GetRoot());
            TreePointer.push(root);
        }
        else{
            BiTree<string>* tree = new BiTree<string>();
            tree->CreateRoot(Postfix[i]);
            TreePointer.push(tree);
        }
    }
    BiTree<string>* Tree=TreePointer.top();
    TreePointer.pop();
    return Tree;
}

void DealExpression() {
    VarList varlist;
    varlist.item=new VarElem[10];
    varlist.len=0;
    while(1){
        cout << "请输入表达式，不要省略乘号:" << endl;
        string line;
        while (cin.peek() == '\n') cin.get();
        cin >> line;
        if(!line.empty() && (line.back()==';')) line.pop_back();
        line+='#';
        vector<string> Postfix=GetPostfix(line);
        BiTree<string>* Tree=PostfixToBiTree(Postfix);
        Tree->LevelTraverse();
        delete Tree;
        string replaced=line;
        replaced=ReplaceVariable(replaced, varlist);
        double result=EvaluateExpression(replaced);
        cout<<"运算结果为："<<result<<endl;
        if(varlist.len){
            while(1){
                cout << "是否要继续改变变量的值？y/n:" << endl;
                char continue_express;
                cin >> continue_express;
                replaced=line;
                if(continue_express=='y'){
                    for(int i=0;i<varlist.len;i++){
                        cout<<"请输入变量"<<varlist.item[i].var<<"的修改值："<<endl;
                        cin>>varlist.item[i].val;
                    }
                    replaced=ReplaceVariable(replaced, varlist);
                    double result=EvaluateExpression(replaced);
                    cout<<"运算结果为："<<result<<endl;
                }
                else{
                    cout << "已退出该表达式的求值" << endl;
                    break;
                }
            }
        }
        cout << "是否继续输入新的表达式？y/n:" << endl;
        char cont;
        cin >> cont;
        if (cont != 'y') break;       
    }
    delete[] varlist.item;
    varlist.len=0;
}
