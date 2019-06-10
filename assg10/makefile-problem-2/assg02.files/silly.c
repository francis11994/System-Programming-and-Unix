/*
 * silly.c
 * Don't worry about what it does.
 * Just make it compile without warnings
 */

//Don't touch the code below this line
int main(int argc, char **argv) {
  int seed;
  assert(argc > 1);
  sscanf(argv[1], "%d", &seed);
  srand(seed);
  int r = rand();
  r = (r%15)+2;
  char wd[20];
  printf("Enter a word with %d letters \n", r);
  scanf("%19s", wd);	
  if (strlen(wd) == r) 
    printf("Correct\n");
  else
    printf("Wrong number of letters\n");
  return 0;
}
