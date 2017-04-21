#include "log_event.h"

LogEvent::LogEvent(char* msg)
{
    m_pmsg = msg;
}

char* LogEvent::get_msg()
{
    return m_pmsg;
}

