#ifndef _UTIL_HPP_
#define _UTIL_HPP_

#include <cstdio>
#include <cstring>
#include "platform_def.hpp"

class util_t
{
public:
    // 断言返回值
    static void assert_ret(int ret);

    // 从fd中读出指定长度的数据
    static int read_n(int fd, char* buff, int size);

    // 向fd中写入指定长度的数据
    static int write_n(int fd, char* buff, int size);

	static int ls_inet_aton(char* caddr, sockaddr_in& saddr);

	static void ls_sleep(int time);

	static void ls_close(int fd);
};

#endif
