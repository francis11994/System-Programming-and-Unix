CC = gcc
CFLAGS = -g -Wall -m32

.PHONY: all clean
all : mayan palindromes rotstr vowels

mayan : mayan.c
	$(CC) $(CFLAGS) mayan.c -o mayan

palindromes : palindromes.c
	$(CC) $(CFLAGS) palindromes.c -o palindromes

rotstr : rotstr.c
	$(CC) $(CFLAGS) rotstr.c -o rotstr

vowels : vowels.c
	$(CC) $(CFLAGS) vowels.c -o vowels

clean:
	/bin/rm -f mayan palindromes rotstr vowels