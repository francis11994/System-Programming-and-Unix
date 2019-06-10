/*
* File: sumDigits.c
* Author: Francis Kim
* Purpose: input number, and then print out sum of each digit number. if you are not input positive number, then print out error message.
*/

#include <stdio.h>
#include <stdlib.h>
/*
* sumOfDigits(int num) -- returns the sum of each digit numbers of 'num'. 'num' * is input value in main function using scanf.
*/

int sumOfDigits(int num)
{
	int rev_num = 0;
	int total;
	
	while(num > 0)
	{
		rev_num = rev_num + num%10;
		num = num/10;
	}
	
	total = rev_num;

	return total;
}

int main(void)
{
	
	int input, input1, status;
		
	while((status = scanf("%d %d", &input, &input1)) != EOF ){	
		if(status == 0){
			printf("Error: please input integer, not character\n");
			return 1;
		}
		if( input <= 0){
		printf("Error: your input %d is not positive number \n", input);
			return 1;
		} 
		if( input > 0){
			printf("%d\n", sumOfDigits(input));
		}
	}
	return 0;
}









