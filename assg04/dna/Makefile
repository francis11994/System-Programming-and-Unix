.PHONY: clean
.PHONY: coverage

dna : dna.c
	gcc -Wall dna.c -o dna
coverage : 
	gcc -fprofile-arcs -ftest-coverage -o dna dna.c
clean : 
	/bin/rm -f dna *.gcda *.c.gcov *.gcno
