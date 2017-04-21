#include "pool.h"

template<class T> Pool Pool_alloc<T>::mem(sizeof(T));

template<class T>
Pool_alloc<T>::Pool_alloc() throw()
{
	printf("pool_alloc construct be called\n");
}

template<class T>
Pool_alloc<T>::~Pool_alloc() throw()
{
	printf("pool_alloc destruct be called\n");
}

template<class T>
template<class U> Pool_alloc<T>::Pool_alloc(const Pool_alloc<U>& ref) throw()
{
	printf("pool_alloc copy construct be called\n");
}

template<class T>
T* Pool_alloc<T>::allocate(size_type n, const_pointer hint)
{
	printf("pool_alloc::allocate be called, size: %u\n", n);
    if (n == 1) {
		printf("pool_alloc::allocate end\n");
        return static_cast<T*>(mem.alloc());
    }
	printf("pool_alloc::allocate end\n");
	return 0;
}

template <class T>
void Pool_alloc<T>::deallocate(pointer p, size_type n)
{
	printf("pool_alloc::deallocate be called, size: %u\n", n);
    if (n == 1) {
        mem.free(p);
		printf("pool_alloc::deallocate end\n");
        return;
    }
	printf("pool_alloc::deallocate end\n");
}

