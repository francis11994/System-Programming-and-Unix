.PHONY: coverage
.PHONY: clean

rpn : rpn.c
	gcc -Wall rpn.c -o rpn
coverage :
	gcc -fprofile-arcs -ftest-coverage -o rpn rpn.c
clean :
	/bin/rm -f rpn *.gcda *.c.gcov *.gcno
