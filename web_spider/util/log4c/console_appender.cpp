#include <cstring>
#include <cstdio>
#include "console_appender.h"

ConsoleAppender::ConsoleAppender(char* pname)
{
    if (pname == NULL) {
        pname = (char*)"UNKONW_APPENDER_NAME";
    }

    m_pname = new char[strlen(pname) + 1];
    strcpy(m_pname, pname);
}

ConsoleAppender::~ConsoleAppender()
{
    delete []m_pname;
}

void ConsoleAppender::initall()
{

}

void ConsoleAppender::do_appender(LogEvent* pevent)
{
    printf("[console appender %s] : [%s]\n", m_pname, pevent->get_msg());
}

