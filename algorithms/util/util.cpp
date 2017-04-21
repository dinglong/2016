#include <cstring>
#include <cstdlib>
#include <assert.h>
#include "util.h"

char get_char(char* data)
{
    assert(data != NULL);
    return data[0];
}

int get_int(char* data)
{
    assert(data != NULL);
    return atoi(data);
}

char* get_string(char* data)
{
    assert(data != NULL);

    int len = strlen(data);
    assert(len > 0);

    char* ps = new char[len + 1];
    memcpy(ps, data, len + 1);

    return ps;
}

void release_string(char* data)
{
    assert(data != NULL);
    delete []data;
}

