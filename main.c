#include "memory.h"
#include "Tests/test.h"

int main(int argc, char **argv)
{
//	MAKE_TEST(test1)
//	MAKE_TEST(test2)
//	MAKE_TEST(test3)
//	MAKE_TEST(test4)
//	MAKE_TEST(test5)
//	MAKE_TEST(test6)
//	MAKE_TEST(test7)
//	MAKE_TEST(test8)
	void* ptrs[100];

	ptrs[0] = malloc(1024);
	ptrs[1] = malloc(1024);
	ptrs[2] = malloc(1024);
	ptrs[3] = malloc(1024);

	ptrs[4] = malloc(1024);
	ptrs[5] = malloc(1024);
	ptrs[6] = malloc(1024);
	ptrs[7] = malloc(782);

	show_alloc_mem();
//	free(ptrs[2]);
//	free(ptrs[3]);
//	free(ptrs[1]);
	return (0);
}
