#include <cstring>
#include <cstdio>
#include "logger_factory.h"
#include "../props/props.h"

const std::string LoggerFactory::LOGGER_NAME = "logger.name";
const std::string LoggerFactory::LOGGER_LEVEL = "logger.level";
const std::string LoggerFactory::LOGGER_APPENDER_TYPE = "logger.appender.type";
const std::string LoggerFactory::LOGGER_APPENDER_NAME = "logger.appender.name";

std::map<char*, Logger*> LoggerFactory::m_map_loggers;

Logger* LoggerFactory::get_logger(char* name, int level, char* config[][2])
{
    if (name != NULL) {
        // 先查找，如果已经有这个名字的logger直接返回
        std::map<char*, Logger*>::iterator it = m_map_loggers.begin();
        for (; it != m_map_loggers.end(); it++) {
            if (0 == strcmp(it->first, name)) {
                return it->second;
            }
        }

        // 没有，创建新的
        char* tn = new char[strlen(name) + 1];
        strcpy(tn, name);

        Logger* logger = new Logger(tn, level);
        logger->initall(config);
        m_map_loggers.insert(std::pair<char*, Logger*>(tn, logger));

        return logger;
    }

    return NULL;
}

Logger* LoggerFactory::get_logger(char* props_name)
{
    if (props_name != NULL) {
        Props* props = new Props();

        props->load(props_name);

        std::string* logger_name = props->get_prop(&LOGGER_NAME);
        std::string* logger_level = props->get_prop(&LOGGER_LEVEL);
        std::string* appender_type = props->get_prop(&LOGGER_APPENDER_TYPE);
        std::string* appender_name = props->get_prop(&LOGGER_APPENDER_NAME);

        if (logger_name != NULL &&
                logger_level != NULL &&
                appender_type != NULL &&
                appender_name != NULL) {
            char* configs[2][2];

            // TODO 由于存在从 string 到 char* 的转换，因此应该后期考虑 const 参数的兼容
            configs[0][0] = (char*)(appender_name->c_str());
            configs[0][1] = (char*)(appender_type->c_str());
            configs[1][0] = NULL;
            configs[1][1] = NULL;

            return get_logger((char*)(logger_name->c_str()), stolevel(logger_level->c_str()), configs);
        }
    }

    return NULL;
}

int LoggerFactory::stolevel(const char* slevel)
{
    if (strcmp(slevel, "debug") == 0) {
        return Logger::LEVEL_DEBUG;
    } else if (strcmp(slevel, "info") == 0) {
        return Logger::LEVEL_INFO;
    } else if (strcmp(slevel, "trace") == 0) {
        return Logger::LEVEL_TRACE;
    } else {
        return -1;
    }
}

