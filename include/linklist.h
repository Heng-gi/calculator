#ifndef LINKLIST_H
#define LINKLIST_H

#include <cstdio>
#include <cstdlib>
#include <cmath>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;

typedef struct {
    double coef;
    int expn;
} ElemType;

typedef struct LNode {
    ElemType data;
    struct LNode *next;
} *Link, *Position;

typedef struct {
    Link head, tail;
    int len;
} Linklist;

// 链表基本操作
Status MakeNode(Link &p, ElemType e);
void FreeNode(Link &p);
Status Init_LinkList(Linklist &L);
Status Destroy_LinkList(Linklist &L);
Status Clear_LinkList(Linklist &L);
Status Append(Linklist &L, Link s);
int cmp(ElemType a, ElemType b);
void SortLinkList(Linklist &L, int (*cmp)(ElemType, ElemType));

// 多项式操作（链表）
void CreatPolyn_Link(Linklist &P, int m);
void PrintPolyn_Link(Linklist &P);
void AddPolyn_Link(Linklist &Pa, Linklist &Pb);
void SubtractPolyn_Link(Linklist &Pa, Linklist &Pb);
void MultiplyPolyn_Link(Linklist &Pa, Linklist &Pb);
void Derivative(Linklist &P);
void Derivative_N(Linklist &P, int num, void(*Diff)(Linklist &));

#endif
