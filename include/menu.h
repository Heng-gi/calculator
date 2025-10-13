#ifndef MENU_H
#define MENU_H

#include "sqlist.h"
#include "linklist.h"

// 菜单打印
void printMainMenu();
void printSqListMenu();
void printVectorMenu();
void printSqPolyMenu();
void printLinkPolyMenu();

// 创建演示对象
void createTestSqList(Sqlist &L);
void createVector(Sqlist &vec);

#endif
