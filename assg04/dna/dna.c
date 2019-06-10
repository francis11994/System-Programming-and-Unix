/*
* File: dna.c
* Author: Francis Kim
* Purpose: Compare DNA obtained from a suspect with DNA obtained from a crime scene to see if there is a match.
*/

#include <stdio.h>
#include <string.h>

/*
* sumofDna(first, second) -- this function compare the two numbers between number of higher than 6, or compare number of lower than 6 from first input and second input   of value, and return lower value. But if number of first and second vale is same, then return any first or second value. 
*/
int numOfDna(int first, int second){

	int decide;
	if(first > second){
		decide = second;
	}
	if(second > first){
		decide = first;
	}
	if(second == first){
		decide = first; // we can also do "decide = second"
	}
	return decide;
}

/*
* main() -- input two integer value which are suspect and crime scene, and return the matching DNA for them.

*/
int main(void){

	char input1[1025];
	char input2[1025];
	int status, length1, length2, numOfInput=0, i, a;
	int lower1=0, lower2=0, higher1=0, higher2=0;
	int lowerValue, higherValue, sum;
	scanf("%s", input1);
	length1 = strlen(input1);

	numOfInput = 1;
	while((status = scanf("%s", input2)) != EOF){
	
		numOfInput = 2;
		length2 = strlen(input2);
	
		if(length1 != length2){
			fprintf(stderr, "Input strings are not of the same length \n");
			return 1;
		}	
		for(i = 0; input1[i] != '\0'; i++){
			if(input1[i] > 57 || input1[i] < 48){
				fprintf(stderr, "Illegal character in input: %c \n", input1[i]); 
				return 1;
			}
			if(input1[i] >= 48 && input1[i] <= 54){
				lower1++;
			}
			if(input1[i] >= 55 && input1[i] <= 57){
				higher1++;
			}
		}
		for(a = 0; input2[a] != '\0'; a++){
			if(input2[a] > 57 || input2[a] < 48){
				fprintf(stderr, "Illegal character in input %c \n", input2[a]);
				return 1;
			}
			if(input2[a] >= 48 && input2[a] <= 54){
				lower2++;
			}
			if(input2[a] >= 55 && input2[a] <= 57){
				higher2++;
			}
		}
		
		lowerValue = numOfDna(lower1, lower2);
		higherValue = numOfDna(higher1, higher2);
		sum = lowerValue + higherValue;
		
		if(numOfInput == 2){
			printf("%d\n", sum);
			break;
		}
	}
	if(numOfInput == 1){
		fprintf(stderr, "Not enough inputs \n");
		return 1;
	}
	return 0;
}
