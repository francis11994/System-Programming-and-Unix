/*
  Author: Francis Kim
  File: mymake.c
  Purpose: implements part the core funcionality of the make utility
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mymake.h"

//int main(int argc, char *argv[])--combined all functions and work together
int main(int argc, char *argv[]){
	char *eachWord;
	// check error
	inputFile=fopen(argv[1],"r");
	if(checkError(argc, inputFile, argv[1])){
		return 1;
	}else{
		eachWord=save(inputFile);
		if(eachWord!=NULL){
			searchTarget(eachWord);
		while(!strcmp(eachWord,"@target")){
			missingError(eachWord);
			while((eachWord=save(inputFile))!=NULL){
				if(!strcmp(eachWord,"@cmd")){
					break;
				}
				if(*eachWord=='@'){ 	
					fprintf(stderr,"Illegal eachWord: %s\n",eachWord); 
					free(eachWord);	
					freeMemory();	
				}
				right(eachWord);		
			}	
			specifyError(eachWord);
			while((eachWord=save(inputFile))!=NULL){
				if(!strcmp(eachWord,"@target")){
					break;
				}
				if(*eachWord=='@'){	
					fprintf(stderr,"Illegal eachWord: %s\n",eachWord);	
					free(eachWord);	
					freeMemory();	
				}
				free(eachWord);
			}
			if(eachWord==NULL){
				break;
			}
		}
	}
	
	final(argv[2], inputFile);
	}
	return 0;
}
