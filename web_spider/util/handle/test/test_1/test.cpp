#include <cstdio>
#include "../../handle.h"

class A
{
public:
    A(int a) {
        m_a = a;
        printf("A construct be called. m_a[%d]\n", m_a);
    }

    A(const A& a_ref) {
        m_a = a_ref.m_a;
        printf("A copy construct be called. m_a[%d]\n", m_a);
    }

    void f() {
        printf("this is [%d]\n", m_a);
    }

    ~A() {
        printf("A destruct be called. m_a[%d]\n", m_a);
    }

private:
    int m_a;
};

int main()
{
    Handle<A> ha(new A(1));
    Handle<A> hb(new A(2));
    Handle<A> hc(ha);
    ha = hb;

    ha->f();
    hb->f();
    hc->f();

    ha.dump();
    hb.dump();
    hc.dump();

    return 0;
}

