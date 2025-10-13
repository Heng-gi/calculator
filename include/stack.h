#ifndef STACK_H
#define STACK_H

#include <cstdlib>
#include <iostream>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define OK 1
#define ERROR 0

typedef int Status;

template <typename SElemtype>
class SqStack {
private:
    SElemtype *base;
    SElemtype *top;
    int stacksize;

public:
    Status Init() {
        base = (SElemtype *)malloc(STACK_INIT_SIZE * sizeof(SElemtype));
        if (!base) return ERROR;
        top = base;
        stacksize = STACK_INIT_SIZE;
        return OK;
    }

    Status Destroy() {
        free(base);
        base = top = nullptr;
        return OK;
    }

    Status Push(SElemtype e) {
        if (top - base >= stacksize) {
            base = (SElemtype *)realloc(base, (stacksize + STACKINCREMENT) * sizeof(SElemtype));
            if (!base) return ERROR;
            top = base + stacksize;
            stacksize += STACKINCREMENT;
        }
        *(top++) = e;
        return OK;
    }

    Status Pop(SElemtype &e) {
        if (top == base) return ERROR;
        e = *(--top);
        return OK;
    }

    SElemtype GetTop() { return *(top - 1); }
    Status Empty() { return top == base; }
    void Clear() { top = base; }
};

#endif
