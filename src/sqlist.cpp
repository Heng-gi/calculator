#include "../include/sqlist.h"
#include <iostream>
using namespace std;

Status Initlist_sq(Sqlist &L) {
    L.elem = (double *)malloc(LIST_INIT_SIZE * sizeof(double));
    if (!L.elem) exit(OVERFLOW);
    for (int i = 0; i < LIST_INIT_SIZE; i++) L.elem[i] = 0;
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}

Status Destroylist_sq(Sqlist &L) {
    free(L.elem);
    L.elem = nullptr;
    L.length = 0;
    L.listsize = 0;
    return OK;
}

Status Clearlist_sq(Sqlist &L) {
    for (int i = 0; i < L.length; i++) L.elem[i] = 0;
    L.length = 0;
    return OK;
}

Status ListEmpty(const Sqlist &L) { return !L.length; }
int ListLength(const Sqlist &L) { return L.length; }

Status GetElem(const Sqlist &L, int i, double &e) {
    if (i < 1 || i > L.length) return ERROR;
    e = L.elem[i - 1];
    return OK;
}

Status LocateElem(const Sqlist &L, double e) {
    for (int i = 0; i < L.length; i++) {
        if (fabs(L.elem[i] - e) < 1e-6) return i + 1;
    }
    return 0;
}

Status ListInsert_sq(Sqlist &L, int i, double e) {
    if (i < 1 || i > L.length + 1) return ERROR;
    if (L.length >= L.listsize) {
        double *newbase = (double *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(double));
        if (!newbase) return OVERFLOW;
        L.elem = newbase;
        for (int j = L.listsize; j < L.listsize + LISTINCREMENT; j++) L.elem[j] = 0;
        L.listsize += LISTINCREMENT;
    }
    double *q = &(L.elem[i - 1]);
    for (double *p = &(L.elem[L.length - 1]); p >= q; p--) *(p + 1) = *p;
    *q = e;
    L.length++;
    return OK;
}

Status ListDelete_sq(Sqlist &L, int i, double &e) {
    if (i < 1 || i > L.length) return ERROR;
    double *p = &L.elem[i - 1];
    e = *p;
    double *q = &L.elem[L.length - 2];
    for (; p <= q; p++) *p = *(p + 1);
    L.length--;
    return OK;
}

Status ListTraverse(Sqlist L) {
    if (!L.length) return ERROR;
    for (int i = 0; i < L.length; i++) printf("%lf ", L.elem[i]);
    printf("\n");
    return OK;
}

// ---------------- 向量与多项式操作 ----------------

Status Add_sq(Sqlist &L1, Sqlist &L2) {
    if (L1.length != L2.length) return ERROR;
    for (int i = 0; i < L1.length; i++) L1.elem[i] += L2.elem[i];
    Destroylist_sq(L2);
    return OK;
}

Status Minus_sq(Sqlist &L1, Sqlist &L2) {
    if (L1.length != L2.length) return ERROR;
    for (int i = 0; i < L1.length; i++) L1.elem[i] -= L2.elem[i];
    Destroylist_sq(L2);
    return OK;
}

double Euclidean(const Sqlist &L) {
    double sum = 0;
    for (int i = 0; i < L.length; i++) sum += L.elem[i] * L.elem[i];
    return sqrt(sum);
}

double Cosine_similarity(const Sqlist &L1, const Sqlist &L2, double &cos) {
    if ((L1.length != L2.length) || !L1.length || !L2.length) return ERROR;
    double dot = 0;
    for (int i = 0; i < L1.length; i++) dot += L1.elem[i] * L2.elem[i];
    cos = dot / (Euclidean(L1) * Euclidean(L2));
    return OK;
}

// ---------------- 多项式（顺序表） ----------------

Status CreatPolyn_Sq(Sqlist &L, int m) {
    if (!Initlist_sq(L)) return ERROR;
    printf("请输入一元多项式（每行输入：系数 指数）:\n");
    int max_expn = 0;
    for (int i = 0; i < m; i++) {
        double coef; int expn;
        scanf("%lf %d", &coef, &expn);
        while (expn >= L.listsize) {
            double *newbase = (double *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(double));
            if (!newbase) return OVERFLOW;
            L.elem = newbase;
            for (int j = L.listsize; j < L.listsize + LISTINCREMENT; j++) L.elem[j] = 0;
            L.listsize += LISTINCREMENT;
        }
        if (fabs(coef) > 1e-6) {
            L.elem[expn] += coef;
            max_expn = max_expn > expn ? max_expn : expn;
        }
    }
    L.length = max_expn + 1;
    return OK;
}

void PrintSq(const Sqlist &L) {
    int printed = 0;
    for (int i = 0; i < L.length; i++) {
        if (fabs(L.elem[i]) < 1e-6) continue;
        if (printed && L.elem[i] > 0) printf("+");
        printf("%.2lfx^%d", L.elem[i], i);
        printed = 1;
    }
    if (!printed) printf("0");
    printf("\n");
}

Status AddPolyn_Sq(Sqlist &La, Sqlist &Lb) {
    int max_len = max(La.length, Lb.length);
    while (max_len > La.length) ListInsert_sq(La, La.length + 1, 0);
    while (max_len > Lb.length) ListInsert_sq(Lb, Lb.length + 1, 0);
    Add_sq(La, Lb);
    return OK;
}

Status MinusPolyn_Sq(Sqlist &La, Sqlist &Lb) {
    int max_len = max(La.length, Lb.length);
    while (max_len > La.length) ListInsert_sq(La, La.length + 1, 0);
    while (max_len > Lb.length) ListInsert_sq(Lb, Lb.length + 1, 0);
    Minus_sq(La, Lb);
    return OK;
}

Status MultiplyPolyn_Sq(Sqlist &La, Sqlist &Lb) {
    if (!La.length || !Lb.length) {
        Clearlist_sq(La);
        Destroylist_sq(Lb);
        return OK;
    }
    Sqlist LP;
    Initlist_sq(LP);
    for (int i = 0; i < Lb.length; i++) {
        if (fabs(Lb.elem[i]) < 1e-6) continue;
        for (int j = 0; j < La.length; j++) {
            if (fabs(La.elem[j]) < 1e-6) continue;
            int idx = i + j;
            if (idx >= LP.listsize) ListInsert_sq(LP, idx + 1, La.elem[j] * Lb.elem[i]);
            else LP.elem[idx] += La.elem[j] * Lb.elem[i];
        }
    }
    Destroylist_sq(Lb);
    Destroylist_sq(La);
    La = LP;
    return OK;
}

Status Derivative_Sq(Sqlist &L) {
    for (int i = 1; i < L.length; i++) L.elem[i - 1] = L.elem[i] * i;
    if (L.length) L.length--;
    L.elem[L.length] = 0;
    return OK;
}

Status Derivative_N_Sq(Sqlist &L, int num, Status (*Diff)(Sqlist &)) {
    if (num < 0) return ERROR;
    for (int i = 0; i < num; i++) Diff(L);
    return OK;
}
