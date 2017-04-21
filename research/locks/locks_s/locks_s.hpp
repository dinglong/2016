#ifndef _LOCKS_S_HPP_
#define _LOCKS_S_HPP_

#include "dir_tree.hpp"

/**
 * 对外提供lock服务
 */
class locks_s_t
{
public:
    locks_s_t();
    ~locks_s_t();

    int init();
    int parse_cmd();

private:
    int dispatch_cmd(char* cmd);

    int bind();
    int make_file();

    int lock();
    int unlock();

    int notify();

private:
    int server_fd;
    dir_tree_t* file_system;
};

#endif
