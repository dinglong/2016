#include <cstring>
#include <cstdio>
#include "filter.h"

Filter::Filter()
{
    filters = new std::vector<char*>();
}

void Filter::add_filter(char* pf)
{
    char* tmp = new char[strlen(pf)];

    strcpy(tmp, pf);
    filters->push_back(tmp);
}

void Filter::del_filter(char* pf)
{
    // TODO
}

bool Filter::pass(const char* pv)
{
    std::vector<char*>::iterator iter = filters->begin();
    for (; iter != filters->end(); iter++) {
        if (0 == strncmp(*iter, pv, strlen(*iter)) && NULL != strstr(pv, ".html")) {
            return true;
        }
    }

    return false;
}

Filter::~Filter()
{
    if (filters != NULL) {
        std::vector<char*>::iterator iter = filters->begin();
        for (; iter != filters->end(); iter++) {
            delete *iter;
        }

        filters->clear();
        delete filters;
    }
}

