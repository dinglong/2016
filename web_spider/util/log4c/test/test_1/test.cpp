#include <cstdio>
#include "../../logger_factory.h"

int main(int argc, char* argv[])
{
    char* configs[2][2];
    configs[0][0] = (char*)"testappender";
    configs[0][1] = (char*)"file";
    configs[1][0] = NULL;
    configs[1][1] = NULL;

    Logger* logger = LoggerFactory::get_logger((char*)"mylogger", Logger::LEVEL_TRACE, configs);

    if (logger != NULL) {
        logger->info("this is info log.");
        logger->debug("this is debug log.");
        logger->trace("this is trace log.");
    }

    return 0;
}

