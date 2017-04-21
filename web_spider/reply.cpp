#include <cstring>
#include <assert.h>
#include <unistd.h>
#include "reply.h"

Reply::Reply()
{
    m_buff = new char[MAX_BUFF];
}

Reply::~Reply()
{
    if (m_buff != NULL) {
        delete []m_buff;
    }
}

char* Reply::read(int fd)
{
    int cnt = 0; // 目前已经读取的字节数
    char buff[4];

    while (::read(fd, buff, 1) == 1) {
        m_buff[cnt++] = buff[0];
    }

    assert(cnt < MAX_BUFF);
    m_buff[cnt] = '\0';

    if (cnt  > 0) {
        return m_buff;
    } else {
        return NULL;
    }
}

