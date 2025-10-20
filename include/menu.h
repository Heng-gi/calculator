#ifndef MENU_H
#define MENU_H

#include "sqlist.h"
#include "linklist.h"
#include "matrix.h"

// 菜单打印
void printMainMenu();
void printSqListMenu();
void printVectorMenu();
void printSqPolyMenu();
void printLinkPolyMenu();
void printExtremePointMenu();
void printLinearEquationMenu();
void printNonLinearEquationMenu();
void printMatrixMenu();
void createMatrix(Matrix &matrix);

// 创建演示对象
void createTestSqList(Sqlist &L);
void createVector(Sqlist &vec);

#endif
