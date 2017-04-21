#include <cstring>
#include <cstdio>
#include "analysor.h"

Analysor::Analysor()
{
    filter = new Filter();
    filter->add_filter((char*)"www"); // TODO 目前默认只识别 www 开头的网址
}

void Analysor::set_content(char* content)
{
    m_curr_pos = content;
}

char* Analysor::get_url()
{
    // 从网页的内容中分析出url，返回；如果分析到结尾未找到，则返回null
    m_curr_pos = strstr(m_curr_pos, "href=\"http://");

    while (m_curr_pos != NULL) {
        char* tmp_pos = m_curr_pos + strlen("href=\"http://") + 1;
        m_curr_pos = strstr(tmp_pos, "\"");

        if (m_curr_pos != NULL) {
            *m_curr_pos++ = '\0';

            if (filter->pass(tmp_pos)) {
                return tmp_pos;
            }
        }
    }

    return NULL;
}

Analysor::~Analysor()
{
    if (filter != NULL) {
        delete filter;
    }
}

