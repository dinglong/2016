#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "expr_translate.h"

int pri_table[7][7] = {
    // #   +   -   *   /   (   )
    { -1, -1, -1, -1, -1, -1, -1},
    { +1, +1, +1, -1, -1, -1, +1},
    { +1, +1, +1, -1, -1, -1, +1},
    { +1, +1, +1, +1, +1, -1, +1},
    { +1, +1, +1, +1, +1, -1, +1},
    { -1, -1, -1, -1, -1, -1, +0},
    { +0, +0, +0, +0, +0, +0, +0}
};

ExprTranslate::ExprTranslate(const char* expr)
{
    m_expr = NULL;

    if (expr != NULL) {
        m_expr = new char[strlen(expr) + 1];
        strcpy(m_expr, expr);
    }
}

ExprTranslate::~ExprTranslate()
{
    if (m_expr != NULL) {
        delete []m_expr;
    }
}

Stack* ExprTranslate::get_middle_expr()
{
    int index = 0;
    node_t* token = NULL;
    Stack* expr_stack = new Stack();

    while ((token = read_token(index)) != NULL) {
        expr_stack->push(token);
    }

    return expr_stack;
}

Stack* ExprTranslate::get_suff_expr()
{
    int index = 0;
    node_t* token = NULL;
    Stack op_stack;
    Stack num_stack;
    Stack* expr_stack = new Stack();

    while ((token = read_token(index)) != NULL) {
        if (is_op(token)) {
            while (true) {
                if (op_stack.is_empty()) {
                    op_stack.push(token);
                    break;
                } else {
                    node_t* top = op_stack.pop();
                    int pri = comp_pri(top, token);
                    if (pri > 0) {
                        expr_stack->push(top);
                        printf("%s ", top->data);
                    } else if (pri < 0) {
                        op_stack.push(top);
                        op_stack.push(token);
                        break;
                    } else {
                        // 左右括号相遇
                    }
                }
            }
        } else {
            expr_stack->push(token);
            printf("%s ", token->data);
        }
    }

    return expr_stack;
}

node_t* ExprTranslate::read_token(int& index)
{
    node_t* token = NULL;

    if (m_expr[index] == '\0') {
        return NULL;
    }

    while (m_expr[index] == ' ') {
        index++;
    }

    int begin = index;
    int end = index;
    while (!is_op(m_expr[index]) && m_expr[index] != '\0') {
        end++;
        index++;
    }

    if (begin < end) {
        token = new node_t();
        int len = end - begin;
        token->data = new char[len];
        strncpy(token->data, &m_expr[begin], len);
        token->data[len] = '\0';
    } else if (is_op(m_expr[index])) {
        token = new node_t();
        token->data = new char[2];
        token->data[0] = m_expr[index];
        token->data[1] = '\0';
        index++;
    }

    fprintf(stderr, "token [%s]\n", token->data);

    return token;
}

bool ExprTranslate::is_op(char ch)
{
    if (ch == '#'
            || ch == '+'
            || ch == '-'
            || ch == '*'
            || ch == '/'
            || ch == '('
            || ch == ')') {
        return true;
    }

    return false;
}

bool ExprTranslate::is_op(node_t* token)
{
    return is_op(token->data[0]);
}

int ExprTranslate::comp_pri(node_t* t1, node_t* t2)
{
    int row = get_index(t1);
    int col = get_index(t2);

    fprintf(stderr, "pri_table[%s][%s]=[%d]\n", t1->data, t2->data, pri_table[row][col]);

    return pri_table[row][col];
}

int ExprTranslate::get_index(node_t* token)
{
    int index = -1;
    switch (token->data[0]) {
    case '#':
        index = 0;
        break;
    case '+':
        index = 1;
        break;
    case '-':
        index = 2;
        break;
    case '*':
        index = 3;
        break;
    case '/':
        index = 4;
        break;
    case '(':
        index = 5;
        break;
    case ')':
        index = 6;
        break;
    default:
        fprintf(stderr, "error op [%c]\n", token->data[0]);
        exit(1);
    }
    return index;
}

