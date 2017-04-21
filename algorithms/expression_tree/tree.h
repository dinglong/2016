#ifndef _TREE_H_
#define _TREE_H_

#include "node.h"

class ExprTree
{
public:
    ExprTree();
    ~ExprTree();

    void construct(const char* expr);

    void b_print(); // 前序
    void m_print(); // 中序
    void a_print(); // 后序

private:
    void b_print(node_t* t); // 前序
    void m_print(node_t* t); // 中序
    void a_print(node_t* t); // 后序

private:
    node_t* m_proot;
};

#endif

