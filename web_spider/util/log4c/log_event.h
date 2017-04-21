#ifndef _LOG_EVENT_H_
#define _LOG_EVENT_H_

class LogEvent
{
public:
    LogEvent(char* msg);

    char* get_msg();

private:
    char* m_pmsg;
};

#endif

