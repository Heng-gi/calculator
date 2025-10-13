#include "../include/expression.h"
#include "../include/stack.h"
#include "../include/utils.h"
#include <cctype>
#include <cmath>
#include <iostream>
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

double EvaluateExpression(const string &line){
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
            if(c=='-' && possibleminus){
                currentnumber+=c;
                possibleminus=false;
                continue;
            }
            possibleminus=false;
            if(isdigit(c) || c=='.'){
                currentnumber+=c;
                continue;
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
    cout<<"运算结果为："<<result<<endl;
    return result;
}

void DealExpression() {
    cout << "请输入表达式，以#结尾，中间不要输入空格，不要省略乘号:" << endl;
    string line;
    cin >> line;
    cout << "表达式中是否包含变量？y/n" << endl;
    char need_variable;
    cin >> need_variable;
    if (need_variable == 'n') {
        EvaluateExpression(line);
    } else {
        cout << "请输入变量名:" << endl;
        string variable_name;
        cin >> variable_name;
        while (1) {
            cout << "请输入变量" << variable_name << "的值:" << endl;
            string variable_val;
            cin >> variable_val;
            string variable_val_with_paren ="(" + variable_val + ")";
            string replaced = replaceAll(line, variable_name, variable_val_with_paren);
            EvaluateExpression(replaced);
            cout << "是否要继续改变变量" << variable_name << "的值？y/n:" << endl;
            char continue_express;
            cin >> continue_express;
            if (continue_express == 'n') {
                cout << "已退出该表达式的求值" << endl;
                break;
            }
        }
    }
}
