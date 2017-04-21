#ifndef _STACK_H_
#define _STACK_H_

#include "node.h"

typedef struct Element {
    node_t* data;
    struct Element* next;
} element_t;

class Stack
{
public:
    Stack();
    ~Stack();

    void push(node_t* data);
    node_t* pop();

    bool is_empty();

private:
    element_t* m_ptop;
};

#endif

