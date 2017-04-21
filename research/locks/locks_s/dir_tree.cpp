#include <cstring>
#include <cstdio>
#include "dir_tree.hpp"

// -----------------------------------------------------------------
// class list_t
// -----------------------------------------------------------------
list_t::list_t()
{
    // 初始化队列的头结点
    head = new link_t();
    head->item = new item_t();
    head->item->data = new char[2];
    head->item->data[0] = '.';
    head->item->data[1] = '\0';
    head->pre = head;
    head->next = head;
}

list_t::~list_t()
{
    // 只销毁头，其他的需要使用remove的方式删除
    delete head->item->data;
    delete head->item;
    delete head;
}

int list_t::insert(link_t* data)
{
    // 头插法
    data->pre = head->next->pre;
    data->next = head->next;
    head->next->pre = data;
    head->next = data;

    return 0;
}

int list_t::remove(link_t* data)
{
    if (data == NULL || data == head) {
        return -1;
    }

    // 从链表中摘除
    data->pre->next = data->next;
    data->next->pre = data->pre;

    // data内存的释放留给用户

    return 0;
}

link_t* list_t::begin()
{
    return head;
}

link_t* list_t::next(link_t* plist)
{
    // 已经是队尾节点
    if (plist->next == head) {
        return NULL;
    }
    return plist->next;
}

link_t* list_t::find(const char* value)
{
    link_t* p = head;
    while ((p = next(p)) != NULL) {
        if (strcmp(value, p->item->data) == 0) {
            return p;
        }
    }
    return NULL;
}

// -----------------------------------------------------------------
// class dir_tree_t
// -----------------------------------------------------------------
dir_tree_t::dir_tree_t()
{
	logger = logger_t::get_logger();
    
	// tree存在一个头结点
    root = new item_t();
    root->data = new char[2];
    root->data[0] = '#';
    root->data[1] = '\0';
    root->childs = new list_t();

    // 初始的结点为 /ls
    link_t* data = new link_t();
    data->item = new item_t();
    data->item->data = new char[4];
    data->item->data[0] = '/';
    data->item->data[1] = 'l';
    data->item->data[2] = 's';
    data->item->data[3] = '\0';
    data->item->childs = NULL;

    // 将节点置于tree根的孩子中
    root->childs->insert(data);
}

dir_tree_t::~dir_tree_t()
{
    destroy(root);
}

int dir_tree_t::insert(char* path, const char* value)
{
    // 按路径查找位置
    item_t* pitem = find_item(path);
    if (pitem == NULL) {
        return -1;
    }

    // 构造新的节点
    link_t* child = new link_t();
    child->item = new item_t();
    child->item->data = new char[strlen(value) + 1];
    memcpy(child->item->data, value, strlen(value) + 1);
    child->item->childs = NULL;

    // 将新节点放入
    if (pitem->childs == NULL) {
        pitem->childs = new list_t();
    }
    pitem->childs->insert(child);

    return 0;
}

int dir_tree_t::remove(char* path, const char* value)
{
    item_t* item = find_item(path);
    if (item == NULL) {
        return -1;
    }

    link_t* data = item->childs->find(value);
    if (data == NULL) {
        return -1;
    }

    item->childs->remove(data);
    return 0;
}

item_t* dir_tree_t::get_item(char* path)
{
    // TODO 合并find_item
    return find_item(path);
}

void dir_tree_t::format_path(char* buff, const char* path)
{
    logger->debug("before format path [%s].\n", path);

    char* tmp = buff;
    bool hasFindSlash = false;

    while (*path != '\0') {
        if (*path != '/' || !hasFindSlash) {
            *(tmp++) = *path;
        }
        hasFindSlash = (*path == '/');
        path++;
    }

    // TODO 相对路径的支持

    // 如果结尾是分隔符，去掉
    if (*(tmp - 1) == '/') {
        *(tmp - 1) = '\0';
    } else {
        *tmp = '\0';
    }

    logger->debug("after format path [%s].\n", buff);
}

void dir_tree_t::dump()
{
    dump(root, 0);
}

void dir_tree_t::dump(item_t* root, int deep)
{
    // traverse childs
    if (root->childs != NULL) {
        link_t* pchild = root->childs->begin();
        while ((pchild = root->childs->next(pchild)) != NULL) {
            dump(pchild->item, deep + 1);
        }
    }

    // print self
    for (int i = 1; i < deep; i++) {
        printf("    ");
    }
    printf("%s\n", root->data);
}

void dir_tree_t::destroy(item_t* root)
{
    // traverse childs
    if (root->childs != NULL) {
        link_t* pchild = root->childs->begin();
        while ((pchild = root->childs->next(pchild)) != NULL) {
            destroy(pchild->item);
        }
        // TODO destroy list childs
    }

    logger->debug("free item [%s]\n", root->data);

    // destroy self
    delete [](root->data);
    delete root->childs;
    delete root;
    root = NULL;
}

item_t* dir_tree_t::find_item(char* path)
{
    char* data = NULL;
    char* pos = path;
    bool findpos = true;
    item_t* pitem = root;

    // 根据路径在树中找到位置
    while ((data = next_item(pos)) != NULL) {
        if (pitem->childs != NULL) {
            link_t* child = pitem->childs->find(data);
            if (child != NULL) {
                pitem = child->item;
            } else {
                findpos = false;
            }
        }
        delete []data; // TOOD 反复分配内存，优化
    }

    if (!findpos) {
        return NULL;
    }
    return pitem;
}

char* dir_tree_t::next_item(char*& path_pos)
{
    char* start = path_pos;

    if (*path_pos == '\0') {
        return NULL;
    }

    // must start with slash, skip
    path_pos++;

    // find next slash
    while (*path_pos != '\0' && *path_pos != '/') {
        path_pos++;
    }

    int len = path_pos - start;
    char* value = new char[len + 1];
    memcpy(value, start, len);
    *(value + len) = '\0';

    return value;
}

int mainx(int argc, char* argv[])
{
    dir_tree_t dtt;
    dtt.insert((char*)"/ls", (char*)"/x");
    dtt.insert((char*)"/ls/x", (char*)"/y");
    dtt.insert((char*)"/ls", (char*)"/a");
    dtt.insert((char*)"/ls/a", (char*)"/b");
    dtt.insert((char*)"/ls/a", (char*)"/c");
    dtt.dump();

    char* path = "///a/b//c///";
    char* buff = new char[strlen(path) + 1];
    dtt.format_path(buff, path);

    return 0;
}
