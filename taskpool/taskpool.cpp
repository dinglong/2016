#include <assert.h>
#include "taskpool.h"

extern "C"
{
    static void* thread_routine_dispatch(void* arg)
    {
        TaskPool* taskpool = (TaskPool*)arg;
        assert(taskpool);
        taskpool->dispatch(taskpool->m_arg);
        return NULL;
    }

    static void* thread_routine_reap(void* arg)
    {
        TaskPool* taskpool = (TaskPool*)arg;
        assert(taskpool);
        taskpool->reap(taskpool->m_arg);
        return NULL;
    }
}

void TaskPool::dispatch(void* arg)
{
    // TODO 启动dispatch功能
}

void TaskPool::reap(void* arg)
{
    // TODO 启动空闲回收功能
}

void TaskPool::start()
{
    pthread_t tid;
    pthread_create(&tid, NULL, thread_routine_dispatch, this);
    pthread_create(&tid, NULL, thread_routine_reap, this);
}

void TaskPool::add_task(Task* task)
{
    pthread_mutex_lock(&m_lock_tasks);
    m_tasks.push_back(task);
    pthread_mutex_unlock(&m_lock_tasks);
}

void TaskPool::del_task(Task* task)
{
    // TODO
}

void TaskPool::add_worker()
{
    // TODO 考虑最大线程数
    Worker* worker = new Worker();
    worker->start();

    m_workers.push_back(worker);
}

void TaskPool::sub_worker()
{
    // TODO 尝试删除一个处于idle状态的worker
    // TODO 考虑最小线程数
}

