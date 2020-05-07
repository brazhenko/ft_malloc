
int main()
{
//	void *a = malloc(123);
//	void *b = malloc(321);
//	printf("add free: %p\n", free);
//	free1(0xFFFFFFFF);free1(b);

	void *a = malloc(1234);
	void *b = malloc(1234);
	void *c = malloc(1234);
	void *d = malloc(1234);
	void *e =  malloc(1234);
	free(a);free(b);free(c);free(d);free(e);
	// printf("%d %d\n", a, b);
}