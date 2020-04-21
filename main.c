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

	testHexPrint();
	void* ptrs[100];

	ptrs[0] = malloc(24);
	memset(ptrs[0], 'a', 24);

	ptrs[1] = malloc(128);
	memset(ptrs[1], 'A', 128);
	show_mem_hex();
	show_alloc_mem();
//	free(ptrs[2]);
//	free(ptrs[3]);
//	free(ptrs[1]);
	return (0);
}
