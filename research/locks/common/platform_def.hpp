#ifndef _PLATFORM_DEF_HPP_
#define _PLATFORM_DEF_HPP_

#ifdef WIN32
	#include <Ws2tcpip.h>
	#include <windows.h>

	#pragma comment(lib, "Ws2_32.lib")
#elif
	#include <unistd.h>
	#include <arpa/inet.h>
#endif

#endif
