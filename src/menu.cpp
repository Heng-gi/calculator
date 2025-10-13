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
