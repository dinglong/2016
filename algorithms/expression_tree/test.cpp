#include <cstdio>
#include "tree.h"
#include "expr_translate.h"

int main(int argc, char* argv[])
{
    char* expr = (char*)"#a+b*c+(d+f)+g#";

    // char* expr = (char*)"#a+b#";

    // char* expr = argv[1];
    printf("expr [%s]\n", expr);

    ExprTranslate* pe = new ExprTranslate(expr);
    pe->get_suff_expr();

    printf("\n--- test expr tree ----\n");

    ExprTree* t = new ExprTree();
    t->construct(expr);

    printf("\nbefore translate\n");
    t->b_print();
    printf("\nmiddle translate\n");
    t->m_print();
    printf("\nafter  translate\n");
    t->a_print();

    printf("\n");

    return 0;
}

