#ifndef _THREAD_POOL_HPP_
#define _THREAD_POOL_HPP_

#include "thread.hpp"
#include "safe_queue.hpp"
#include "work.hpp"

class threadpool_t;

/**
 * 一个worker即一个工作线程，处理自己队列中的消息
 */
class worker_t : public util::thread_t
{
public:
    worker_t(int index, threadpool_t* pool);
    ~worker_t();

    void done();
    void push_work(work_t* work);
    void run();

private:
	threadpool_t* pool;

    bool is_done;
    int index;
    safe_queue_t<work_t>* work_queue;
};

/**
 * 池中有多个工作的线程，即worker，向池中投入任务
 * 由池进行自动的均衡
 */
class threadpool_t
{
public:
    threadpool_t();
    ~threadpool_t();

    int add_work(work_t* work);

private:
    void init_thread();
    int get_index();

    threadpool_t(const threadpool_t&);
    const threadpool_t& operator = (const threadpool_t&);

    int worker_index;
    safe_queue_t<worker_t>* workers;

private:
    static const int MIN_POOL_SIZE = 5;  ///< 池中的最小线程数量
    static const int MAX_POOL_SIZE = 20; ///< 池中的最大线程数量
};

#endif

