#ifndef _REQUEST_H_
#define _REQUEST_H_

#include "node.h"

#define MAX_REQ_LEN 1024

class Request
{
public:
    Request();
    ~Request();

    /**
     * 创建socket
     */
    bool init();

    /**
     * 销毁socket
     */
    void destory();

    int send(Node* node);

private:
    int   m_fd;  ///< 用于发送请求的socket
    char* m_req; ///< 构造http请求
};

#endif

