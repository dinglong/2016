#ifndef _FILTER_H_
#define _FILTER_H_

#include <vector>

class Filter
{
public:
    Filter();

    void add_filter(char* pf);
    void del_filter(char* pf);

    bool pass(const char* pv);

    ~Filter();

private:
    std::vector<char*>* filters; ///<  过滤条件
};

#endif

