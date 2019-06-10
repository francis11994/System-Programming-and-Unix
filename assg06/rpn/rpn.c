/*
 File: rpn.c
 Author: Francis Kim
 Purpose: This program involves writing a calculator that evaluates expressions in Reverse Polish notation
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct s{
	int num;
	struct s *next;
}node;
node *head = NULL;

// push data into stack
void push(int val)
{
    node *pt;
    pt = malloc(sizeof(node));
    pt->num = val;
    pt->next = head;
    head = pt;
}
//pop the data from stack
int pop(node *head)
{
    node *pt;
    if (head == NULL) {
	return 0;
    }
    pt = head;
    return pt->num;
}
// int integer(char *original) -- this function check input is wheather number or not
 
int integer(char *original){

    int length=strlen(original)-1;

	while(length != -1){
		if((*original+length) < 48 || *(original + length) > 57){
			return 0;
		}
		length--;
	}

    return 1;
}

// int checkOutput(int check) -- this is check the how many number acount. if number acount is bigger than 1 then return 0 which is false, or not return 1 true

int checkOutput(int check){

	if(check > 1){
		return 0;
	}else{
		return 1;
	}
}		


// int errorCheck(char *original) -- this function will check wheather input is correct input or not
 
int errorCheck(char *original){
    int count;
    int i;
    if(*original >= 48 && *original <= 57){

        count = 1;
       
	for(i = 0; *(original+count) != 0; i++){
            if(*(original+count) > 57|| *(original+count) < 48){

                fprintf(stderr,"ERROR [eval]: invalid input %s\n", original);
                return 1;
            }
            count++;
	}
        return 0;
    }

    if(*original == 43 || *original == 45 || *original == 42 || *original == 47){
        if(*(original+1) != '\0'){

            fprintf(stderr,"ERROR [eval]: unrecognized operator\n");
            return 1;
        }
        return 0;
    }
    else{
        fprintf(stderr,"ERROR [eval]: unrecognized token %s\n", original);
        return 1;
    }
}
// int main() --  this main function combined with num and check function, so it will calculate all our inputs
 
int main(){

    static int terminate =0;
    char *point;
    char *tok;
    int *pt1, save;
    int print = 0;
    int count, result1, result=0, value;
    size_t size;

    point = malloc(sizeof(char)*1025);
    if(point==NULL){

        fprintf(stderr,"ERROR: Memmory delocated");
        return 1;

    }

    while(getline(&point, &size,stdin)!=EOF){
	print=0;
	result1 = 1;
        count=0;
	tok = malloc(sizeof(char)*strlen(point));
	pt1 = malloc(sizeof(int)*strlen(point));
        if(tok == NULL){

            fprintf(stderr, "ERROR: Memmory delocated\n");
            return 1;

        }else if(pt1 == NULL){
	    fprintf(stderr, "ERROR: Memmory delocated\n");
	}
        while ((tok = strtok(point, " \t\n")) != NULL){
	    print++;
            point = NULL;
            if(errorCheck(tok)){
                terminate = 1;
		result1 = 0;
	    }else if(integer(tok)){ 
                                
                *(pt1+count)=atoi(tok);
                count++;
		
  	    }else if(count < 2){
		
                fprintf(stderr, "ERROR [eval]: not enough operands\n");
                terminate = 1;
		result1=0;

      	    }else{
		print++;
		if(*tok == 43){
			save = 3;
		}else if(*tok == 45){
			save = 4;
		}else if(*tok == 42){
			save = 5;
		}else if(*tok == 47){
			save = 6;
		}
		switch(save){
		
			case 3 :
				count--;
				*(pt1+count-1) += *(pt1+count);
				break;
			case 4 :
				count--;
				*(pt1+count-1) -= *(pt1+count);
				break;
			case 5 :
				count--;
				*(pt1+count-1) *= *(pt1+count);
				break;
			case 6 :
				count--;
				*(pt1+count-1) /= *(pt1+count);
				break;
		}
		
	    }
	   
        }
        
        if(checkOutput(count) && result1==1){

            result=*pt1;
	    push(result);
	      value = pop(head);	
	    if(print > 0){ 
            printf("%d\n",value);
	    }
	    print = 0;
	    
        }else if(count > 1){
		fprintf(stderr, "ERROR [eval]: too many operands\n");
		terminate = 1;
	}
  

    }


    return terminate;
}
