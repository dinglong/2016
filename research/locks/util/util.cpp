#include <cstdlib>
#include "platform_def.hpp"
#include "util.hpp"

/**
 * 断言返回值大于等于0
 */
void util_t::assert_ret(int ret)
{
    if (ret < 0) {
        perror("assert ret error");
        abort();
    }
}

/**
 * 从fd中读指定字节的数据
 */
int util_t::read_n(int fd, char* buff, int size)
{
    int count = 0;

    while (count < size) {
		#ifdef WIN32
		int len = recv((SOCKET)fd, buff + count, size - count, 0);
		#elif
		int len = read(fd, buff + count, size - count);
		#endif

        if (len < 0) {
            printf("read msg error, maybe client is closed\n");
            count = -1;
            break;
        } else if (len == 0) {
            printf("no any data to read\n");
            count = -1;
            break;
        } else {
            count += len;
        }
    }

    return count;
}

/**
 * 向fd写指定字节的数据
 */
int util_t::write_n(int fd, char* buff, int size)
{   
	// TODO
#ifdef WIN32
	return send((SOCKET)fd, buff, size, 0);
#elif
	return write(fd, buff, size);
#endif

    return 0;
}

/**
 * 将点分十进制转化为sockaddr 
 */
int util_t::ls_inet_aton(char* caddr, sockaddr_in& saddr)
{
#ifdef WIN32
	saddr.sin_addr.s_addr = inet_addr(caddr);
	return 0;
#elif
	return inet_aton(caddr, &saddr.sin_addr);
#endif
}

/**
 * 封装跨平台的sleep
 */
void util_t::ls_sleep(int time)
{
#ifdef WIN32
	Sleep(1000 * time);
#elif
	sleep(time);
#endif
}

/**
 * 对fd进行关闭处理
 */
void util_t::ls_close(int fd)
{
#ifdef WIN32
	closesocket(fd);
#elif
	close(fd);
#endif
}
