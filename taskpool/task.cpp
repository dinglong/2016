#include "taskpool.h"

Task::Task(std::list<Task*>* tasks)
{
    m_finish = false;
    m_cancle = false;
    m_depends = tasks;
}

bool Task::can_exec()
{
    bool can_exec = true;

    // 所有依赖的任务都完成或者取消，那么自己可以执行
    if (m_depends != NULL) {
        std::list<Task*>::iterator iter = m_depends->begin();
        for (; can_exec && iter != m_depends->end(); iter++) {
            can_exec = ((*iter)->m_finish || (*iter)->m_cancle);
        }
    }

    return can_exec;
}

