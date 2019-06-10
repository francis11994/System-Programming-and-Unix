/*
 File: median.c
 Author: Francis Kim
 Purpose: Type the number, and get a median
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct s{
	double realNum;
	struct s *next;
}node;
node *head = NULL;
static int count=0;
//push the data into stack
void push(double val)
{
    node *pt;
    pt = malloc(sizeof(node));
    pt->realNum = val;
    pt->next = head;
    head = pt;
}

//pop data from the stack
double pop(node *head)
{
    node *pt;
    if (head == NULL) {
	return 0;
    }
      pt=head;
    return pt->realNum;
}
// int checkError(char *original) -- this function check the error, if there is error then return 0, if not then return 1
int checkError(char *original){

	char *copy, character;
	copy = strdup(original);
	int status = 1;	
	while(sscanf(copy, "%c", &character) != EOF){

		if(character == ' ' || character == '\n' || character == '\t'){
			status = 1;
			copy++;
		}else if((character >= 48 && character <= 57) && ((character != '-') || (character != '+'))){
			status = 1;
			copy++;
		}else if((character == '-' || character == '+') && status && (*(copy + 1) >= 48 && *(copy + 1) <= 57)){
			status = 0;
			copy++;
		}else{
			fprintf(stderr, "Error: non-numeric character(s) in input\n");
			return 0;
		}	
	} 

	return 1;
}

// double getMedian(int *num) -- this function find a median number from we input
double getMedian(int *num){

	int *copy;
	int i, j, length = 0, temp;
	double value, value2, value3;
	copy = num;
	
	while(*num != '\0'){
		length++;
		num++;
	}

	for(i=0; i < length; i++){
		for(j=i+1; j < length; j++){
			if(*(copy+i) > *(copy+j)){
				temp = *(copy+i);
				*(copy+i) = *(copy+j);
				*(copy+j) = temp;
			}
		}
	}

	if(length%2 == 0){
		value = *(copy+(length/2));
		value2 = *(copy+((length/2) - 1));
		value3 = (value + value2) / 2;
		return value3;
	}else if(length%2 == 1){
		return *(copy+(length/2));
	}
	return 0;
}

// int main() -- this main function is combined with errorCheck and getMedian function, finally we can get results of median.
int main(){

	char *buffer = NULL;
	size_t size, turn = 0;
	int num, space;
	int *copyNum;
	int *realNum;
	double result;
	while(getline(&buffer, &size, stdin) != EOF){
		if(*buffer!='\n'){
		count++;
		}
		if(turn == 0){
			copyNum = malloc(1025*sizeof(int));
			realNum = copyNum;
		}
		turn = 1;
		if(turn == 1){
			if(checkError(buffer)){
			
			}else{
				return 1;
			}
			turn++;
		}
		if(turn > 1){
			while(sscanf(buffer, "%d %n", &num, &space) != EOF){
				*copyNum = num;
				copyNum++;	
				buffer = buffer + space;
			}
		}

	}
		
	if(count > 0){
	push(getMedian(realNum));
	result = pop(head);
	printf("%f\n", result);
	}else if(count==0){
		fprintf(stderr, "Error: no inputs found\n");
		return 1;
	}
	
	return 0;
}
