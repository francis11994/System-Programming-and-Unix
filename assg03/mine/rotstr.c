

//This is the most recent coding for rotstr.c. I added coding standard.

/*
* File: rotstr.c
* Author: Francis Kim
* Purpose: Change the character from inputting value at first how much you move.
*/

#include <stdio.h>


/* main() -- If at first input is not integer, then it will return error end terminate the system. If you input proper integer, then you can input character at second
* and change the character by at first input which is integer.
*/

int main(void){


	int move;
	int status, i, sum, a, value, retu=0;
	int access, real;
	status = scanf("%d\n", &move);
	real = move;
	if(status == 0){
		fprintf(stderr, "Error: First input must be the integer\n");
		return 1;
	}
	
	if(move < 0){
	move = -move;
	}	
	sum = move%26;
	
	char input[64];

	while( scanf("%s", input) != EOF){
		access = 5;
		for(i=0; input[i] != '\0'; i++){
		
			value = input[i];	
			if(input[i] >= 65 && input[i] <= 90){
					
					if(real >= 0){
						value = value + sum;
						if(value > 90){
							a = value - 90;
							input[i] = 64 + a;
						}else{
							input[i] = value;
						}
						
					}
					if(real < 0){
						value = value - sum;
						if(value < 65){
							a = 65 - value;
							input[i] = 91 - a;
						}else{
							input[i] = value;
						}
					}
				
			}else if(input[i] >= 97 && input[i] <= 122){
					if(real >= 0){
						value = value + sum;
						if(value > 122){
							a = value - 122;
							input[i] = 96 + a;
						}else{
							input[i] = value;
						}
					}
					if(real < 0){
						value = value - sum;
						if(value < 97){
							a = 97 - value;
							input[i] = 123 - a;
						}else{
							input[i] = value;
						}
					}
			}else if(input[i] >= 48 && input[i] <= 57){
			}
			else{
				fprintf(stderr,"The input is not alphanumerical: %s\n", input);
				access = 6;
				retu = 1;
				break;			
			} 
		}
		if(access == 5){
			printf("%s\n", input);
			
		}
		
	}
	return retu;
	
}
