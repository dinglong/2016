#ifndef _HANDLE_H_
#define _HANDLE_H_

#include <cstdio>

/**
 * 实现handle类，进行引用技术管理
 */
template<class X>
class Handle
{
public:
    Handle(X* px) : m_rep(px), m_pcount(new int(1)) {}
    Handle(const Handle& ref) : m_rep(ref.m_rep), m_pcount(ref.m_pcount) {
        (*m_pcount)++;
    }

    X* operator->() {
        return m_rep;
    }

    Handle& operator=(const Handle& ref) {
        if (m_rep != ref.m_rep) {
            if (--(*m_pcount) == 0) {
                delete m_rep;
                delete m_pcount;
            }
            m_rep = ref.m_rep;
            m_pcount = ref.m_pcount;
            (*m_pcount)++;
        }
        return *this;
    }

    ~Handle() {
        if (--(*m_pcount) == 0) {
            delete m_rep;
            delete m_pcount;
        }
    }

    void dump() {
        if (m_rep != NULL) {
            printf("value address [%p]\n", m_rep);
            printf("value count [%d]\n", *m_pcount);
        }
    }

private:
    X* m_rep;
    int* m_pcount;
};

#endif

