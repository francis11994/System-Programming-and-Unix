/*
* File: palindromes.c
* Author: Francis Kim
* Purpose: Write a program to distinguish wheather input is palindrome or not. 
*/
#include <stdio.h>
#include <string.h>

/*
 main() -- input any characters or number, and check them wheather it is true or not. If it is true, then print out 1. If it is not true, then print out 0.
*/
int main(void)
{
	char input1[64];
	int status, length=0,d=5 ,i, a;
		
	while((status = scanf("%s", input1)) != EOF){
		d=5;	
		length = strlen(input1);
		
		for(a=0; a<=length; a++){
			if(input1[a] >= 65 && input1[a] <= 90){
				input1[a] = input1[a] + 32;
			}
		}
			
		for(i=0; i <= length; i++){
			if(input1[i] != input1[length-i-1]){
				d=6;
			}
		}
		if(d==6){
			printf("%d\n", 0);
		}
		if(d==5){
			printf("%d\n", 1);
		}
	}
	return 0;
}
