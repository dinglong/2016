#ifndef _DIR_TREE_HPP_
#define _DIR_TREE_HPP_

#include "logger.hpp"

struct item_tag;

/**
 * 链表项
 */
typedef struct link_tag {
    struct item_tag* item;
    struct link_tag* pre;
    struct link_tag* next;
} link_t;

/**
 * 链表实现
 */
class list_t
{
public:
    list_t();
    ~list_t();

    int insert(link_t* data);
    int remove(link_t* data);

    // 用于正向遍历链表
    link_t* begin();
    link_t* next(link_t* plist);

    link_t* find(const char* value);

private:
    link_t* head;
};

/**
 * tree中的项
 */
typedef struct locks_item_tag {
    bool lock;
} lock_item_t;

typedef struct item_tag {
    char* data;
    lock_item_t* lock_item;
    list_t* childs;
} item_t;

/**
 * dir tree实现
 */
class dir_tree_t
{
public:
    dir_tree_t();
    ~dir_tree_t();

    // 增加和删除tree中的项
    int insert(char* path, const char* value);
    int remove(char* path, const char* value);

    item_t* get_item(char* path);

    // 打印tree
    void dump();

    void format_path(char* buff, const char* path);

private:
    // tree禁止复制
    dir_tree_t(const dir_tree_t&);
    const dir_tree_t& operator=(const dir_tree_t&);

    // 提供递归打印工具
    void dump(item_t* root, int deep);

    // 从路径中的指定位置，获取下一个item值
    char* next_item(char*& path_pos);

    void destroy(item_t* root);
    item_t* find_item(char* path);

private:
    item_t* root; ///< tree根
    logger_t* logger;
};

#endif
