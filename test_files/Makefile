all:
	make test  2>&1 | grep "MSK\|reclaims\|run.sh\|Bonjours" > log
test:
	@date
	gcc test0.c -o test0 -L.. -lft_malloc
	gcc test1.c -o test1 -L.. -lft_malloc
	gcc test2.c -o test2 -L.. -lft_malloc
	gcc test3.c -o test3 -L.. -lft_malloc
	gcc test3bis.c -o test3bis -L.. -lft_malloc
	gcc test4.c -o test4 -L.. -lft_malloc
	gcc test4bis.c -o test4bis -L.. -lft_malloc
	gcc test5.c -o test5 -L.. -lft_malloc

	./run.sh /usr/bin/time -l ./test0
	./run.sh /usr/bin/time -l ./test1
	./run.sh /usr/bin/time -l ./test2
	./run.sh /usr/bin/time -l ./test3
	./run.sh /usr/bin/time -l ./test3bis
	./run.sh /usr/bin/time -l ./test4
	./run.sh /usr/bin/time -l ./test4bis
	./run.sh /usr/bin/time -l ./test5

clean:
	rm -f ./test0 ./test1 ./test2 ./test3 ./test3bis ./test4 ./test4bis ./test5 *.so