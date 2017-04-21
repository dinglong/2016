#include <cstring>
#include <cstdio>
#include "file_appender.h"

FileAppender::FileAppender(char* pname)
{
    if (pname == NULL) {
        pname = (char*)"UNKONW_APPENDER_NAME";
    }

    m_pname = new char[strlen(pname) + 1];
    strcpy(m_pname, pname);
}

FileAppender::~FileAppender()
{
    delete []m_pname;
}

void FileAppender::initall()
{

}

void FileAppender::do_appender(LogEvent* pevent)
{
    printf("[file appender %s] : [%s]\n", m_pname, pevent->get_msg());
}

