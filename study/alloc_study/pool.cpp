#include "pool.h"

void* Pool::alloc()
{
	printf("pool::alloc be called\n");
    if (head == 0) {
        grow();
    }

    // return first elem
    Link* p = head;
    head = p->next;

	printf("pool::alloc end\n");

    return p;
}

void Pool::free(void* chunk)
{
	printf("pool::free be called\n");
    Link* p = static_cast<Link*>(chunk);
    p->next = head;
    head = p;
	printf("pool::free end\n");
}

Pool::Pool(unsigned int size) : esize(size < sizeof(Link) ? sizeof(Link) : size)
{
	printf("pool construct be called\n");
    head = 0;
    chunks = 0;
	printf("pool construct end\n");
}

Pool::~Pool()
{
	printf("pool destruct be called\n");
    Chunk* pchunks = chunks;
    while (pchunks) {
        Chunk* p = pchunks;
        pchunks = pchunks->next;
        delete p;
    }
	printf("pool destruct end\n");

}

void Pool::grow()
{
	printf("pool::grow be called\n");
    Chunk* n = new Chunk();
    n->next = chunks;
    chunks = n;

    const int nelem = size / esize;
    char* start = n->mem;
    char* last = &start[(nelem - 1) * esize];

    for (char* p = start; p < last; p += esize) {
        reinterpret_cast<Link*>(p)->next = reinterpret_cast<Link*>(p + size);
    }

    reinterpret_cast<Link*>(last)->next = 0;
    head = reinterpret_cast<Link*>(start);
	printf("pool::grow end\n");
}

