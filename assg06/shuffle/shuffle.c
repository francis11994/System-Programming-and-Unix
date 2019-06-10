/*
 File: shuffle.c
 Author: Francis Kim
 Purpose: This progrem simulates a technique, known as riffle shuffle, for mixing up the cards in a card deck.
*/ 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int echo = 0;

// void printRemain(char *original) -- this function print out remain out input1 and input2

void printRemain(char *original){

	char *copy;
	int num, space;
	copy = original;
	while(sscanf(copy, "%d %n", &num, &space) != EOF){
		printf("%d\n", num);
		copy = copy + space;
	}

}

// checkError(char *original) -- this function check the error, and if there is error then return 0, if not then return 1

int checkError(char *original){

	char *copy, character, *remain;
	copy = original;
	int error = 0;
	int status = 1, length;
	while(sscanf(copy, "%c", &character) != EOF){
		error = 0;
		if(character == ' '){
			status = 1;
			copy++;
			error = 1;
		}else if(character == '\t'){
			status = 1;
			copy++;
			error = 1;
		}else if(character == '\n'){
			status = 1;
			copy++;
			error = 1;
		}else if(character >= 48 && character <= 57){
			status = 0;
			copy++;
			error = 1;
		}else if((character == 43 || character == 45) && status && (*(copy+1) >= 48 && *(copy+1) <= 57)){
			status = 0;
			copy++;
			error = 1;
		}

		if(error == 0){
			length = strlen(copy);
			remain = malloc(length*sizeof(char));
			sscanf(copy, "%s", remain);
			fprintf(stderr, "Error: non-numberic character(s) in input: %s\n", remain);
			copy++;
			echo = 1;
			return 0;
		}
	}

	return 1;
}

//int main() -- this function is combined with checkError, if checkError is return false then print out the number that we shuffle

int main(){

	char *input1 = NULL;
	char *input2 = NULL;
	char *copy, *copy2;
	int number1, number2, count = 1;
	int space1, space2;
	size_t size;

	while(getline(&input1, &size, stdin) != EOF){
		
		if(count == 1){
			getline(&input2, &size, stdin);
		}
		if(count == 1){
			copy = input1;
			count++;
		}
		if(count == 2){
			copy2 = input2;
			count++;
		}

		if(count == 3){
			if(checkError(copy) && checkError(copy2)){
				while(sscanf(copy, "%d %n", &number1, &space1) != EOF && sscanf(copy2, "%d %n", &number2, &space2) != EOF){
					printf("%d\n", number1);
					printf("%d\n", number2);
					copy = copy + space1;
					copy2 = copy2 + space2;
				}
				printRemain(copy), printRemain(copy2);
			}else{
				return 1;
			}
			return 0;
		}
	}
		
	return echo;
}
