#include "prase_doc.h"

int main()
{
    PraseDoc* pd = new PraseDoc((char*)"test.html");
    pd->prase();

    pd->dump_doc();

    return 0;
}

