/*
 Author: Francis Kim
 File: jdec.c
 Purpose: This problem involves writing code to reverse engineer the byte code instructions for expression evaluation whith in the Java virtual machine
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int result=0;
// typedef struct s -- this is struct and make node
typedef struct s{
	char *str;
	struct s *next;
} node;

// void push(node *realStack, char *str1) -- this push data into stack
void push(node *realStack, char *str1){
	node *temp = malloc(sizeof(node));
	if(temp==NULL){
		fprintf(stderr, "Memmory is out of bound\n");
		exit(1);
	}
	temp->str = realStack->str;
	temp->next = realStack->next;
	realStack->str = strdup(str1);
	realStack->next = temp;
}
// char *pop(node *realStack) -- this pop out the first data we input
char *pop(node *realStack){

	char *ptr;
	if(realStack->str == NULL){
		fprintf(stderr, "Memmory is out of bound\n");
		return realStack->str;
	}
	node *temp = realStack->next;
	ptr=realStack->str;
	realStack->str=temp->str;
	realStack->next = temp->next;
	free(temp);
	return ptr; 
}
//void make(char *formula, node *realStack) -- this function update and make from past node to current node that we input recent
void make(char *formula, node *realStack){
	char *end = pop(realStack);
	char *beggining = pop(realStack);
	char *output = malloc(2049);
	if(output == NULL){
		fprintf(stderr, "Memmory is out of bound\n");
		exit(1);
	}
	strcpy(output,"(");
	strcat(output,beggining);
	strcat(output,formula);
	strcat(output,end);
	strcat(output,")");
	free(beggining);
	free(end);
	push(realStack, output);
}	

//int errorCheck(char *original) -- this function check the error of first input and catch the error
int errorCheck(char *original){
	char *copy;
	char *load="iload", *sub="isub", *const1="iconst", *add="iadd", *mul="imul", *div="idiv";
	copy = original;	
	if(strcmp(copy, load)==0 || strcmp(copy, sub)==0 || strcmp(copy, const1)==0 || strcmp(copy, mul)==0 || strcmp(copy, div)==0 || strcmp(copy, add)==0){
		
	}else{
		fprintf(stderr, "ERROR: Unrecognized instruction: %s\n", copy);
		result = 1;
		return 1;
	}
	
	return 0;
}

//int errorLoad(char *original1) -- this function check the error for iload
int errorLoad(char *original1){

	char *copy;
	int length = strlen(original1), num=0;
	copy = original1;
	
	while( num != length){
		if((*(copy+num) < 65 && *(copy+num) > 90) || (*(copy+num) < 97 || *(copy+num) > 122)){
			fprintf(stderr, "ERROR: Non-letter character '%c', in variable name\n", *copy);
			return 0;
		}
		num++;
	}
	return 1;
}

//int errorConst(char *original2) -- this function check the error for iConst
int errorConst(char *original2){
	char *copy;
	int length = strlen(original2), num=0;
	copy = original2;
	while( num != length){
		if(*(copy+num) < 48 || *(copy+num) > 57){
			fprintf(stderr, "ERROR: Non-digit character '%c', in integer literal\n", *copy);
			return 0;
		}
		num++;
	}
	return 1;
}

//int main() -- this function combined all of functions we made and execute the real program
int main(){

	char *buffer = NULL;
	char *tok, count = 0,count1=0, stack=0, save, *copyTok, *result5;
	char *load="iload", *sub="isub", *const1="iconst", *add="iadd", *mul="imul", *div="idiv";
	size_t size;

	node *realStack = malloc(sizeof(node));
	while(getline(&buffer, &size, stdin) != EOF){
		count = 0;
		count1 = 0;

		while((tok = strtok(buffer, "' '\t\n")) != NULL){
			copyTok = tok;
			buffer = NULL;
			if(count == 0){
				if(errorCheck(tok)){
					return 1;	
				}else{
					if(strcmp(tok, load)==0){
						count++;
						count1 = 1;
						save = 3;
					}else if(strcmp(tok, const1)==0){
						count++;
						count1 = 1;
						save = 4;
					}else if(strcmp(tok, sub)==0 || strcmp(tok, add)==0 || strcmp(tok, mul)==0 || strcmp(tok, div)==0){
							
						if(stack >= 2){
							if(strcmp(tok, sub) == 0){
								make(" - ", realStack);
							}
							if(strcmp(tok, add) == 0){
								make(" + ", realStack);
							}
							if(strcmp(tok, mul) == 0){
								make(" * ", realStack);
							}
							if(strcmp(tok, div) == 0){
								make(" / ", realStack);
							}
							stack--;	
						}else if(stack == 1){
							fprintf(stderr, "ERROR: attempt to pop empty stack\n");
							return 1;
						}else if(stack == 0){
							fprintf(stderr, "ERROR: attempt to pop empty stack\n");
							fprintf(stderr, "ERROR: attempt to pop empty stack\n");
							return 1;
						}
						
					}				
				}
			}else if(count == 1){
				count1 = 0;
				if((save == 3) && errorLoad(tok)){
					stack++;
					count++;
					push(realStack, tok);
				}else if(save == 3){
					return 1;
				}
				if((save == 4) && errorConst(tok)){
					stack++;
					count++;
					push(realStack, tok);
				}else if(save == 4){
					return 1;
				}
			}else if(count > 1){
				if(save == 4){
				fprintf(stderr, "too many operands for iconst: %s\n", tok);
				}else if(save == 3){
				fprintf(stderr, "too many operands for iload: %s\n", tok);
				}
				return 1;
			}
		}
		if(count1 == 1){
			printf("ERROR: insufficient arguments: %s\n", copyTok);
			return 1;
		}	
	}
	if(stack >= 2){
		fprintf(stderr, "Systax error: too many items on the stack\n");
		return 1;
	}else{
	result5=pop(realStack);
	printf("%s\n", result5);
	free(result5);
	free(realStack);
	}
	return 0;
}
