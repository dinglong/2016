#ifndef _PAGES_H_
#define _PAGES_H_

#include <list>
#include "node.h"
#include "request.h"
#include "reply.h"
#include "analysor.h"

class Pages
{
public:
    Pages();
    ~Pages();

    bool init();
    char* next();
    void add_node(Node* pnode);
    void del_node(Node* pnode);

    int has_node();
    int has_new();

private:
    bool contain(const std::list<Node*> ref_nodes, const Node* pnode);

private:
    std::list<Node*> m_new_nodes; ///< 等待分析的node
    std::list<Node*> m_old_nodes; ///< 已经分析过的node
    Request* m_requester;
    Reply* m_replyer;
    Analysor* m_analysor;
};

#endif

