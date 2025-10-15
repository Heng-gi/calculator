#include "../include/menu.h"
#include "../include/sqlist.h"
#include "../include/linklist.h"
#include "../include/expression.h"
#include "../include/func.h"
#include <cstdio>
#include <cstdlib>

int main() {
    int choice;
    Sqlist sqList, vecA, vecB, polySqA, polySqB;
    Linklist polyLinkA, polyLinkB;
    int isSqListInit = 0, isVecAInit = 0, isVecBInit = 0;
    int isPolySqAInit = 0, isPolySqBInit = 0;
    int isPolyLinkAInit = 0, isPolyLinkBInit = 0;

    FuncList funclist;
    InitFuncList(funclist);

    do {
        printMainMenu();
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1: { // 顺序表操作
                int op;
                do {
                    printSqListMenu();
                    if (scanf("%d", &op) != 1) { op = 0; break; }
                    switch (op) {
                        case 1:
                            if (isSqListInit) Destroylist_sq(sqList);
                            createTestSqList(sqList);
                            isSqListInit = 1;
                            break;
                        case 2:
                            if (!isSqListInit) { printf("顺序表未初始化\n"); break; }
                            printf("顺序表元素: ");
                            ListTraverse(sqList);
                            break;
                        case 3:
                            if (!isSqListInit) { printf("顺序表未初始化\n"); break; }
                            Clearlist_sq(sqList);
                            printf("顺序表已清空\n");
                            break;
                        case 4:
                            if (!isSqListInit) { printf("顺序表未初始化\n"); break; }
                            Destroylist_sq(sqList);
                            isSqListInit = 0;
                            printf("顺序表已销毁\n");
                            break;
                        case 5: {
                            if (!isSqListInit) { printf("顺序表未初始化\n"); break; }
                            int pos; double val;
                            printf("请输入插入位置(初始为第1个位置)和元素值: ");
                            if (scanf("%d%lf", &pos, &val) == 2) {
                                if (ListInsert_sq(sqList, pos, val) == OK) printf("插入成功\n");
                                else printf("插入失败\n");
                            }
                            break;
                        }
                        case 6: {
                            if (!isSqListInit) { printf("顺序表未初始化\n"); break; }
                            int pos; double val;
                            printf("请输入删除位置: ");
                            if (scanf("%d", &pos) == 1) {
                                if (ListDelete_sq(sqList, pos, val) == OK) printf("删除成功，删除元素为: %lf\n", val);
                                else printf("删除失败\n");
                            }
                            break;
                        }
                        case 7: {
                            if (!isSqListInit) { printf("顺序表未初始化\n"); break; }
                            int pos; double val;
                            printf("请输入获取元素的位置: ");
                            if (scanf("%d", &pos) == 1) {
                                if (GetElem(sqList, pos, val) == OK) printf("位置%d的元素为: %lf\n", pos, val);
                                else printf("获取失败\n");
                            }
                            break;
                        }
                        case 8: {
                            if (!isSqListInit) { printf("顺序表未初始化\n"); break; }
                            double val;
                            printf("请输入查找的元素值: ");
                            if (scanf("%lf", &val) == 1) {
                                int pos = LocateElem(sqList, val);
                                if (pos) printf("元素%lf的位置为: %d\n", val, pos);
                                else printf("未找到元素%lf\n", val);
                            }
                            break;
                        }
                        case 0: printf("返回主菜单\n"); break;
                        default: printf("无效操作，请重新选择\n");
                    }
                } while (op != 0);
                break;
            }

            case 2: {
                int op;
                do {
                    printVectorMenu();
                    if (scanf("%d", &op) != 1) { op = 0; break; }
                    switch (op) {
                        case 1:
                            if (isVecAInit) Destroylist_sq(vecA);
                            createVector(vecA);
                            isVecAInit = 1;
                            break;
                        case 2:
                            if (isVecBInit) Destroylist_sq(vecB);
                            createVector(vecB);
                            isVecBInit = 1;
                            break;
                        case 3:
                            if (!isVecAInit || !isVecBInit) { printf("向量A或B未初始化\n"); break; }
                            if (Add_sq(vecA, vecB) == OK) { printf("向量相加成功，结果为: "); ListTraverse(vecA); isVecBInit = 0; }
                            else printf("向量维度不同，无法相加\n");
                            break;
                        case 4:
                            if (!isVecAInit || !isVecBInit) { printf("向量A或B未初始化\n"); break; }
                            if (Minus_sq(vecA, vecB) == OK) { printf("向量相减成功，结果为: "); ListTraverse(vecA); isVecBInit = 0; }
                            else printf("向量维度不同，无法相减\n");
                            break;
                        case 5: {
                            int vecChoice;
                            printf("请选择计算哪个向量的距离(1:A, 2:B): ");
                            if (scanf("%d", &vecChoice) == 1) {
                                if (vecChoice == 1 && isVecAInit) printf("向量A的欧几里得距离为: %lf\n", Euclidean(vecA));
                                else if (vecChoice == 2 && isVecBInit) printf("向量B的欧几里得距离为: %lf\n", Euclidean(vecB));
                                else printf("向量未初始化\n");
                            }
                            break;
                        }
                        case 6: {
                            if (!isVecAInit || !isVecBInit) { printf("向量A或B未初始化\n"); break; }
                            double cosVal;
                            if (Cosine_similarity(vecA, vecB, cosVal) == OK) printf("向量间夹角余弦值为: %lf\n", cosVal);
                            else printf("无法计算夹角余弦值\n");
                            break;
                        }
                        case 7:
                            if (!isVecAInit) { printf("向量A未初始化\n"); break; }
                            printf("向量A: "); ListTraverse(vecA);
                            break;
                        case 8:
                            if (!isVecBInit) { printf("向量B未初始化\n"); break; }
                            printf("向量B: "); ListTraverse(vecB);
                            break;
                        case 0: printf("返回主菜单\n"); break;
                        default: printf("无效操作，请重新选择\n");
                    }
                } while (op != 0);
                break;
            }

            case 3: {
                int op;
                do {
                    printSqPolyMenu();
                    if (scanf("%d", &op) != 1) { op = 0; break; }
                    switch (op) {
                        case 1:
                            if (isPolySqAInit) Destroylist_sq(polySqA);
                            {
                                int m;
                                printf("请输入多项式A的项数: ");
                                if (scanf("%d", &m) == 1) {
                                    if (CreatPolyn_Sq(polySqA, m) == OK) { printf("多项式A创建成功\n"); isPolySqAInit = 1; }
                                }
                            }
                            break;
                        case 2:
                            if (isPolySqBInit) Destroylist_sq(polySqB);
                            {
                                int m;
                                printf("请输入多项式B的项数: ");
                                if (scanf("%d", &m) == 1) {
                                    if (CreatPolyn_Sq(polySqB, m) == OK) { printf("多项式B创建成功\n"); isPolySqBInit = 1; }
                                }
                            }
                            break;
                        case 3:
                            if (!isPolySqAInit || !isPolySqBInit) { printf("多项式A或B未初始化\n"); break; }
                            AddPolyn_Sq(polySqA, polySqB);
                            printf("多项式相加结果: "); PrintSq(polySqA);
                            isPolySqBInit = 0;
                            break;
                        case 4:
                            if (!isPolySqAInit || !isPolySqBInit) { printf("多项式A或B未初始化\n"); break; }
                            MinusPolyn_Sq(polySqA, polySqB);
                            printf("多项式相减结果: "); PrintSq(polySqA);
                            isPolySqBInit = 0;
                            break;
                        case 5:
                            if (!isPolySqAInit || !isPolySqBInit) { printf("多项式A或B未初始化\n"); break; }
                            if (MultiplyPolyn_Sq(polySqA, polySqB) == OK) { printf("多项式相乘成功，结果为: "); PrintSq(polySqA); isPolySqBInit = 0; }
                            else printf("多项式相乘失败\n");
                            break;
                        case 6:
                            if (!isPolySqAInit) { printf("多项式A未初始化\n"); break; }
                            if (Derivative_Sq(polySqA) == OK) { printf("多项式A的一阶导数为: "); PrintSq(polySqA); }
                            else printf("求导失败\n");
                            break;
                        case 7: {
                            if (!isPolySqAInit) { printf("多项式A未初始化\n"); break; }
                            int n;
                            printf("请输入导数阶数: ");
                            if (scanf("%d", &n) == 1) {
                                if (Derivative_N_Sq(polySqA, n, Derivative_Sq) == OK) { printf("多项式A的%d阶导数为: ", n); PrintSq(polySqA); }
                                else printf("求n阶导数失败\n");
                            }
                            break;
                        }
                        case 8:
                            if (!isPolySqAInit) { printf("多项式A未初始化\n"); break; }
                            printf("多项式A: "); PrintSq(polySqA);
                            break;
                        case 9:
                            if (!isPolySqBInit) { printf("多项式B未初始化\n"); break; }
                            printf("多项式B: "); PrintSq(polySqB);
                            break;
                        case 0: printf("返回主菜单\n"); break;
                        default: printf("无效操作，请重新选择\n");
                    }
                } while (op != 0);
                break;
            }

            case 4: {
                int op;
                do {
                    printLinkPolyMenu();
                    if (scanf("%d", &op) != 1) { op = 0; break; }
                    switch (op) {
                        case 1:
                            if (isPolyLinkAInit) Destroy_LinkList(polyLinkA);
                            {
                                int m; printf("请输入多项式A的项数: ");
                                if (scanf("%d", &m) == 1) { CreatPolyn_Link(polyLinkA, m); isPolyLinkAInit = 1; }
                            }
                            break;
                        case 2:
                            if (isPolyLinkBInit) Destroy_LinkList(polyLinkB);
                            {
                                int m; printf("请输入多项式B的项数: ");
                                if (scanf("%d", &m) == 1) { CreatPolyn_Link(polyLinkB, m); isPolyLinkBInit = 1; }
                            }
                            break;
                        case 3:
                            if (!isPolyLinkAInit || !isPolyLinkBInit) { printf("多项式A或B未初始化\n"); break; }
                            AddPolyn_Link(polyLinkA, polyLinkB);
                            printf("多项式相加结果: "); PrintPolyn_Link(polyLinkA);
                            isPolyLinkBInit = 0;
                            break;
                        case 4:
                            if (!isPolyLinkAInit || !isPolyLinkBInit) { printf("多项式A或B未初始化\n"); break; }
                            SubtractPolyn_Link(polyLinkA, polyLinkB);
                            printf("多项式相减结果: "); PrintPolyn_Link(polyLinkA);
                            isPolyLinkBInit = 0;
                            break;
                        case 5:
                            if (!isPolyLinkAInit || !isPolyLinkBInit) { printf("多项式A或B未初始化\n"); break; }
                            MultiplyPolyn_Link(polyLinkA, polyLinkB);
                            printf("多项式相乘结果: "); PrintPolyn_Link(polyLinkA);
                            isPolyLinkBInit = 0;
                            break;
                        case 6:
                            if (!isPolyLinkAInit) { printf("多项式A未初始化\n"); break; }
                            Derivative(polyLinkA);
                            printf("多项式A的导数: "); PrintPolyn_Link(polyLinkA);
                            break;
                        case 7: {
                            if (!isPolyLinkAInit) { printf("多项式A未初始化\n"); break; }
                            int n; printf("请输入导数阶数: ");
                            if (scanf("%d", &n) == 1) { Derivative_N(polyLinkA, n, Derivative); printf("多项式A的%d阶导数: ", n); PrintPolyn_Link(polyLinkA); }
                            break;
                        }
                        case 8:
                            if (!isPolyLinkAInit) { printf("多项式A未初始化\n"); break; }
                            printf("多项式A: "); PrintPolyn_Link(polyLinkA);
                            break;
                        case 9:
                            if (!isPolyLinkBInit) { printf("多项式B未初始化\n"); break; }
                            printf("多项式B: "); PrintPolyn_Link(polyLinkB);
                            break;
                        case 0: printf("返回主菜单\n"); break;
                        default: printf("无效操作，请重新选择\n");
                    }
                } while (op != 0);
                break;
            }

            case 5:
                // expression
                DealExpression();
                break;

            case 6: {
                getchar();
                printf("\n===== 函数操作模式 =====\n");
                printf("支持以下指令：\n");
                printf("  - 定义函数：DEF 函数名(参数)=表达式\n");
                printf("  - 运行函数：RUN 函数名(参数值)\n");
                printf("  - 查看函数：LIST\n");
                printf("  - 清除函数：CLEAR\n");
                printf("  - 退出模式：EXIT\n");
                printf("========================\n");
                printf("\n请输入指令: \n");
                DealFunc(funclist);
            }

            case 0:
                printf("感谢使用，再见！\n");
                if (isSqListInit) Destroylist_sq(sqList);
                if (isVecAInit) Destroylist_sq(vecA);
                if (isVecBInit) Destroylist_sq(vecB);
                if (isPolySqAInit) Destroylist_sq(polySqA);
                if (isPolySqBInit) Destroylist_sq(polySqB);
                if (isPolyLinkAInit) Destroy_LinkList(polyLinkA);
                if (isPolyLinkBInit) Destroy_LinkList(polyLinkB);
                DestoryFunclist(funclist);
                break;

            default:
                printf("无效选择，请重新输入\n");
        }
    } while (choice != 0);

    return 0;
}
