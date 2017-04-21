#ifndef _SOCKET_WRAP_HPP_
#define _SOCKET_WEAP_HPP_

class socket_warp_t
{
public:
	/**
	 * windows平台socket初始化
	 */
	static int init();
	static int uninit();

	/**
	 * 对基本的socket api进行封装
	 */
	static int ls_socket(int domain, int type, int protocol);
	static int ls_bind(int fd, char* ip, int port);
	static int ls_listen(int fd, int backlog);
	static int ls_accept(int fd, struct sockaddr* addr, socklen_t* len);
	static int ls_connect(int fd, char* ip, int port);
};

#endif
