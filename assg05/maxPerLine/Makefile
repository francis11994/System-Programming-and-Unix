.PHONY: clean
.PHONY: coverage

maxPerLine: maxPerLine.c
		gcc -Wall maxPerLine.c -o maxPerLine
coverage :
		gcc -fprofile-arcs -ftest-coverage -o maxPerLine maxPerLine.c
clean:
	/bin/rm -f maxPerLine *.gcda *.c.gcov *.gcno 
