#include <iostream>
#include "../props.h"
using namespace std;

int main()
{
    Props* p = new Props();

    p->load("a.prop");

    cout << "------------------------------------------" << endl;
    p->list_props();

    p->set_prop((char*)"ding", (char*)"longlong");

    std::string key("long");
    std::string value("longlong");
    p->set_prop(&key, &value);

    cout << "------------------------------------------" << endl;
    p->list_props();
    cout << "get ding: " << *(p->get_prop((char*)"ding")) << endl;

    delete p;

    return 0;
}

