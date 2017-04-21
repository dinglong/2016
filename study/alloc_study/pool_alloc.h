#include "pool.h"

template<class T> class Pool_alloc
{
public:
    typedef T value_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    typedef T* pointer;
    typedef const T* const_pointer;

    typedef T& reference;
    typedef const T& const_reference;

    pointer address(reference r) const {
        return &r;
    }
    const_pointer address(const_reference r) const {
        return &r;
    }

    Pool_alloc() throw();
    template<class U> Pool_alloc(const Pool_alloc<U>&) throw();
    ~Pool_alloc() throw();

    pointer allocate(size_type n, const_pointer hint = 0);
    void deallocate(pointer p, size_type n);

    void construct(pointer p, const T& val)
    {
		printf("pool_alloc::construct be called\n");
        new(p) T(val);
		printf("pool_alloc::construct end\n");
    }

    void destroy(pointer p) {
		printf("pool_alloc::destroy be called\n");
        p->~T();
		printf("pool_alloc::destroy end\n");
    }

    size_type max_size() const throw();

    template<class U>
    struct rebind {
        typedef Pool_alloc<U> other;
    };

private:
    static Pool mem;
};

#include "pool_alloc.cpp"

