.PHONY: coverage
.PHONY: clean

shuffle : shuffle.c
	gcc -Wall shuffle.c -o shuffle
coverage :
	gcc -fprofile-arcs -ftest-coverage -o shuffle shuffle.c
clean :
	/bin/rm -f shuffle *.gcda *.c.gcov *.gcno
