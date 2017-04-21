#ifndef _BASE_FUNC_HPP_
#define _BASE_FUNC_HPP_

#include <string>

class service_t;

class base_func_t
{
public:
    base_func_t(service_t* s) : service(s) {}
    virtual ~base_func_t() {}

    // 实现请求
    virtual int invoke(char* params) = 0;

    // 获取唯一名
    virtual char* get_name() = 0;

    // 将自己注册到服务框架中
    int regist();

private:
    service_t* service;
};

#endif
