#include "locks_s.hpp"

locks_s_t::locks_s_t()
{
    file_system = new dir_tree_t();
}

locks_s_t::~locks_s_t()
{
    delete file_system;
}

int locks_s_t::init()
{
    // TODO 初始化服务socket
    return 0;
}

int locks_s_t::parse_cmd()
{
    char* cmd = NULL;

    // 读socket，解析出命令

    // 分发命令
    dispatch_cmd(cmd);

    return 0;
}

int locks_s_t::dispatch_cmd(char* cmd)
{
    // 根据命令的类型，分发到不同的功能函数
    return 0;
}

int locks_s_t::bind()
{
    return 0;
}

int locks_s_t::make_file()
{
    return 0;
}

int locks_s_t::lock()
{
    return 0;
}

int locks_s_t::unlock()
{
    return 0;
}

int locks_s_t::notify()
{
    return 0;
}
