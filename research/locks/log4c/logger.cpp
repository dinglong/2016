#include <cstdio>
#include <cstdarg>
#include "logger.hpp"

logger_t* logger_t::logger = NULL;

const int logger_t::OFF = -1;
const int logger_t::INFO = 0;
const int logger_t::DEBUG = 1;
const int logger_t::TRACE = 2;

const std::string logger_t::S_OFF = "OFF";
const std::string logger_t::S_INFO = "INFO";
const std::string logger_t::S_DEBUG = "DEBUG";
const std::string logger_t::S_TRACE = "TRACE";

const int logger_t::MAX_BUFF_LEN = 512;

logger_t* logger_t::get_logger()
{
    if (logger == NULL) {
        logger = new logger_t();
    }
    return logger;
}

logger_t::logger_t(int l) : level(l)
{
    props.load("log4c.props");
    std::string* level = props.get_prop("ls.logger.level");
    if (level != NULL) {
        this->level = get_level(level);
    }
};

void logger_t::info(const char* format, ...)
{
    if (level <= INFO) {
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

        do_log(pmsg);
    }
}

void logger_t::debug(const char* format, ...)
{
    if (level <= DEBUG) {
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

        do_log(pmsg);
    }
}

void logger_t::trace(const char* format, ...)
{
    if (level <= TRACE) {
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

        do_log(pmsg);
    }
}

int logger_t::do_log(char* msg)
{
    printf("%s", msg);
    return 0;
}

int logger_t::get_level(std::string* level)
{
    if (level->compare(S_INFO) == 0) {
        return INFO;
    } else if (level->compare(S_DEBUG) == 0) {
        return DEBUG;
    } else if (level->compare(S_TRACE) == 0) {
        return TRACE;
    } else if (level->compare(S_OFF) == 0) {
        return OFF;
    }
    return INFO;
}

int mainx(char* argc, char* argv[])
{
    logger_t* logger = logger_t::get_logger();

    logger->info("%s\n", "this is info log.");
    logger->debug("%s\n", "this is debug log.");
    logger->trace("%s\n", "this is trace log.");

    return 0;
}
