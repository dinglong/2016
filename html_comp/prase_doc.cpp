#include <cstdlib>
#include <assert.h>
#include <cstdio>
#include <cstring>
#include "prase_doc.h"

// -------------------------------------------------------------------
// class PraseStack
// -------------------------------------------------------------------

PraseStack::PraseStack()
{
    m_top = NULL;
}

PraseStack::~PraseStack()
{
    while (m_top != NULL) {
        stacknode_t* snode = m_top;
        m_top = m_top->next;
        delete snode;
    }
}

node_t* PraseStack::pop()
{
    node_t* ret = NULL;

    if (m_top != NULL) {
        ret = m_top->value;

        stacknode_t* snode = m_top;
        m_top = m_top->next;

        delete snode;
    }

    return ret;
}

node_t* PraseStack::get_top()
{
    node_t* ret = NULL;

    if (m_top != NULL) {
        ret = m_top->value;
    }

    return ret;
}

void PraseStack::push(node_t* node)
{
    stacknode_t* snode = new stacknode_t();

    snode->value = node;
    snode->next = m_top;
    m_top = snode;
}

bool PraseStack::is_empty()
{
    return (m_top == NULL);
}

// -------------------------------------------------------------------
// class PraseDoc
// -------------------------------------------------------------------

PraseDoc::PraseDoc(char* filename)
{
    m_pnodes = NULL;

    m_filename = new char[strlen(filename) + 1];
    strcpy(m_filename, filename);
}

PraseDoc::~PraseDoc()
{
    if (m_filename != NULL) {
        delete []m_filename;
    }
}

void PraseDoc::prase()
{
    PraseStack praseStack;
    FILE* fd = fopen(m_filename, "r");

    if (fd == NULL) {
        printf("open file[%s] error.", m_filename);
        return;
    }

    int ch = '\0';
    while (ch != EOF && (ch = fgetc(fd)) != EOF) {

        // 跳过空白和换行
        do {
            if (ch != ' ' && ch != '\t' && ch != '\n' && ch != '\r') {
                break;
            }
        } while ((ch = fgetc(fd)) != EOF);

        if (ch == EOF) {
            break;
        }

        if (ch == '<') {
            if ((ch = fgetc(fd)) == EOF) {
                break;
            }

            if (ch == '!') {
                // 跳过注释
                while ((ch = fgetc(fd)) != EOF) {
                    if (ch == '>') {
                        break;
                    }
                }
            } else if (ch == '/') {
                prase_endnode(fd, praseStack, ch);
            } else {
                prase_startnode(fd, praseStack, ch);
            }
        } else {
            prase_nodevalue(fd, praseStack, ch);
        }
    }
}

void PraseDoc::prase_startnode(FILE* fd, PraseStack& praseStack, int& ch)
{
    // nodename
    char* pname = new char[MAX_BUFF];

    int index = 0;
    int buff_len = MAX_BUFF;
    do {
        pname[index++] = (char)ch;

        // realloc buff
        if (index >= buff_len) {
            char* oldbuff = pname;
            pname = new char[2 * buff_len];
            memcpy(pname, oldbuff, buff_len);
            buff_len *= 2;

            delete []oldbuff;
        }

        ch = fgetc(fd);
        if (ch == EOF) {
            return;
        }
    } while (ch != '/' && ch != '>');

    pname[index] = '\0';

    // 栈定元素即为接下来的node的父node
    node_t* parent = praseStack.get_top();

    if (ch == '>') {
        // 记录该node
        node_t* node = new node_t();
        node->name = pname;

        if (parent != NULL) {
            // 尾插法，逆序排列
            node->next = parent->child;
            parent->child = node;
        }

        if (m_pnodes == NULL) {
            m_pnodes = node;
        }

        praseStack.push(node);
    } else if (ch == '/') {
        // 如果是结束node的结束标签，对比分析栈定，如果
        // 找到相同的node，则正确退栈，结束该node的分析
        // 否则，认为该node是一个单边的node
        ch = fgetc(fd);
        if (ch == EOF) {
            return;
        }

        if (ch == '>') {
            if (parent != NULL) {
                if (strcmp(parent->name, pname) == 0) {
                    praseStack.pop();
                }
                delete []pname;
            }
        } else {
            // TODO 文本有错误
        }
    }
}

void PraseDoc::prase_endnode(FILE* fd, PraseStack& praseStack, int& ch)
{
    // nodevalue
    char* pname = new char[MAX_BUFF];

    int index = 0;
    int buff_len = MAX_BUFF;

    while (ch != '>') {
        pname[index++] = (char)ch;

        // realloc buff
        if (index >= buff_len) {
            char* oldbuff = pname;
            pname = new char[2 * buff_len];
            memcpy(pname, oldbuff, buff_len);
            buff_len *= 2;

            delete []oldbuff;
        }

        ch = fgetc(fd);
        if (ch == EOF) {
            return;
        }
    }

    pname[index] = '\0';

    // 栈定元素即为接下来的node的父node
    node_t* parent = praseStack.get_top();

    if (parent != NULL) {
        if (strcmp(parent->name, pname) == 0) {
            praseStack.pop();
        }
        delete []pname;
    }
}

void PraseDoc::prase_nodevalue(FILE* fd, PraseStack& praseStack, int& ch)
{
    if (praseStack.is_empty()) {
        printf("error html doc.\n");
        exit(1);
    }

    char* pvalue = new char[MAX_BUFF];

    int index = 0;
    int buff_len = MAX_BUFF;

    while (ch != '<') {
        pvalue[index++] = (char)ch;

        // realloc buff
        if (index >= buff_len) {
            char* oldbuff = pvalue;
            pvalue = new char[2 * buff_len];
            memcpy(pvalue, oldbuff, buff_len);
            buff_len *= 2;

            delete []oldbuff;
        }

        ch = fgetc(fd);
        if (ch == EOF) {
            return;
        }
    }

    // put back
    ungetc(ch, fd);

    pvalue[index] = '\0';

    prop_t* prop = new prop_t();
    prop->value = pvalue;

    // TODO
    // 此处应该是链表
    node_t* parent = praseStack.get_top();
    parent->props = prop;
}

void PraseDoc::compare(PraseDoc* pdoc)
{

}

void PraseDoc::dump_doc()
{
    print_node(m_pnodes, 0);
}

void PraseDoc::print_node(node_t* node, int prefix)
{
    node_t* pns = node;
    while (pns != NULL) {
        printf("%d node name [%s]\n", prefix, pns->name);
        if (pns->props != NULL) {
            printf("%d node value[%s]\n", prefix, pns->props->value);
        }

        node_t* child = pns->child;
        while (child != NULL) {
            print_node(child, prefix++);
            child = child->next;
        }

        pns = pns->next;
    }
}

