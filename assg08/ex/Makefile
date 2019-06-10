.PHONY: coverage
.PHONY: clean

spellcheck : spellcheck.c
	gcc -Wall spellcheck.c -o spellcheck

coverage :
	gcc -fprofile-arcs -ftest-coverage -o spellcheck spellcheck.c

clean :
	/bin/rm -f spellcheck *gcda *.c.gcov *.gcno
