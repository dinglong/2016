#ifndef _APPENDER_H_
#define _APPENDER_H_

#include "log_event.h"
#include "layout.h"

/**
 * 定义appender的统一接口
 */
class Appender
{
public:
    static const char* TYPE_CONSOLE;
    static const char* TYPE_FILE;

public:
    /*
     * 作特定的初始化工作
     */
    virtual void initall() = 0;

    /*
     * 将log输出到appender
     */
    virtual void do_appender(LogEvent* event) = 0;

private:
    Layout* playout;
};

#endif

