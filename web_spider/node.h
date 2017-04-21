#ifndef _NODE_H_
#define _NODE_H_

class Node
{
public:
    Node(char* url);
    ~Node();

    bool equal(const Node& node);
    char* get_addr();
    char* get_page();

private:
    char* m_start_pos;  // 开始的位置，排除了http／https
    char* m_middle_pos; // 网址 和 页面 的分割位置
    char* m_url;        // node 关联的 网页地址
};

#endif

