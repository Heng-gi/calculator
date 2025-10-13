#ifndef SQLIST_H
#define SQLIST_H

#include <cstdio>
#include <cstdlib>
#include <cmath>

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2

typedef int Status;

typedef struct {
    double *elem;
    int length;
    int listsize;
} Sqlist;

// 基本操作
Status Initlist_sq(Sqlist &L);
Status Destroylist_sq(Sqlist &L);
Status Clearlist_sq(Sqlist &L);
Status ListInsert_sq(Sqlist &L, int i, double e);
Status ListDelete_sq(Sqlist &L, int i, double &e);
Status ListTraverse(Sqlist L);
Status GetElem(const Sqlist &L, int i, double &e);
Status ListEmpty(const Sqlist &L);
int ListLength(const Sqlist &L);
Status LocateElem(const Sqlist &L, double e);

// 向量与多项式操作（顺序表）
Status Add_sq(Sqlist &L1, Sqlist &L2);
Status Minus_sq(Sqlist &L1, Sqlist &L2);
double Euclidean(const Sqlist &L);
double Cosine_similarity(const Sqlist &L1, const Sqlist &L2, double &cos);
Status CreatPolyn_Sq(Sqlist &L, int m);
void PrintSq(const Sqlist &L);
Status AddPolyn_Sq(Sqlist &La, Sqlist &Lb);
Status MinusPolyn_Sq(Sqlist &La, Sqlist &Lb);
Status MultiplyPolyn_Sq(Sqlist &La, Sqlist &Lb);
Status Derivative_Sq(Sqlist &L);
Status Derivative_N_Sq(Sqlist &L, int num, Status (*Diff)(Sqlist &));

#endif
