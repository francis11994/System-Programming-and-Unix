/*
 * File: famrel.h
 * Author: Francis Kim
 * Purpose: header file for mymake program
 *
*/
#ifndef MYMAKE_H_
#define MYMAKE_H_
typedef struct node{
		int placeNotice;
		int num;
		char *head;
		struct node *right;
		struct node *below;
} Node;
extern FILE *inputFile;
extern Node *target;
extern Node *copyTarget;
extern int error1;

//void searchTarget(char *eachWord)--search the target and catch error
void searchTarget(char *eachWord);
//int checkError(int arg, FILE *input, char *ch)--check first error
int checkError(int arg, FILE *input, char *ch);
//char* save(FILE *f)--save the words
char* save(FILE *f);
//void freeMemory()--free memory
void freeMemory();
//void below(char *b)--connect the node in below side
void below(char *b);
//void right(char *r)--connect the node in right side
void right(char *r);
//int checkword(char *f)--check word error
int checkword(char *f);
//void get(char* pt1,char *pt2)-- get a word
void get(char* pt1,char *pt2);
//void actToBelow(Node *node, char *b)--copy the word
void actToBelow(Node *node, char *b);
//void missingError(char *eachWord)--Error catch
void missingError(char *eachWord);
//void final(char *fi, FILE *inputFile)--catch the error at last
void final(char *fi, FILE *inputFile);
void specifyError(char *eachWord);
#endif 
