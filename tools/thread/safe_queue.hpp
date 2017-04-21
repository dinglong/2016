#ifndef _SAFE_QUEUE_HPP_
#define _SAFE_QUEUE_HPP_

#include <pthread.h>
#include <sys/time.h>
#include <queue>

template <class T>
class safe_queue_t
{
public:
    safe_queue_t();
    ~safe_queue_t();

    int push_element(T* element);
    T* poll_element();
    T* dequeue_element(long timeout);
    T* access_element(long timeout);

private:
    void make_timeout(timespec* tsp, long seconds);

private:
    T* get_element(bool dequeue, long timeout);

    pthread_cond_t queue_ready;
    pthread_mutex_t queue_lock;

    std::queue<T*>* elements;

private:
    safe_queue_t(const safe_queue_t&);
    const safe_queue_t& operator = (const safe_queue_t&);
};

#include "safe_queue.cpp"

#endif

