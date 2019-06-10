#include <stdio.h>
#include <stdlib.h>

int foo(int y)
{
  long i = 1;

  while (y > 0) {
    if (i % 8 != 0) {
      i *= 5;
      y -= 5;
    }
    else {
      i /= 2;
      y += 3;
    }
  }
  
  return i;
}

int main(int argc, char *argv[])
{
  int n;

  if (argc < 2) {
    fprintf(stderr, "Usage: %s num\n", argv[0]);
    exit(1);
  }
  
  n = atoi(argv[1]);

  printf("foo(%d) = %d\n", n, foo(n));
  
  return 0;
}
