#include "platform_def.hpp"
#include "socket_warp.hpp"
#include "util.hpp"

/**
 * 初始化windows socket数据
 */
int socket_warp_t::init()
{
#ifdef WIN32
	WSADATA  ws;
	if ( WSAStartup(MAKEWORD(2,2), &ws) != 0 ) {
		return -1;
	}
#endif
	return 0;
}

/**
 * 清理windows socket数据
 */
int socket_warp_t::uninit()
{
#ifdef WIN32
	WSACleanup();
#endif
	return 0;
}

int socket_warp_t::ls_socket(int domain, int type, int protocol)
{
	int fd = (int)socket(domain, type, protocol);
    util_t::assert_ret(fd);

	return fd;
}

/**
 * bind指定的ip port
 */
int socket_warp_t::ls_bind(int fd, char* ip, int port)
{
	sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
	util_t::ls_inet_aton(ip, addr);

	int ret = bind(fd, (sockaddr*)&addr, sizeof(addr));
    util_t::assert_ret(ret);

	return ret;
}

int socket_warp_t::ls_listen(int fd, int backlog)
{
	int ret = listen(fd, 1024);
    util_t::assert_ret(ret);

	return ret;
}

int socket_warp_t::ls_accept(int fd, struct sockaddr* addr, socklen_t* len)
{
	int cfd = accept(fd, (sockaddr*)&addr, len);
    util_t::assert_ret(cfd);

	return cfd;
}

/**
 * 连接到指定的ip port
 */
int socket_warp_t::ls_connect(int fd, char* ip, int port)
{
	sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
	util_t::ls_inet_aton(ip, addr);

	int ret = connect(fd, (sockaddr*)&addr, sizeof(addr));
    util_t::assert_ret(ret);

	return ret;
}
