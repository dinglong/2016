#ifndef _SERVICE_HPP_
#define _SERVICE_HPP_

#include <map>
#include <string>
#include "logger.hpp"

class base_func_t;

class comp_t
{
public:
    inline bool operator()(char* x, char* y) {
        return (strcmp(x, y) > 0); 
    } 
};

class service_t
{
public:
	service_t();
	~service_t();

    int init(int port);
    void run();

    // 想函数映射表中填入映射关系
    int regist_func(char* name, base_func_t* func);

private:
    int service_fd;
    std::map<char*, base_func_t*, comp_t> func_table;
	logger_t* logger;
};

#endif
