/* 
* File: vowels.c
* Author: Francis Kim
* Purpose: Find a word that having alphabetical vowel order. For example, 'a' should be come out before 'e', 'i', 'o', 'u'. if not, it is error.
*/
#include <stdio.h>
#include <stdlib.h>

/*
 main() -- input a any words which could be not having meaning, but it must in order of vowels. If it is true return 1, and if it is not return 0.
*/
int main(void)
{
	char input1[64];
	int status, i, a=0, save[64], count=0, fact=6, z, k, retu=0;

	while((status = scanf("%s", input1)) != EOF){
		a=0;	
		k=0;
		fact=6;		

		for(z=0; input1[z] != '\0'; z++){
			
			if(input1[z] >= 65 && input1[z] <= 90){
				input1[z] = input1[z] + 32;
			}
			if((input1[z] < 65 || input1[z] > 90) && (input1[z] < 97 || input1[z] > 122)){
				fprintf(stderr, "Error: please input only alphabet character, your input is '%s', we found '%c' in your input \n", input1, input1[z]);
				k=1;
				retu = 1;
				break;	
			}
		}

		for(i=0; input1[i] != '\0'; i++){
			if(input1[i] == 97 || input1[i] == 101 || input1[i] == 105 || input1[i] == 111 || input1[i] == 117){
				save[a] = input1[i];
				if(count >= 1){
					if(save[a] > save[a-1]){
						fact = 5;	
					}
					if(save[a] < save[a-1]){
						fact = 6;
						break;
					}
				}
				
				a++;
				count++;
			}else{
				fact = 5;
			}
		}	
		if(k == 0){
			if(fact==5){
				printf("%d\n", 1);
				
			}
			if(fact==6){
				printf("%d\n", 0);
				retu = 1;
			}
		}

	}
	return retu;
}
