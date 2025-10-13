#include "../include/linklist.h"
#include <iostream>
using namespace std;

Status MakeNode(Link &p, ElemType e) {
    p = (Link)malloc(sizeof(LNode));
    if (!p) return ERROR;
    p->data.coef = e.coef;
    p->data.expn = e.expn;
    p->next = NULL;
    return OK;
}

void FreeNode(Link &p) {
    if (p) {
        free(p);
        p = NULL;
    }
}

Status Init_LinkList(Linklist &L) {
    L.head = (Link)malloc(sizeof(LNode));
    if (!L.head) return ERROR;
    L.head->next = NULL;
    L.tail = L.head;
    L.len = 0;
    return OK;
}

Status Destroy_LinkList(Linklist &L) {
    Link p = L.head;
    Link tmp;
    while (p) {
        tmp = p->next;
        free(p);
        p = tmp;
    }
    L.head = L.tail = NULL;
    L.len = 0;
    return OK;
}

Status Clear_LinkList(Linklist &L) {
    Link p = L.head->next;
    Link tmp;
    while (p) {
        tmp = p->next;
        free(p);
        p = tmp;
    }
    L.head->next = NULL;
    L.tail = L.head;
    L.len = 0;
    return OK;
}

Status Append(Linklist &L, Link s) {
    if (!s) return OK;
    L.tail->next = s;
    // count nodes in s
    while (s) {
        L.len++;
        if (!s->next) break;
        s = s->next;
    }
    L.tail = s;
    return OK;
}

int cmp(ElemType a, ElemType b) {
    if (a.expn > b.expn) return 1;
    else if (a.expn == b.expn) return 0;
    else return -1;
}

void SortLinkList(Linklist &L, int (*cmp)(ElemType, ElemType)) {
    if (L.head->next == NULL || L.head->next->next == NULL) return;
    Link p = L.head->next->next;
    Link sorted = L.head->next;
    sorted->next = NULL;
    L.tail = sorted;
    while (p != NULL) {
        Link q = L.head;
        Link pnext = p->next;
        while (q->next != NULL && cmp(p->data, q->next->data) > 0) {
            q = q->next;
        }
        if (q->next == NULL) {
            q->next = p;
            p->next = NULL;
            L.tail = p;
        } else if (!cmp(p->data, q->next->data)) {
            q->next->data.coef += p->data.coef;
            FreeNode(p);
            L.len--;
        } else {
            Link tmp = q->next;
            q->next = p;
            p->next = tmp;
        }
        p = pnext;
    }
}

void CreatPolyn_Link(Linklist &P, int m) {
    if (!Init_LinkList(P)) {
        printf("未能成功创建一元多项式的有序链表\n");
        return;
    }
    printf("请输入一元多项式（每行输入一个项：系数 指数）:\n");
    for (int i = 0; i < m; i++) {
        ElemType e;
        if (scanf("%lf %d", &e.coef, &e.expn) != 2) {
            printf("输入错误\n");
            return;
        }
        Link node;
        if (!MakeNode(node, e)) {
            printf("内存分配失败\n");
            return;
        }
        Append(P, node);
    }
    SortLinkList(P, cmp);
    printf("成功创建一元多项式的有序链表\n");
}

void PrintPolyn_Link(Linklist &P) {
    if (P.head->next == NULL) {
        printf("0\n");
        return;
    }
    Link p = P.head->next;
    int has_term = 0;
    while (p != NULL) {
        if (fabs(p->data.coef) < 1e-6) {
            p = p->next;
            continue;
        }
        if (has_term && p->data.coef > 0) printf("+");
        printf("%.2lfx^%d", p->data.coef, p->data.expn);
        has_term = 1;
        p = p->next;
    }
    if (!has_term) printf("0");
    printf("\n");
}

void AddPolyn_Link(Linklist &Pa, Linklist &Pb) {
    Append(Pa, Pb.head->next);
    SortLinkList(Pa, cmp);
    Pb.head->next = NULL;
    Destroy_LinkList(Pb);
    printf("已完成多项式相加运算，并将结果存储到第一个多项式中\n");
}

void SubtractPolyn_Link(Linklist &Pa, Linklist &Pb) {
    Position ha = Pa.head;
    Position hb = Pb.head;
    Position qa = ha->next;
    Position qb = hb->next;
    while (qa && qb) {
        ElemType a = qa->data;
        ElemType b = qb->data;
        switch (cmp(a, b)) {
            case -1: {
                ha = qa;
                qa = qa->next;
                break;
            }
            case 0: {
                double res = a.coef - b.coef;
                if (fabs(res) >= 1e-6) {
                    qa->data.coef = res;
                    ha = qa;
                } else {
                    // remove qa
                    ha->next = qa->next;
                    FreeNode(qa);
                    Pa.len--;
                    qa = ha->next;
                }
                // remove qb
                hb->next = qb->next;
                FreeNode(qb);
                qb = hb->next;
                break;
            }
            case 1: {
                // move qb node into Pa before qa
                Link temp = qb->next;
                qb->data.coef = -qb->data.coef;
                qb->next = qa;
                ha->next = qb;
                Pa.len++;
                hb->next = temp;
                qb = hb->next;
                ha = ha->next;
                break;
            }
        }
    }
    // append remaining qb nodes (negated)
    while (hb->next != NULL) {
        Link node = hb->next;
        hb->next = node->next;
        node->next = NULL;
        node->data.coef = -node->data.coef;
        Append(Pa, node);
    }
    // fix tail
    Link p = Pa.head;
    while (p->next != NULL) p = p->next;
    Pa.tail = p;
    FreeNode(hb);
}

void MultiplyPolyn_Link(Linklist &Pa, Linklist &Pb) {
    if (Pa.head->next == NULL || Pb.head->next == NULL) {
        Clear_LinkList(Pa);
        Destroy_LinkList(Pb);
        return;
    }
    Link pb = Pb.head->next;
    Linklist P;
    Init_LinkList(P);
    while (pb != NULL) {
        Link pa = Pa.head->next;
        while (pa != NULL) {
            ElemType e;
            e.coef = pa->data.coef * pb->data.coef;
            e.expn = pa->data.expn + pb->data.expn;
            // insert e into P in order
            // Use OrderInsert-like behavior:
            Position q = P.head;
            while (q->next != NULL && cmp(e, q->next->data) > 0) q = q->next;
            if (q->next != NULL && cmp(e, q->next->data) == 0) {
                q->next->data.coef += e.coef;
            } else {
                Link node;
                if (!MakeNode(node, e)) { Destroy_LinkList(P); return; }
                node->next = q->next;
                q->next = node;
                P.len++;
            }
            pa = pa->next;
        }
        pb = pb->next;
    }
    Destroy_Link_List:
    Destroy_LinkList(Pa);
    Pa = P;
    Destroy_LinkList(Pb);
}

void Derivative(Linklist &P) {
    Position hp = P.head;
    Position qp = hp->next;
    while (qp != NULL) {
        if (qp->data.expn == 0) {
            // remove qp
            hp->next = qp->next;
            FreeNode(qp);
            P.len--;
            qp = hp->next;
        } else {
            qp->data.coef *= qp->data.expn;
            qp->data.expn -= 1;
            hp = qp;
            qp = qp->next;
        }
    }
    P.tail = P.head;
    while (P.tail->next) P.tail = P.tail->next;
}

void Derivative_N(Linklist &P, int num, void(*Diff)(Linklist &)) {
    if (num < 0) {
        printf("不存在负阶导数\n");
        return;
    }
    for (int i = 0; i < num; i++) Diff(P);
}
