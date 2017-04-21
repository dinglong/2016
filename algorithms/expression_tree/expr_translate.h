#ifndef _EXPR_TRANSLATE_H_
#define _EXPR_TRANSLATE_H_

#include "stack.h"
#include "node.h"

class ExprTranslate
{
public:
    ExprTranslate(const char* expr);
    ~ExprTranslate();

    Stack* get_middle_expr();
    Stack* get_suff_expr();

    bool is_op(node_t* token);

private:
    node_t* read_token(int& index);
    bool is_op(char ch);
    int get_index(node_t* token);
    int comp_pri(node_t* t1, node_t* t2);

private:
    char* m_expr;
};

#endif

