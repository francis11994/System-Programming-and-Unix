//Author: Francis Kim
//File: wordCount.c
//Purpose: print a frequency count of all the words coming from input from stdin.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//int main() -- change to Capital to Small letter and strip all the nonalphabethical symbol from end of the string and front of the string. and print frequency of word.
int main(){

	char input[1025], t[20], word[1025];
	char array[1025][1025], *array1="";
	int index=0, i, j, z, o, l, m, index1 = 0, count = 0;
	while(scanf("%s", input) != EOF){
		index1=0;
		for(i = 0; input[i] != '\0'; i++){
			o=5;
			if(input[i] >= 65 && input[i] <= 90){
				input[i] = input[i] + 32;
			}
			if((input[i] < 65 || input[i] > 90) && (input[i] < 97 || input[i] > 122)){
				for(l = i; input[l] != '\0'; l++){
					if((input[l] >= 65 && input[l] <= 90) || (input[l] >= 97 && input[l] <= 122)){
						o=5;	
						if((input[0] < 65 || input[0] >90) && (input[0] < 97 || input[0] > 122)){
							o=6;
						}
						break;
					}else{
						o=6;
					}
				}
			}
			if(o==5){
				word[index1] = input[i];
				index1++;
			}
	
		}
		word[index1] = '\0';
		strcpy(array[index], word);
		index++;
	}
		
		for(i = 1; i < index+1; i++){
			for(j = 1; j < index+1; j++){
				if(strcmp(array[j-1], array[j]) > 0){
					strcpy(t, array[j-1]);
					strcpy(array[j-1], array[j]);
					strcpy(array[j], t);
				}
			}
		}
	
	
	for(z = 1; z < index+1; z++){
		
		count = 1;
		for(m = z+1; m < index+1; m++){
			
			if(strcmp(array[z], array[m]) == 0){
				
				count++;
				
			}
			
		}
		
		if(strcmp(array1, array[z])!=0){	
			printf("%s %d\n", array[z], count);
			array1 = strdup(array[z]);
		}
		
	}
	
	return 0;
}
