#include <cstdio>
#include <cstdlib>
#include "thread.hpp"

extern "C"
{
    static void* thread_routine(void* args)
    {
        util::thread_t* self = (util::thread_t*)args;
        self->run();
        return NULL;
    }
}

void util::thread_t::start()
{
    int rc = pthread_create(&tid, NULL, thread_routine, this);
    error_assert(rc, "create thread error");
}

void util::thread_t::stop()
{
    int rc = pthread_join(tid, NULL);
    error_assert(rc, "join thread error");
}

void util::thread_t::error_assert(int rc, const char* msg)
{
    if (rc != 0) {
        perror(msg);
        abort();
    }
}

