// *********************************************************************
//
// compile:  g++ test_safe_queue.cpp -Wall -lpthread -o test_safe_queue
//
// *********************************************************************

#include <cstdio>
#include <cstring>
#include "safe_queue.hpp"
#include "work.hpp"

class work_impl_t : public work_t
{
public:
    work_impl_t(const char* name) {
        this->name = new char[32];
        strncpy(this->name, name, strlen(name) + 1);
    }

    ~work_impl_t() {
        delete name;
    }

    int execute() {
        printf("this is %s work execute...\n", name);
        sleep(1);
        return 0;
    }

private:
    char* name;
};

int main(int argc, char* argv[])
{
    safe_queue_t<work_t> wq;

    work_impl_t* work = new work_impl_t("work-1");

    wq.push_element(work);
    work_t* w = wq.poll_element();

    w->execute();

    delete work;

	// 超时等待2s
	work_t*	tmp_w = wq.dequeue_element(10);
	if(tmp_w != NULL) {
		printf("error been discovered.\n");
	}

    return 0;
}
