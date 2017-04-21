#include <cstdio>
#include <cstdlib>
#include "stack.h"

Stack::Stack()
{
    m_ptop = NULL;
}

Stack::~Stack()
{
    while (!is_empty()) {
        node_t* tmp = pop();
        delete tmp;
    }
}

void Stack::push(node_t* data)
{
    element_t* pe = new element_t();

    pe->data = data;
    pe->next = m_ptop;
    m_ptop = pe;
}

node_t* Stack::pop()
{
    node_t* ret = NULL;

    if (!is_empty()) {
        ret = m_ptop->data;
        m_ptop = m_ptop->next;
    } else {
        printf("stack is null, can't pop.\n");
        exit(1);
    }

    return ret;
}

bool Stack::is_empty()
{
    return (m_ptop == NULL);
}

