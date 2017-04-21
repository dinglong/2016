#ifndef _LOGGER_FACTORY_H_
#define _LOGGER_FACTORY_H_

#include <map>
#include <string>
#include "logger.h"

class LoggerFactory
{
public:
    static Logger* get_logger(char* props_name);
    static Logger* get_logger(char* pname, int level, char* config[][2]);

private:
    LoggerFactory(); ///< 私有构造函数，防止被实例化

    static int stolevel(const char* slevel);
private:
    static const std::string LOGGER_NAME;
    static const std::string LOGGER_LEVEL;
    static const std::string LOGGER_APPENDER_TYPE;
    static const std::string LOGGER_APPENDER_NAME;

private:
    static std::map<char*, Logger*> m_map_loggers;
};

#endif

