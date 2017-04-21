#include <cstdio>
#include <cstdlib>
#include <assert.h>
#include "../util/util.h"
#include "../util/base_data.h"

typedef struct nodetag {
    char data;
    int high;
    nodetag* left;
    nodetag* right;
} node;

int max(int a, int b)
{
    return (a > b ? a : b);
}

int high(node* tree)
{
    if (tree == NULL) {
        return -1;
    } else {
        return tree->high;
    }
}

node* left_route(node* tree)
{
    printf("-- left route -- %c --\n", tree->data);

    node* tree_left = tree->left;
    tree->left = tree->left->right;
    tree_left->right = tree;

    tree->high = max(high(tree->left), high(tree->right));
    tree_left->high = max(high(tree_left->left), tree->high);

    return tree_left;
}

node* right_route(node* tree)
{
    printf("-- right route -- %c --\n", tree->data);

    node* tree_right = tree->right;
    tree->right = tree->right->left;
    tree_right->left = tree;

    tree->high = max(high(tree->left), high(tree->right));
    tree_right->high = max(high(tree_right->right), tree->high);

    return tree_right;
}

node* double_route_left(node* tree)
{
    printf("-- double route left -- %c --\n", tree->data);

    tree->left = right_route(tree->left);
    return left_route(tree);
}

node* double_route_right(node* tree)
{
    printf("-- double route right -- %c --\n", tree->data);

    tree->right = left_route(tree->right);
    return right_route(tree);
}

node* insert(node* tree, node* n)
{
    assert(n != NULL);

    if (tree == NULL) {
        tree = n;
    } else if (n->data < tree->data) {
        tree->left = insert(tree->left, n);
        if (high(tree->left) - high(tree->right) == 2) {
            if (n->data < tree->left->data) {
                tree = left_route(tree);
            } else {
                tree = double_route_left(tree);
            }
        }
    } else if (n->data > tree->data) {
        tree->right = insert(tree->right, n);
        if (high(tree->right) - high(tree->left) == 2) {
            if (n->data > tree->right->data) {
                tree = right_route(tree);
            } else {
                tree = double_route_right(tree);
            }
        }
    } else {
        // 已经存在的节点，不处理
    }

    tree->high = max(high(tree->left), high(tree->right)) + 1;
    return tree;
}

void pre_traversal(node* tree)
{
    if (tree != NULL) {
        printf("%c ", tree->data);
        pre_traversal(tree->left);
        pre_traversal(tree->right);
    }
}

void mid_traversal(node* tree)
{
    if (tree != NULL) {
        mid_traversal(tree->left);
        printf("%c ", tree->data);
        mid_traversal(tree->right);
    }
}

node* make_node(char data)
{
    node* p = new node();

    if (p == NULL) {
        printf("alloc node mem error\n");
        exit(1);
    }

    p->data = data;
    p->high = 0;
    p->left = NULL;
    p->right = NULL;

    return p;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("usage: %s <test_data_file>\n", argv[0]);
        return 1;
    }

    node* tree = NULL;

    Data<char> data;
    data.load(argv[1], get_char);
    char* datas = data.get_data();
    int size = data.get_size();

    // create tree
    for (int i = 1; i <= size; i++) {
        printf("data is [%c]\n", datas[i]);
        tree = insert(tree, make_node(datas[i]));
    }

    // pre trasveral
    printf("pre trasveral: ");
    pre_traversal(tree);
    printf("\n");

    // mid trasveral
    printf("mid trasveral: ");
    mid_traversal(tree);
    printf("\n");

    return 0;
}

