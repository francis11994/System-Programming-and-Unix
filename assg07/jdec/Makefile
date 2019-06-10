.PHONY: coverage
.PHONY: clean

jdec : jdec.c
	gcc -Wall jdec.c -o jdec
coverage :
	gcc -fprofile-arcs -ftest-coverage -o jdec jdec.c
clean :
	/bin/rm -f jdec *.gcda *.c.gcov *.gcno
