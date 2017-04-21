#include <cassert>

template <class T>
safe_queue_t<T>::safe_queue_t()
{
    pthread_mutex_init(&queue_lock, NULL);
    pthread_cond_init(&queue_ready, NULL);
    elements = new std::queue<T*>();
}

template <class T>
safe_queue_t<T>::~safe_queue_t()
{
    pthread_mutex_destroy(&queue_lock);
    pthread_cond_destroy(&queue_ready);
    delete elements;
}

template <class T>
int safe_queue_t<T>::push_element(T* element)
{
    assert(element != NULL);

    // 对队列加锁
    pthread_mutex_lock(&queue_lock);
    elements->push(element);
    pthread_mutex_unlock(&queue_lock);

    // 唤醒一个阻塞的线程
    pthread_cond_signal(&queue_ready);

    // TODO 考虑队列的最大限制

    return 0;
}

template <class T>
T* safe_queue_t<T>::poll_element()
{
    // 获取并从队列中摘除
    T* element = get_element(true, -1);

    assert(element != NULL);

    return element;
}

template <class T>
T* safe_queue_t<T>::dequeue_element(long timeout)
{
    // 访问，且出队
    T* element = get_element(true, timeout);
    return element;
}

template <class T>
T* safe_queue_t<T>::access_element(long timeout)
{
    // 只访问，而不出队
    T* element = get_element(false, timeout);
    return element;
}

template <class T>
T* safe_queue_t<T>::get_element(bool dequeue, long timeout)
{
    pthread_mutex_lock(&queue_lock);

    T* element = NULL;

    // 条件不满足，等待
    if (elements->size() == 0) {
        if (timeout < 0) {
            pthread_cond_wait(&queue_ready, &queue_lock);
        } else {
            timespec waittime;
            make_timeout(&waittime, timeout);
            pthread_cond_timedwait(&queue_ready, &queue_lock, &waittime);
        }
    }


    if (elements->size() > 0) {
        element = elements->front();

        // 需要出队
        if (dequeue) {
            elements->pop();
        }
    }

    pthread_mutex_unlock(&queue_lock);

    return element;
}

template <class T>
void safe_queue_t<T>::make_timeout(timespec* tsp, long seconds)
{
	// TODO printf("timeout %ld\n", seconds);

    timeval now;

    // 获取并填入当前的时间
    gettimeofday(&now, NULL);
    tsp->tv_sec = now.tv_sec;
    tsp->tv_nsec = now.tv_usec * 1000;

	// TODO printf("now: %s\n", ctime(&now.tv_sec));

    // 加上偏移值
    tsp->tv_sec += seconds;
}

