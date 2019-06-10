.PHONY: clean
.PHONY: coverage

wordCount : wordCount.c
		gcc -Wall wordCount.c -o wordCount
coverage :
	gcc -fprofile-arcs -ftest-coverage -o wordCount wordCount.c
clean :
	/bin/rm -f wordCount *.gcda *.c.gcov *.gcno
