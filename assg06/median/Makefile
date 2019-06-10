.PHONY: clean
.PHONY: coverage

median : median.c
	gcc -Wall median.c -o median
coverage :
	gcc -fprofile-arcs -ftest-coverage -o median median.c
clean :
	/bin/rm -f median *.gcda *.c.gcov *.gcno
