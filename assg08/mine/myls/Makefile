.PHONY: coverage
.PHONY: clean

myls : myls.c
	gcc -Wall myls.c -o myls
coverage :
	gcc -fprofile-arcs -ftest-coverage -o myls myls.c
clean :
	/bin/rm -f myls *.gcda *.c.gcov *.gcno
	
