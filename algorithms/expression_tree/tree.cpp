#include <cstdio>
#include "stack.h"
#include "tree.h"
#include "expr_translate.h"

ExprTree::ExprTree()
{
    m_proot = NULL;
}

ExprTree::~ExprTree()
{
    // TODO
}

void ExprTree::construct(const char* expr)
{
    Stack* input = new Stack();
    ExprTranslate* et = new ExprTranslate(expr);
    Stack* ep = et->get_suff_expr();

    while (!ep->is_empty()) {
        node_t* token = ep->pop();

        printf("input --- %s\n", token->data);
        input->push(token); // 逆转
    }

    while (!input->is_empty()) {
        node_t* token = input->pop();

        if (et->is_op(token)) {
            token->right = ep->pop();
            token->left = ep->pop();
            ep->push(token);
        } else {
            ep->push(token);
        }
    }

    m_proot = ep->pop();

    delete ep;
    delete et;
    delete input;
}

void ExprTree::b_print()
{
    b_print(m_proot);
}

void ExprTree::m_print()
{
    m_print(m_proot);
}

void ExprTree::a_print()
{
    a_print(m_proot);
}

void ExprTree::b_print(node_t* t)
{
    if (t != NULL) {
        printf("%s ", t->data);
        b_print(t->left);
        b_print(t->right);
    }
}

void ExprTree::m_print(node_t* t)
{
    if (t != NULL) {
        m_print(t->left);
        printf("%s ", t->data);
        m_print(t->right);
    }
}

void ExprTree::a_print(node_t* t)
{
    if (t != NULL) {
        a_print(t->left);
        a_print(t->right);
        printf("%s ", t->data);
    }
}

