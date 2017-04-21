#ifndef _NODE_H_
#define _NODE_H_

typedef struct Node {
    char* data;
    struct Node* left;
    struct Node* right;
} node_t;

#endif

