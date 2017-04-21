#include "locks_c.hpp"

lock_c_t::lock_c_t()
{

}

lock_c_t::~lock_c_t()
{

}

// bind到指定的服务器
int lock_c_t::bind()
{
    return 0;
}

// 在服务文件系统中创建文件
int lock_c_t::make_file()
{
    return 0;
}

// 使用文件进行互斥操作
int lock_c_t::lock()
{
    return 0;
}

int lock_c_t::unlock()
{
    return 0;
}

// 处理服务端发送的命令
int lock_c_t::invoke(char* cmd)
{
    return 0;
}
