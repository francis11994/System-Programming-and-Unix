.PHONY: all clean

rotstr : rotstr.c
	gcc -Wall rotstr.c -o rotstr

vowels : vowels.c
	gcc -Wall vowels.c -o vowels
coverage : rotstr.c
	gcc -fprofile-arcs -ftest-coverage rotstr.c
clean:
	/bin/rm -f rotstr vowels
