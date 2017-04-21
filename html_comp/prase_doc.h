#ifndef _PRASE_DOC_H_
#define _PRASE_DOC_H_

#include <cstdio>

typedef struct proptag {
    char* name;
    char* value;
} prop_t;

typedef struct nodetag {
    char* name;
    prop_t* props;

    struct nodetag* child;
    struct nodetag* next;
} node_t;

typedef struct stacknodetag {
    node_t* value;
    struct stacknodetag* next;
} stacknode_t;

class PraseStack
{
public:
    PraseStack();
    ~PraseStack();

    node_t* pop();
    node_t* get_top();
    void push(node_t* node);

    bool is_empty();

private:
    stacknode_t* m_top;
};

class PraseDoc
{
public:
    PraseDoc(char* filename);
    ~PraseDoc();

    void prase();
    void compare(PraseDoc* pdoc);

    void dump_doc();

private:
    void prase_startnode(FILE* fd, PraseStack& praseStack, int& ch);
    void prase_endnode(FILE* fd, PraseStack& praseStack, int& ch);
    void prase_nodevalue(FILE* fd, PraseStack& praseStack, int& ch);
    void print_node(node_t* node, int prefix);

private:
    char* m_filename;
    node_t* m_pnodes;

private:
    static const int MAX_BUFF = 64;
};

#endif

