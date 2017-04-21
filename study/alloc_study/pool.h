#ifndef _POOL_H_
#define _POOL_H_

#include <cstdio>

class Pool
{

public:
    Pool(unsigned int size);
    ~Pool();

    void* alloc();
    void free(void* chunk);

private:
    struct Link {
        Link* next;
    };

    enum { size = 8 * 1024 - 16 };
    struct Chunk {
        char mem[size];
        Chunk* next;
    };

    Chunk* chunks;
    const unsigned int esize;
    Link* head;

    Pool(Pool&);
    void operator=(Pool&);

    void grow();
};

#endif

