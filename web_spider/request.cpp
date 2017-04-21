#include <errno.h>
#include <cstdio>
#include <cstring>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include "request.h"

Request::Request()
{
    m_req = new char[MAX_REQ_LEN];
}

Request::~Request()
{
    if (m_req != NULL) {
        delete m_req;
    }
}

bool Request::init()
{
    m_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (m_fd < 0) {
        perror("create socket");
        return false;
    }

    return true;
}

void Request::destory()
{
    close(m_fd);
}

int Request::send(Node* node)
{
    // 连接远端
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    addr.sin_addr = *((struct in_addr*)gethostbyname(node->get_addr())->h_addr);

    if (connect(m_fd, (struct sockaddr*)&addr, sizeof(struct sockaddr)) < 0) {
        perror("connect error");
        return -1;
    }

    // 构造 http 请求
    sprintf(m_req, "GET /%s HTTP/1.1\r\n", node->get_page());
    sprintf(m_req, "%sHost: %s\r\n",       m_req, node->get_addr());
    sprintf(m_req, "%sConnection: %s\r\n", m_req, "close");
    sprintf(m_req, "%sUser-Agent: %s\r\n", m_req, "Wget/1.10.2");
    sprintf(m_req, "%s\r\n",               m_req);

    // 发送请求
    size_t send_len = 0;
    size_t has_send = 0;
    size_t sum_len = strlen(m_req);
    while (has_send < sum_len) {
        send_len = ::send(m_fd, m_req + has_send, sum_len, 0);

        if (send_len == -1u) {
            perror("send error\n");
            return -2;
        }

        has_send += send_len;
    }

    return m_fd;
}

