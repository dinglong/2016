#include "thread_pool.hpp"

/// -----------------------------------------------------
/// class worker
/// -----------------------------------------------------
worker_t::worker_t(int index, threadpool_t* pool)
{
	this->pool = pool;
    is_done = false;
    this->index = index;
    work_queue = new safe_queue_t<work_t>();
}

worker_t::~worker_t()
{
    delete work_queue;
}

void worker_t::done()
{
    is_done = true;
}

void worker_t::push_work(work_t* work)
{
    work_queue->push_element(work);
}

void worker_t::run()
{
    while (!is_done) {
        printf("worker %d working...\n", index);

        work_t* work = work_queue->poll_element();
        work->execute();

        delete work;
    }
}

/// -----------------------------------------------------
/// class threadpool
/// -----------------------------------------------------
threadpool_t::threadpool_t()
{
    worker_index = 0;
    workers = new safe_queue_t<worker_t>();
    init_thread();
}

threadpool_t::~threadpool_t()
{
    worker_t* worker = NULL;
    while ((worker = workers->dequeue_element(0)) != NULL) {
        worker->done();
        delete worker;
    }
    delete workers;
}

int threadpool_t::add_work(work_t* work)
{
    worker_t* worker = workers->poll_element();
    worker->push_work(work);

    // 增减了工作，置于队尾
    workers->push_element(worker);

    return 0;
}

void threadpool_t::init_thread()
{
    for (int i = 0; i < MIN_POOL_SIZE; i++) {
        worker_t* worker = new worker_t(get_index(), this);
        worker->start();
        workers->push_element(worker);

        printf("init add worker %d\n", i);
    }
}

int threadpool_t::get_index()
{
    return worker_index++;
}

