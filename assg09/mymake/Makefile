CFLAGS = -Wall
COVFLAGS = -Wall -fprofile-arcs -ftest-coverage
OBJ = mymake.o graph.o

famrel: $(OBJ)
	gcc $(CFLAGS) $(OBJ) -o mymake

%.o : %.c mymake.h
	gcc $(CFLAGS) -c $*.c

.PHONY:coverage
coverage:
	gcc $(COVFLAGS) -o mymake graph.c mymake.c


clean:
	rm -f *.o mymake *.gcov *.gcno *.gcda
