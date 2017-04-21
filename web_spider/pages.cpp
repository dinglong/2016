#include <cstring>
#include <cstdio>
#include "pages.h"

Pages::Pages()
{
    m_requester = new Request();
    m_replyer = new Reply();
    m_analysor = new Analysor();
}

Pages::~Pages()
{
    if (m_requester != NULL) {
        delete m_requester;
    }
    if (m_replyer != NULL) {
        delete m_replyer;
    }
    if (m_analysor != NULL) {
        delete m_analysor;
    }
}

bool Pages::init()
{
    return m_requester->init();
}

char* Pages::next()
{
    // 初始化链接
    m_requester->init();

    // 向这个node发送http请求
    int fd = -1;
    Node* pnode = NULL;
    if (m_new_nodes.size() > 0) {
        pnode = m_new_nodes.front();
        fd = m_requester->send(pnode);
    }

    // 接受网络回复
    char* reply = NULL;
    if (fd > 0) {
        do {
            reply = m_replyer->read(fd);

            if (reply != NULL) {
                // 分析这个回复，将其中的url作为节点再加入到node list中
                if (reply != NULL) {
                    char* url = NULL;
                    m_analysor->set_content(reply);
                    while (NULL != (url = m_analysor->get_url())) {
                        add_node(new Node(url));
                    }
                }

                // 将刚分析过的node加入到已分析队列中
                if (pnode != NULL) {
                    m_new_nodes.pop_front();
                    m_old_nodes.push_back(pnode);
                }
            }
        } while (reply != NULL);

        // 释放链接
        m_requester->destory();
    }

    return reply;
}

void Pages::add_node(Node* pnode)
{
    if (!contain(m_old_nodes, pnode) && !contain(m_new_nodes, pnode)) {
        m_new_nodes.push_back(pnode);
    }
}

void Pages::del_node(Node* pnode)
{
    /*
    std::list<Node*>::iterator iter = m_new_nodes.begin();
    for (; iter != m_new_nodes.end(); iter++) {
        Node* value = *iter;
        if (value->equal(*pnode)) {
            m_new_nodes.erase(iter);
            return 0;
        }
    }
    */
}

bool Pages::contain(const std::list<Node*> ref_nodes, const Node* pnode)
{
    std::list<Node*>::const_iterator iter = ref_nodes.begin();
    for (; iter != ref_nodes.end(); iter++) {
        Node* value = *iter;
        if (value->equal(*pnode)) {
            return true;
        }
    }
    return false;
}

int Pages::has_node()
{
    return (m_new_nodes.size() + m_old_nodes.size());
}

int Pages::has_new()
{
    return m_new_nodes.size();
}

