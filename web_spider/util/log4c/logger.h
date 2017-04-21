#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <vector>
#include "appender.h"

class Logger
{
public:
    /*
     * 定义Log的级别
     */
    static const int LEVEL_DEBUG = 0;
    static const int LEVEL_INFO  = 1;
    static const int LEVEL_TRACE = 2;

public:
    Logger(char* pname, int level);
    ~Logger();

    /*
     * 使用configs对logger进行初始化
     *
     * config形式：
     * ----------------------------
     * | <appender_name> | <type> |
     * ----------------------------
     * | ......          | ...... |
     * ----------------------------
     * | NULL            | NULL   |
     * ----------------------------
     */
    void initall(char* configs[][2]);

    void debug(const char* format, ...);
    void info(const char* format, ...);
    void trace(const char* format, ...);

private:
    void do_appender(char* pmsg);

private:
    int m_level;
    char* m_pname;
    std::vector<Appender*> m_vec_appenders; ///< 属于该logger的appender
};

#endif

