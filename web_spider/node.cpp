#include <cstring>
#include <cstdio>
#include "node.h"

Node::Node(char* url)
{
    printf("url: %s\n", url);

    // 对url进行一份 copy
    size_t len = strlen(url);
    m_url = new char[len + 1];
    memcpy(m_url, url, len + 1);

    // 去除 http 前缀
    m_start_pos = m_url;
    if (strncmp(url, "http", 4) == 0) {
        m_start_pos = strchr(m_url, '/') + 2;
    }

    // 分离出页面
    m_middle_pos = strchr(m_start_pos, '/');
    if (m_middle_pos != NULL) {
        *m_middle_pos++ = '\0'; // 分解成两个字符串
    }
}

Node::~Node()
{
    if (m_url != NULL) {
        delete []m_url;
    }
}

bool Node::equal(const Node& node)
{
    if (strcmp(m_start_pos, node.m_start_pos) == 0 &&
            strcmp(m_middle_pos, node.m_middle_pos) == 0) {
        return true;
    }
    return false;
}

char* Node::get_addr()
{
    return m_start_pos;
}

char* Node::get_page()
{
    return m_middle_pos;
}

