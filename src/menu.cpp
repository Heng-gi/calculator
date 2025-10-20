#include "../include/menu.h"
#include "../include/sqlist.h"
#include <cstdio>
#include <iostream>
using namespace std;

void printMainMenu() {
    printf("\n===== 计算器主菜单 =====\n");
    printf("1. 顺序表操作\n");
    printf("2. 向量计算（顺序表）\n");
    printf("3. 多项式计算（顺序表）\n");
    printf("4. 多项式计算（链表）\n");
    printf("5. 四则运算表达式求值\n");
    printf("6. 函数定义与运行\n");
    printf("7. 极值点计算\n");       
    printf("8. 线性方程组求解\n");   
    printf("9. 非线性方程组求解\n");
    printf("10. 矩阵计算\n");
    printf("0. 退出程序\n");
    printf("========================\n");
    printf("请选择功能: ");
}

void printSqListMenu() {
    printf("\n===== 顺序表操作 =====\n");
    printf("1. 创建顺序表\n");
    printf("2. 遍历顺序表\n");
    printf("3. 清空顺序表\n");
    printf("4. 销毁顺序表\n");
    printf("5. 插入元素\n");
    printf("6. 删除元素\n");
    printf("7. 获取元素\n");
    printf("8. 查找元素位置\n");
    printf("0. 返回主菜单\n");
    printf("======================\n");
    printf("请选择操作: ");
}

void printVectorMenu() {
    printf("\n===== 向量计算 =====\n");
    printf("1. 创建向量A\n");
    printf("2. 创建向量B\n");
    printf("3. 向量A + 向量B\n");
    printf("4. 向量A - 向量B\n");
    printf("5. 计算向量的欧几里得距离\n");
    printf("6. 计算向量间夹角余弦值\n");
    printf("7. 显示向量A\n");
    printf("8. 显示向量B\n");
    printf("0. 返回主菜单\n");
    printf("====================\n");
    printf("请选择操作: ");
}

void printSqPolyMenu() {
    printf("\n===== 顺序表多项式计算 =====\n");
    printf("1. 创建多项式A\n");
    printf("2. 创建多项式B\n");
    printf("3. 多项式A + 多项式B\n");
    printf("4. 多项式A - 多项式B\n");
    printf("5. 多项式A * 多项式B\n");
    printf("6. 计算多项式A的导数\n");
    printf("7. 计算多项式A的n阶导数\n");
    printf("8. 显示多项式A\n");
    printf("9. 显示多项式B\n");
    printf("0. 返回主菜单\n");
    printf("===========================\n");
    printf("请选择操作: ");
}

void printLinkPolyMenu() {
    printf("\n===== 链表多项式计算 =====\n");
    printf("1. 创建多项式A\n");
    printf("2. 创建多项式B\n");
    printf("3. 多项式A + 多项式B\n");
    printf("4. 多项式A - 多项式B\n");
    printf("5. 多项式A * 多项式B\n");
    printf("6. 计算多项式A的导数\n");
    printf("7. 计算多项式A的n阶导数\n");
    printf("8. 显示多项式A\n");
    printf("9. 显示多项式B\n");
    printf("0. 返回主菜单\n");
    printf("==========================\n");
    printf("请选择操作: ");
}

// 极值点计算菜单
void printExtremePointMenu() {
    printf("\n===== 极值点计算 =====\n");
    printf("1. 输入函数和初始值计算极值点\n");
    printf("0. 返回主菜单\n");
    printf("======================\n");
    printf("请选择操作: ");
}

// 线性方程组求解菜单
void printLinearEquationMenu() {
    printf("\n===== 线性方程组求解 =====\n");
    printf("1. 输入线性方程组并求解（每行一个方程，空行结束）\n");
    printf("0. 返回主菜单\n");
    printf("==========================\n");
    printf("请选择操作: ");
}

// 非线性方程组求解菜单
void printNonLinearEquationMenu() {
    printf("\n===== 非线性方程组求解 =====\n");
    printf("1. 输入非线性方程组并求解（每行一个方程，空行结束）\n");
    printf("0. 返回主菜单\n");
    printf("============================\n");
    printf("请选择操作: ");
}

// 矩阵操作菜单
void printMatrixMenu() {
    printf("\n===== 矩阵计算 =====\n");
    printf("1. 创建矩阵A\n");
    printf("2. 创建矩阵B\n");
    printf("3. 矩阵A + 矩阵B\n");
    printf("4. 矩阵A - 矩阵B\n");
    printf("5. 矩阵A * 矩阵B\n");
    printf("6. 矩阵A转置\n");
    printf("7. 计算矩阵A的行列式\n");
    printf("8. 求矩阵A的逆矩阵\n");
    printf("9. 计算矩阵A的特征值\n");
    printf("10. 显示矩阵A\n");
    printf("11. 显示矩阵B\n");
    printf("0. 返回主菜单\n");
    printf("====================\n");
    printf("请选择操作: ");
}

// 创建矩阵
void createMatrix(Matrix &matrix) {
    int rows, cols;
    printf("请输入矩阵的行数和列数: ");
    if (scanf("%d%d", &rows, &cols) != 2 || rows <= 0 || cols <= 0) {
        printf("输入错误，行数和列数必须为正整数\n");
        return;
    }
    
    vector<vector<double>> data(rows, vector<double>(cols));
    printf("请按行输入%d行%d列矩阵元素（空格分隔）: \n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (scanf("%lf", &data[i][j]) != 1) {
                printf("元素输入错误\n");
                return;
            }
        }
    }
    
    matrix = Matrix(data);
    printf("矩阵创建成功\n");
}

void createTestSqList(Sqlist &L) {
    int n;
    printf("请输入顺序表元素个数: ");
    if (scanf("%d", &n) != 1) { printf("输入错误\n"); return; }
    Initlist_sq(L);
    printf("请输入%d个元素: ", n);
    for (int i = 0; i < n; i++) {
        double val;
        scanf("%lf", &val);
        ListInsert_sq(L, i + 1, val);
    }
    printf("顺序表创建成功\n");
}

void createVector(Sqlist &vec) {
    int dim;
    printf("请输入向量维度: ");
    if (scanf("%d", &dim) != 1) { printf("输入错误\n"); return; }
    Initlist_sq(vec);
    printf("请输入%d个向量元素: ", dim);
    for (int i = 0; i < dim; i++) {
        double val;
        scanf("%lf", &val);
        ListInsert_sq(vec, i + 1, val);
    }
    printf("向量创建成功\n");
}
