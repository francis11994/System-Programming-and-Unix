CFLAGS = -Wall
COVFLAGS = -Wall -fprofile-arcs -ftest-coverage
OBJ = mymake2.o

mymake: $(OBJ)
	gcc $(CFLAGS) $(OBJ) -o mymake

%.o : %.c mymake2.h
	gcc $(CFLAGS) -c $*.c

.PHONY:coverage
coverage:
	gcc $(COVFLAGS) -o mymake2 mymake2.c
.PHONY:clean
clean:
	rm -f *.o mymake2 *.gcov *.gcno *.gcda
