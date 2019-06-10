/*
* File: sumSquares.c
* Author: Francis Kim
* Purpose: Gave the range x to y, and find a number which is sum of squares in given ragne
*/

#include <stdio.h>
#include <stdlib.h>

int main(void){

	int start, end, status, count = 0, count1=0;
	int a, b, c, d, e = 0;
	int sum;
	

	while((status = scanf("%d", &d)) != EOF){
		
		if(status == 0){
			printf("Error: please input positive integer \n");
			return 1;
		}
		if(d <= 0){
			printf("Error : please input integer, not character \n");
			return 1;
		}

		if(count == 0){
			start = d;
			count++;
		}else if(count == 1){
			end = d;
			count1++;	
		}
	
	if(count == 1 && count1 == 1){
		if(start > 0 && end > 0){
		
			for(a = start; a <= end; a++)
			{
				
				for(b = 1; b <= end; b++)
				{
					for(c = b; c <= end; c++)
					{
						sum = b*b + c*c;			
						if(a == sum){
							if(e == 0)
							{        	printf("%d\n", a);
							}	
						}
				
					}
				}
				e = 0;
			}	
					
		}
		
	}
		
	}
	return 0;

}
