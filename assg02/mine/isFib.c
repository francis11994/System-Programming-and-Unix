/*
* File: isFib.c
* Author: Francis Kim
* Purpose: Input numbers, and find a fibonacci number, if not print out error.
*/

#include <stdio.h>
#include <stdlib.h>

int main(void){

	int n, status, sum, sum1, retu=0;
	int a;
	int first, second;
	while((status = scanf("%d", &n)) != EOF){

		first = 0;
		second = 1;	
		if(status == 0){
			printf("Error: please input integer \n");
			return 1;
		}
			
		if(n <= 0){
			printf("Error : %d is not positive number \n", n);
			retu = 1;
		}
		if(n > 0){	
		
			for(a = 2;a <= n+1; a++){
				sum = first + second;
				first = second;
				second = sum;
				if(sum == n){
					printf("%d is fib \n", n);
					sum1 = sum;
				}		
		
			}
			if(sum1 != n){
				printf("%d is not fib \n", n);
			}
			
		}
			
	}	

	return retu;
}
