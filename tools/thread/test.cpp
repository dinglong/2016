#include <cstring>
#include <cstdio>
#include "work.hpp"
#include "thread_pool.hpp"

class mywork_t : public work_t
{
public:
    mywork_t(const char* name) {
        this->name = new char[32];
        strncpy(this->name, name, strlen(name) + 1);
    }

    ~mywork_t() {
        delete name;
    }

    int execute() {
        printf("work [%s] start\n", name);
        sleep(1);
        return 0;
    }

private:
    char* name;
};

int main(int argc, char* argv[])
{
    threadpool_t threadpool;

    mywork_t* w1 = new mywork_t("work-1");
    mywork_t* w2 = new mywork_t("work-2");
    mywork_t* w3 = new mywork_t("work-3");
    mywork_t* w4 = new mywork_t("work-4");
    mywork_t* w5 = new mywork_t("work-5");
    mywork_t* w6 = new mywork_t("work-6");

    threadpool.add_work(w1);
    threadpool.add_work(w2);
    threadpool.add_work(w3);
    threadpool.add_work(w4);
    threadpool.add_work(w5);
    threadpool.add_work(w6);

    while (true) {
        sleep(1);
        printf("main sleep...\n");
    }

    return 0;
}

