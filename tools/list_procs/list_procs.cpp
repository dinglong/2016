#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <dirent.h>
#include <cstring>
#include <unistd.h>

struct ProcStruct;

/**
 * 一个进程的孩子
 */
typedef struct ChildStruct {
    struct ProcStruct* child;
    struct ChildStruct* next;
} Childs;

/**
 * 标识一个process的信息
 */
typedef struct ProcStruct {
    static const int COMM_LEN = 1024;

    /*
     * 对应的命令及参数
     */
    char cmd[COMM_LEN + 1];
    char* args[];

    /*
     * 自己的进程id及父进程id
     */
    pid_t pid;
    pid_t ppid;

    /*
     * 父子关系表
     */
    Childs* childs;
    struct ProcStruct* parent;

    /*
     * 遍历结构表
     */
    struct ProcStruct* next;
} Proc;

/**
 * list系统中的进行信息，构建数据结构
 */
class ProcList
{
public:
    ProcList();
    void read_proc();
    void list_proc(int width);
    Proc* find_proc(pid_t pid);

private:
    Proc* new_proc(char* cmd, pid_t pid, pid_t ppid);
    void add_proc(char* cmd, pid_t pid, pid_t ppid);
    void add_child(Proc* parent, Proc* child);

private:
    Proc* m_base;

    static const int BUFF_SIZE = 1024;
    static const char* PROC_BASE_DIR;
};

const char* ProcList::PROC_BASE_DIR = "/proc";

ProcList::ProcList()
{
    m_base = NULL;
}

/**
 * 从文件系统 proc 中读出系统中的进程信息
 */
void ProcList::read_proc()
{
    char read_buff[BUFF_SIZE + 1];
    DIR* proc_dir = opendir(PROC_BASE_DIR);
    if (proc_dir == NULL) {
        perror("open proc dir error");
        return;
    }

    pid_t pid;
    struct dirent* de = NULL;
    while ((de = readdir(proc_dir)) != NULL) {
        if ((pid = (pid_t)atoi(de->d_name)) != 0) {
            // 在次目录解析出需要的参数
            char* path = new char[strlen(PROC_BASE_DIR) + strlen(de->d_name) + 16];
            sprintf(path, "%s/%s/stat", PROC_BASE_DIR, de->d_name);

            FILE* file = fopen(path, "r");
            if (file == NULL) {
                perror("open stat file error");
                exit(1);
            }

            size_t size = fread(read_buff, 1, BUFF_SIZE, file);
            if (ferror(file) == 0) {
                read_buff[size] = 0;

                char* cmd = NULL;
                char* end_cmd = NULL;
                if ((cmd = strchr(read_buff, (int)'(')) && (end_cmd = strrchr(cmd, (int)')'))) {
                    *end_cmd = 0;
                    cmd++;

                    pid_t ppid = 0;
                    if (sscanf(end_cmd + 2, "%*c %d", &ppid) == 1) {
                        // TODO 考虑是否显示线程(位于 task 中)
                        add_proc(cmd, pid, ppid);
                    }
                }
            }
            delete []path;
        }
    }
}

void ProcList::list_proc(int width)
{
    // self - [parent]parent
    //        [childs]child-child-...
    Proc* ptr = m_base;
    while (NULL != ptr) {
        printf("*****[%d-%s]******************************\n", ptr->pid, ptr->cmd);
        printf("     [parent]-%d\n", (ptr->parent != NULL ? ptr->parent->pid : 0));

        // 打印孩子
        printf("     [childs]");
        Childs* pcs = ptr->childs;

        int cnt = 0;
        while (pcs != NULL) {
            printf("-%d", pcs->child->pid);
            pcs = pcs->next;

            cnt++;
            if (cnt == width) {
                printf("\n     [childs]");
                cnt = 0;
            }
        }
        printf("\n");

        // 处理下一个
        ptr = ptr->next;
    }
}

/**
 * 分配一个进程标识结构
 */
Proc* ProcList::new_proc(char* cmd, pid_t pid, pid_t ppid)
{
    // TODO 内存分配失败处理
    Proc* p = new Proc();
    strcpy(p->cmd, cmd);
    p->pid = pid;
    p->ppid = ppid;

    p->next = m_base;
    m_base = p;

    return m_base;
}

Proc* ProcList::find_proc(pid_t pid)
{
    if (m_base == NULL) {
        return NULL;
    } else {
        Proc* proc = m_base;
        while (proc->pid != pid) {
            proc = proc->next;
            if (proc == NULL) {
                break;
            }
        }
        return proc;
    }
}

void ProcList::add_proc(char* cmd, pid_t pid, pid_t ppid)
{
    Proc* proc = find_proc(pid);
    if (proc == NULL) {
        proc = new_proc(cmd, pid, ppid);
    } else {

        strcpy(proc->cmd, cmd);
        proc->pid = pid;
        proc->ppid = ppid;
    }
    if (pid == ppid) {
        ppid = 0;
    }

    Proc* parent = find_proc(ppid);
    if (parent == NULL) {
        parent = new_proc((char*)"x", ppid, 0);
    }

    add_child(parent, proc);
    proc->parent = parent;

    printf("add proc cmd[%s]-pid[%d]-ppid[%d]\n", cmd, pid, ppid);
}

void ProcList::add_child(Proc* parent, Proc* child)
{
    Childs* childs = new Childs();
    childs->child = child;

    if (parent->childs == NULL) {
        childs->next = NULL;
        parent->childs = childs;
    } else {
        childs->next = parent->childs->next;
        parent->childs->next = childs;
    }
}

int main(int argc, char* argv[])
{
    ProcList proclist;
    proclist.read_proc();

    proclist.list_proc(16);

    return 0;
}

