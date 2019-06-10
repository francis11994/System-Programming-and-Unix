.PHONY: clean
.PHONY: coverage

battleship : battleship.c
	gcc -Wall -o battleship battleship.c
coverage :
	gcc -Wall -fprofile-arcs -ftest-coverage -o battleship battleship.c
clean :
	/bin/rm -f battleship *.gcda *.c.gcov *.gcno	
	
