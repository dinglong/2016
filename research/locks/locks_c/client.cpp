#include <cstdio>
#include "platform_def.hpp"
#include "util.hpp"
#include "msg.hpp"
#include "socket_warp.hpp"
#include "type.hpp"

int main(int argc, char* argv[])
{
	socket_warp_t::init();

    int fd = socket_warp_t::ls_socket(AF_INET, SOCK_STREAM, 0);
    socket_warp_t::ls_connect(fd, "127.0.0.1", 6700);

	int x = 101;

	msg_t msg_0;
    msg_0.type = T_FUNC_NAME;
    msg_0.data = (char*)"test_func_t";
    msg_0.len = strlen(msg_0.data);

	msg_t msg_1;
    msg_1.type = T_PARAM;
    msg_1.data = (char*)&x;
    msg_1.len = sizeof(int);

	msg_t msg_2;
    msg_2.type = T_PARAM;
    msg_2.data = (char*)"hello world";
    msg_2.len = strlen(msg_2.data);

	int size_0;
	int size_1;
	int size_2;
	char* buff_0 = msg_util_t::encord(&msg_0, size_0);
	char* buff_1 = msg_util_t::encord(&msg_1, size_1);
	char* buff_2 = msg_util_t::encord(&msg_2, size_2);

	char* sum_buff = (char*) malloc(size_0 + size_1 + size_2);
	memcpy(sum_buff, buff_0, size_0);
	memcpy(sum_buff + size_0, buff_1, size_1);
	memcpy(sum_buff + size_0 + size_1, buff_2, size_2);

    msg_t msg;
    msg.type = T_RPC;
    msg.data = sum_buff;
    msg.len = size_0 + size_1 + size_2;

    int size = 0;
    char* buff = msg_util_t::encord(&msg, size);

    int len = util_t::write_n(fd, buff, size);
    fprintf(stderr, "write len: %d\n", len);

    // util_t::ls_sleep(100);
    util_t::ls_close(fd);
	socket_warp_t::uninit();

    return 0;
}

