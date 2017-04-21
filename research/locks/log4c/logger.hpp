#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#include "props.hpp"

class logger_t
{
public:
    static logger_t* get_logger();

    void info(const char* format, ...);
    void debug(const char* format, ...);
    void trace(const char* format, ...);

private:
    logger_t(int l = INFO);
    ~logger_t() {};

    int do_log(char* msg);
    int get_level(std::string* level);

private:
    static logger_t* logger;
    int level;
    props_t props;

    const static int OFF;
    const static int INFO;
    const static int DEBUG;
    const static int TRACE;

    const static std::string S_OFF;
    const static std::string S_INFO;
    const static std::string S_DEBUG;
    const static std::string S_TRACE;

    const static int MAX_BUFF_LEN;
};

#endif
