/*
 * File: getline-example.c
 * Purpose: Example to show how to use getline().
 */

// #define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  size_t n = 10;
  char *line = malloc(10);
  
  while (getline(&line, &n, stdin) > 0) {
    printf("[len = %lu, space = %lu, line address = 0x%lx]\n line = %s\n", 
      strlen(line), n, (unsigned long) line, line);
  }

  free(line);
  
  return 0;
  
}
