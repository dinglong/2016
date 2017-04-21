#include "platform_def.hpp"
#include "util.hpp"
#include "msg.hpp"
#include "service.hpp"
#include "socket_warp.hpp"
#include "base_func.hpp"
#include "type.hpp"

service_t::service_t()
{
	logger = logger_t::get_logger();
	socket_warp_t::init();
}

service_t::~service_t()
{
	socket_warp_t::uninit();
}

int service_t::init(int service_port)
{
    service_fd = socket_warp_t::ls_socket(AF_INET, SOCK_STREAM, 0);
	socket_warp_t::ls_bind(service_fd, "0.0.0.0", service_port);
    socket_warp_t::ls_listen(service_fd, 1024);

    return 0;
}

/**
 * 启动服务
 */
void service_t::run()
{
    // TODO 多线程方式运行
    sockaddr_in caddr;
    socklen_t caddr_len = sizeof(sockaddr);
    int cfd = socket_warp_t::ls_accept(service_fd, (sockaddr*)&caddr, &caddr_len);

    while (true) {
        msg_t* msg_rpc = msg_util_t::create_msg();
        msg_util_t::read_msg(cfd, msg_rpc);

		if(msg_rpc->type == T_RPC) {
			msg_t* msg_name = msg_util_t::create_msg();
			char* buff = msg_util_t::read_msg(msg_rpc->data, msg_name);

			logger->debug("read msg data [%s].\n", msg_name->data);

			// 解析出函数名
			if(msg_name->type == T_FUNC_NAME) {
				std::map<char*, base_func_t*, comp_t>::iterator it = func_table.find(msg_name->data);
				if(it != func_table.end()) {
					base_func_t* fc = it->second;
					fc->invoke(buff);
				}
			}

			msg_util_t::destroy_msg(msg_name);
		}

		msg_util_t::destroy_msg(msg_rpc);
    }
}

/**
 * 向函数映射表中填入映射关系
 */
int service_t::regist_func(char* name, base_func_t* func)
{
    if (func_table.find(name) != func_table.end()) {
        return -1;
    }

    logger->debug("regist_func [%s].\n", name);

    func_table.insert(std::pair<char*, base_func_t*>(name, func));
    return 0;
}
