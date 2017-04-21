#ifndef _LOCKS_C_HPP_
#define _LOCKS_C_HPP_

class lock_c_t
{
public:
    lock_c_t();
    ~lock_c_t();

    // bind到指定的服务器
    int bind();

    // 在服务文件系统中创建文件
    int make_file();

    // 使用文件进行互斥操作
    int lock();
    int unlock();

    // 处理服务端发送的命令
    int invoke(char* cmd);

private:
    // TODO
};

#endif
