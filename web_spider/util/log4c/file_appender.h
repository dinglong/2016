#ifndef _FILE_APPENDER_H_
#define _FILE_APPENDER_H_

#include "appender.h"
#include "log_event.h"

class FileAppender : public Appender
{
public:
    FileAppender(char* pname);
    ~FileAppender();

    void initall();
    void do_appender(LogEvent* pevent);

private:
    char* m_pname;
};

#endif

