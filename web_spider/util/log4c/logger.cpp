#include <cstdarg>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include "logger.h"
#include "console_appender.h"
#include "file_appender.h"

#ifdef  MAX_BUFF_LEN
#undef  MAX_BUFF_LEN
#endif

#define MAX_BUFF_LEN 256;

Logger::Logger(char* pname, int level)
{
    if (pname != NULL) {
        pname = (char*)"UNKONW_NAME";
    }

    m_pname = new char[strlen(pname) + 1];
    strcpy(m_pname, pname);

    m_level = level;
}

Logger::~Logger()
{
    delete []m_pname;
}

void Logger::initall(char* configs[][2])
{
    int index = 0;

    while (true) {

        if (configs[index][0] == NULL && configs[index][1] == NULL) {
            break;
        } else {
            Appender* pa = NULL;
            if (configs[index][1] == NULL || 0 == strcmp(configs[index][1], Appender::TYPE_CONSOLE)) {
                // 默认使用 console 类型 appender
                pa = new ConsoleAppender(configs[index][0]);
            } else if (0 == strcmp(configs[index][1], Appender::TYPE_FILE)) {
                pa = new FileAppender(configs[index][0]);
            } else {
                printf("unkown appender type %s\n", configs[index][1]);
            }

            if (pa != NULL) {
                pa->initall();
                m_vec_appenders.push_back(pa);
            }
        }

        index++;
    }
}

void Logger::debug(const char* format, ...)
{
    if (m_level == LEVEL_DEBUG || m_level == LEVEL_INFO || m_level == LEVEL_TRACE) {
        // 不定长参数的处理，该段代码copy自 vsnprintf 的 man 手册
        // TODO 后期考虑实现为宏，避免其他函数中的代码 copy
        int n = 0;
        int size = MAX_BUFF_LEN;
        char* pmsg = NULL;
        va_list ap;

        if ((pmsg = (char*)malloc(size)) != NULL) {
            while (true) {
                va_start(ap, format);
                n = vsnprintf(pmsg, size, format, ap);
                va_end(ap);

                if (n > -1 && n < size) {
                    break;
                }

                // 分配更多的空间
                if (n > -1) {
                    size = n + 1; // glibc 2.1，精确分配
                } else {
                    size *= 2;  // glibc 2.0，分配原有大小的两倍
                }

                char* temp = NULL;
                if ((temp = (char*)realloc(pmsg, size)) == NULL) {
                    free(pmsg);
                    pmsg = NULL;
                } else {
                    pmsg = temp;
                }
            }
        }

        do_appender(pmsg);
    }
}


void Logger::info(const char* format, ...)
{
    if (m_level == LEVEL_INFO || m_level == LEVEL_TRACE) {
        // TODO 存在代码的复制
        int n = 0;
        int size = MAX_BUFF_LEN;
        char* pmsg = NULL;
        va_list ap;

        if ((pmsg = (char*)malloc(size)) != NULL) {
            while (true) {
                va_start(ap, format);
                n = vsnprintf(pmsg, size, format, ap);
                va_end(ap);

                if (n > -1 && n < size) {
                    break;
                }

                // 分配更多的空间
                if (n > -1) {
                    size = n + 1; // glibc 2.1，精确分配
                } else {
                    size *= 2;  // glibc 2.0，分配原有大小的两倍
                }

                char* temp = NULL;
                if ((temp = (char*)realloc(pmsg, size)) == NULL) {
                    free(pmsg);
                    pmsg = NULL;
                } else {
                    pmsg = temp;
                }
            }
        }

        do_appender(pmsg);
    }
}


void Logger::trace(const char* format, ...)
{
    if (m_level == LEVEL_TRACE) {
        // TODO 存在代码的复制
        int n = 0;
        int size = MAX_BUFF_LEN;
        char* pmsg = NULL;
        va_list ap;

        if ((pmsg = (char*)malloc(size)) != NULL) {
            while (true) {
                va_start(ap, format);
                n = vsnprintf(pmsg, size, format, ap);
                va_end(ap);

                if (n > -1 && n < size) {
                    break;
                }

                // 分配更多的空间
                if (n > -1) {
                    size = n + 1; // glibc 2.1，精确分配
                } else {
                    size *= 2;  // glibc 2.0，分配原有大小的两倍
                }

                char* temp = NULL;
                if ((temp = (char*)realloc(pmsg, size)) == NULL) {
                    free(pmsg);
                    pmsg = NULL;
                } else {
                    pmsg = temp;
                }
            }
        }

        do_appender(pmsg);
    }
}

void Logger::do_appender(char* pmsg)
{
    // 构造成LogEvent，依次调用appender的do_appender方法
    if (pmsg != NULL && !m_vec_appenders.empty()) {
        LogEvent* pevent = new LogEvent(pmsg);

        std::vector<Appender*>::iterator it = m_vec_appenders.begin();
        for (; it != m_vec_appenders.end(); it++) {
            (*it)->do_appender(pevent);
        }

        delete pevent;
        delete pmsg; /// 注意，在此统一释放 pmsg
    }
}

