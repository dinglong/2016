#include <assert.h>
#include <stdio.h>
#include "taskpool.h"

extern "C" {
    static void* thread_routine(void* arg)
    {
        Worker* worker = (Worker*)arg;
        assert(worker);

        // TODO 信号处理

        // 驱动实际工作函数
        worker->do_work(worker->m_arg);
        return NULL;
    }
}

void Worker::do_work(void* arg)
{
    while (!m_isdone) {
        if (m_task != NULL && m_task->can_exec()) {
            m_task->exec();
            m_task->finish();
            m_task = NULL;
        }

        pthread_mutex_lock(&m_waitlock);
        if (!m_isdone) {
            m_isidle = true;
            struct timespec tsp;

            maketimeout(&tsp, 10); // 十秒的超时
            pthread_cond_timedwait(&m_cond, &m_waitlock, &tsp);
        }
        pthread_mutex_unlock(&m_waitlock);

        m_isidle = false;
    }
}

void Worker::start()
{
    pthread_t tid;
    pthread_create(&tid, NULL, thread_routine, this);
    printf("create thread %lu\n", tid);
}

void Worker::stop()
{
    pthread_mutex_lock(&m_waitlock);
    m_isdone = true;
    pthread_mutex_unlock(&m_waitlock);
    pthread_cond_signal(&m_cond);
}


void Worker::maketimeout(struct timespec* tsp, long timeout)
{
    struct timeval now;
    gettimeofday(&now, NULL);
    tsp->tv_sec = now.tv_sec;
    tsp->tv_nsec = now.tv_usec * 1000;

    // 加上偏移时间
    tsp->tv_sec += timeout; // 单位是秒
}

