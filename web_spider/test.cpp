#include <iostream>
#include <cstdio>
#include "pages.h"
using namespace std;

int main(int argc, char* argv[])
{
    Pages pages;
    pages.init();

    Node* pnode = new Node(argv[1]);

    cout << pnode->get_addr() << endl;
    cout << pnode->get_page() << endl;

    pages.add_node(pnode);

    while (pages.has_node() < 200 && pages.has_new() > 0) {
        printf("nextpages \n");
        pages.next();
    }

    return 0;
}

