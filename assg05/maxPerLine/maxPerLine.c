// Author: Francis Kim
// File: maxPerLine.c
// Purpose: Print out the largest number in each input line

#include <stdio.h>
//int main()-- print out error statement and largest number in each input line
int main(){

	size_t size;
	char *buffer = NULL;
	int a;
	int result, status, z=0, result1=0;
	int i = 0;
	while(getline(&buffer, &size, stdin) != EOF){
		i=0;
		z=2;
		while((status = sscanf(buffer, "%d", &a)) != EOF){
			if(status == 0){
				z=0;
				result1 = 1;
				break;
			}
			if(i == 0){
				result = a;
				i++;
			}else if(i > 0){
				if(result < a){
					result = a;
				}	
			}
					
			buffer++;
			z=1;
		}
		if(z==0){
			fprintf(stderr, "Bad input\n");
			result1 = 1;
		}else if(z==1){
		printf("%d\n", result);	
		}else if(z==2){
			fprintf(stderr, "Empty String\n");
			result1 = 1;
		}
	}
	return result1;
}
