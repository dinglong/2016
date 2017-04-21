#ifndef _TASK_POOL_H_
#define _TASK_POOL_H_

#include <list>
#include <pthread.h>
#include <sys/time.h>

class Task
{
public:
    Task() : m_finish(false), m_cancle(false), m_depends(NULL) {}

    Task(std::list<Task*>* tasks);

    /**
     * 执行任务
     */
    virtual void exec() = 0;

    /**
     * 任务当前是否可以投入执行
     */
    bool can_exec();

    /**
     * 完成任务
     */
    void finish() {
        m_finish = true;
    }

    /**
     * 取消任务
     */
    void cancle() {
        m_cancle = true;
    }

protected:
    bool m_finish; ///< 任务是否结束
    bool m_cancle; ///< 任务是否取消
    std::list<Task*>* m_depends; ///< 依赖的任务
};

class Worker
{
public:
    Worker() : m_isdone(false), m_isidle(false), m_task(NULL) {
        m_cond = PTHREAD_COND_INITIALIZER;
        m_waitlock = PTHREAD_MUTEX_INITIALIZER;
    }

    /**
     * 线程执行函数
     */
    void do_work(void* arg);

    /**
     * 启动执行
     */
    void start();

    /**
     * 结束执行
     */
    void stop();

    /**
     * 是否处于空闲状态
     */
    int is_idle() {
        return m_isidle;
    }

    /**
     * 关联任务
     */
    void attach(Task* task) {
        m_task = task;
    }

    /**
     * 取消任务的关联
     */
    Task* deatch() {
        // TODO
        return NULL;
    }

private:
    void maketimeout(struct timespec* tsp, long timeout);

public:
    void* m_arg;

private:
    pthread_cond_t m_cond;
    pthread_mutex_t m_waitlock;

    bool m_isdone; ///< worker结束
    bool m_isidle; ///< worker空闲
    Task* m_task; ///< worker要执行的任务
};

class TaskPool
{
public:
    TaskPool() {
        m_lock_tasks = PTHREAD_MUTEX_INITIALIZER;
        m_lock_workers = PTHREAD_MUTEX_INITIALIZER;
    }

    /**
     * 调度任务
     */
    void dispatch(void* arg);

    /**
     * 回收idle线程
     */
    void reap(void* arg);

    /**
     * 启动任务池
     */
    void start();

    /**
     * 停止任务池
     */
    void stop();

    void add_task(Task* task);
    void del_task(Task* task);

    void add_worker();
    void sub_worker();

public:
    void* m_arg;

private:
    pthread_mutex_t m_lock_tasks;
    pthread_mutex_t m_lock_workers;

    std::list<Task*> m_tasks; // 任务队列
    std::list<Worker*> m_workers; // 任务处理者队列
};

#endif

