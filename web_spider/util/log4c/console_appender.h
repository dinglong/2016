#ifndef _CONSOLE_APPENDER_H_
#define _CONSOLE_APPENDER_H_

#include "appender.h"
#include "log_event.h"

class ConsoleAppender : public Appender
{
public:
    ConsoleAppender(char* pname);
    ~ConsoleAppender();

    void initall();
    void do_appender(LogEvent* pevent);

private:
    char* m_pname;
};

#endif

