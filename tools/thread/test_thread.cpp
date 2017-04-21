// ************************************************************************
//
// compile:  g++ thread.cpp test_thread.cpp -lpthread -Wall -o test_thread
//
// ************************************************************************

#include <cstdio>
#include <cstring>
#include <unistd.h>
#include "thread.hpp"

class mythread_t : public util::thread_t
{
public:
    mythread_t(const char* name) {
        this->name = new char[32];
        strncpy(this->name, name, strlen(name) + 1);
    }

    ~mythread_t() {
        delete []name;
    }

    void run() {
        printf("this is %s thread.\n", name);
        sleep(1);
    }

private:
    char* name;
};

int main(int argc, char* argv[])
{
    mythread_t* t1 = new mythread_t("thread-1");
    mythread_t* t2 = new mythread_t("thread-2");
    mythread_t* t3 = new mythread_t("thread-3");

    t1->start();
    t2->start();
    t3->start();

    t1->stop();
    t2->stop();
    t3->stop();

    delete t1;
    delete t2;
    delete t3;

    printf("over\n");

    return 0;
}

