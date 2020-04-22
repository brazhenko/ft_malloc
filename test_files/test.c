#include <sys/mman.h>
#include <unistd.h>
#include <sys/resource.h>

int main()
{
	char* cluster;

//	cluster = 
//			mmap(0,
//			1024,
//			PROT_READ | PROT_WRITE,
//			MAP_ANON | MAP_PRIVATE,
//			-1,
//			0);
//	cluster[0] = 42;
	struct rusage sg;
	getrusage(, &sg);
}
