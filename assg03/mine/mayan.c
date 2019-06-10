/*
* File: mayan.c
* Author: Francis Kim
* Purpose: Input the character number which is base 20, and convert them to decimal number.
*/

#include <stdio.h>
#include <string.h>
/*
* power1(length1, exponent) -- This function returns the power of 20. length1 is the length of input, and exponent is the determine each number's own exponent. 
*/
int power1(int length1, int exponent){

	int a, base=20, value=1;
	for(a=exponent; a <= length1; a++){
		if(a < length1){
		value = base*value;
		}
	}

	return value;
	
}

/*
* main() reads in a sequence of character from 'a' to 't', and convert them to b* ase 20 numbers. If we input other characters or number except 'a' to 'b', then* it prints out error.
*/
int main(void)
{
	char input[64];
	int status, i, access, value, length, length2, decimal, retu=0;
	while((status = scanf("%s", input)) != EOF){
		access = 6;
		decimal = 0;
		length = strlen(input);
		length2 = length;
		
		for(i=0; input[i] != '\0'; i++){
			
			if(input[i] >=65 && input[i] <= 90){
				input[i] = input[i] + 32;
			}
			
			if(input[i] < 97 || input[i] > 116 ){
				fprintf(stderr, "Invalid input based on 20, your input is %s, and invalid digit: %c \n", input, input[i]);
				access = 5;
				retu = 1;
				break;
			}
			
		}

		if(access == 6){
			for(i=0; i <= length-1; i++){
				value = 0;
				if(input[i] >= 97 && input[i] <= 106){
					input[i] = input[i] - 97;
					value = input[i];
					
				}
				if(input[i] >= 107 && input[i] <= 116){
					input[i] = input[i] - 107;
					value = input[i] + 10;
				}
				decimal = decimal + value*power1(length2-1, i);
			}
			printf("%d\n", decimal);	
		}
		
	} 

	return retu;
}
