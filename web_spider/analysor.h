#ifndef _ANALYSOR_H_
#define _ANALYSOR_H_

#include "filter.h"

class Analysor
{
public:
    Analysor();

    void set_content(char* content);
    char* get_url();

    ~Analysor();

private:
    char* m_curr_pos; ///< 正在分析的位置
    Filter* filter;
};

#endif

