#include <iostream>
using namespace std;

class A
{
public:
    A() {
        cerr << "A() been called" << endl;
    }

    virtual ~A() {
        cerr << "~A() been called" << endl;
    }

    virtual A* copy() const = 0;
};

class B : public A
{
public:
    B() {
        cerr << "B() been called" << endl;
    }

    ~B() {
        cerr << "~B() been called" << endl;
    }

    B(const B& b) {
        cerr << "B(const B& b) been called" << endl;
    }

    A* copy() const {
        cerr << "B::copy() been called" << endl;
        return new B(*this);
    }
};

class ProxyA
{
public:
    ProxyA() {
        cerr << "ProxyA() been called" << endl;
        pa = 0;
    }

    ~ProxyA() {
        cerr << "~ProxyA() been called" << endl;
		delete pa;
    }

    ProxyA(const A& a) {
        cerr << "ProxyA(const A& a) been called" << endl;
        pa = a.copy();
    }

    ProxyA(const ProxyA& p) {
        cerr << "ProxyA(const ProxyA& p) been called" << endl;
        pa = (p.pa ? p.pa->copy() : 0);
    }

    ProxyA& operator=(const ProxyA& p) {
        cerr << "ProxyA::operator = been called" << endl;
        if (this != &p) {
            delete pa;
            pa = (p.pa ? p.pa->copy() : 0);
        }
        return *this;
    }

private:
    A* pa;
};

int main(int argc, char* argv[])
{
    cerr << "----------- 0 ------------" << endl;
    ProxyA ps[2];

    cerr << "----------- 1 ------------" << endl;
    B b;

    cerr << "----------- 2 ------------" << endl;
    ps[0] = b;

    cerr << "----------- 3 ------------" << endl;
    return 0;
}

