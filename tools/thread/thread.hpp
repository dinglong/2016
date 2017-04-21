#ifndef _THREAD_HPP_
#define _THREAD_HPP_

#include <pthread.h>

namespace util
{
    class thread_t
    {
    public:
        inline thread_t() {};
        virtual ~thread_t() {};

        void start();
        void stop();

        virtual void run() = 0;

    private:
        pthread_t tid;

        void error_assert(int rc, const char* msg);

        thread_t(const thread_t&);
        const thread_t& operator = (const thread_t&);
    };
}

#endif

