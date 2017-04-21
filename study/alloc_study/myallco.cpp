#include <cstdio>
#include <vector>
#include "pool.h"
#include "pool_alloc.h"
using namespace std;

int main(int argc, char* argv[])
{
	printf("------- 1 --------\n");

	vector<int, Pool_alloc<int> > v;
	printf("------- 2 --------\n");

	v.push_back(1);

	printf("------- over ------\n");
	return 0;
}

