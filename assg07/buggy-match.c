/*
 * File: match.c
 * Purpose: This program uses the Knuth-Morris-Pratt algorithm
 * to implement string matching.  It is invoked as follows:
 *
 *	a.out str [fname]
 *
 * It reads in one line at a time from the file fname (stdin
 * is the default), and matches this line against the string
 * str.  Any line that matches is printed on stdout.  A return
 * status of 0 indicates normal termination, 1 indicates abnormal
 * termination.
 *
 * ASSUMPTION: A line of text is at most 1024 characters long.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **ff;	    /* points to failure function array */

/* compute_ff() computes the failure function for the given
   pattern.						 */

void compute_ff(char *pat, int n) {
    int i, j;

    ff[0] = pat;
    for (j = 2; j <= n; j++) {
      i = ff[j-2] - pat;
      while (i > 0 && pat[j-1] != pat[i]) {
	i = ff[i-1] - pat;
      }
      if (pat[j-1] == pat[i]) {
	ff[j-1] = pat+i+1;
      }
      else {
	ff[j-1] = pat;
      }
    }
}

void init(char *pat) {
    int len;

    if (pat == NULL) {
      fprintf(stderr, "Null pattern!\n");
      exit(-1);
    }

    len = strlen(pat);
    ff = malloc( len*sizeof(int) );
    if (ff == NULL) {
      fprintf(stderr, "Out of memory!\n");
      exit(-1);
    }

    compute_ff(pat, len);
}    

int match(char *pat, char *str) {
    char *p = pat;
    
    if (str == NULL) {
      return -1;
    }

    while (*str != '\0' && *p != '\0') {
      if (*p++ != *str++) {
	p = ff[pat-p];
      }
    }

    return (*p != '\0');
}

/* read_args reads the command line arguments and sets things
   up for further processing.  It returns 0 if everything goes
   OK, 1 if there is an error.				*/

int read_args(int argc, char **argv, char **str_ptr, FILE **fp_ptr) {
  if (argc < 2 || argc > 3) {
    return 1; /* wrong no. of arguments */
  }

  *str_ptr = *++argv;
  if (argc == 3) {	/* a filename has been specified */
    *fp_ptr = fopen(*++argv, "r");
    if (*fp_ptr == NULL) {
      perror(*argv);
      return 1;   /* could not open file */
    }
  }
  else {
    *fp_ptr = stdin;
  }

  return 0;
}

/* xgetline() reads in one line from the file specified by fp, and
   stores upto LEN chars in the array line[].  It returns NULL
   to indicate end of file, line[] otherwise;			*/

int xgetline(FILE *fp, char line[]) {
    int ch, cnt = 0;

    while ((ch = getc(fp)) != EOF && ch != '\n')
	if (cnt < 1024) line[cnt++] = ch;
    line[cnt] = '\0';
    if (ch == EOF && cnt == 0) return -1;
    else return cnt;
}

int main(int argc, char **argv) {
    char *str, line[1025];
    FILE *fp;

    if (read_args(argc, argv, &str, &fp) != 0) {
      return 1;
    }

    init(str);

    while (xgetline(fp, line) >= 0) {
      if (match(str, line) == 0) {
	printf("%s\n", line);
      }
    }

    return 0;
}