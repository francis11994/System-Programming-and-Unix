/*
 *File: myls.c
 * Author: Francis Kim
 * Purpose: This is to implement the basic funtionality of the Unix command ls that lists the files in a directory
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

struct dirent *read;
typedef struct s{
		char *str;
		struct s *next;
}node;
//int error(DIR *dir, FILE *file1, char *d) -- check the error
int error(DIR *dir, FILE *file1, char *d);
//void printNode(node *nameOfFile) -- print all node
void printNode(node *nameOfFile);
//void insert(char *str, node *nameOfFile) -- insert all node
void insert(char *str, node *nameOfFile);
//int main(int argc,char *argv[]) -- operate all function and print outputs
int main(int argc,char *argv[]){

	DIR *dir;
	FILE *file1 = malloc(100);
//	int turn=0;
	char *d=malloc(129);
	strcpy(d,".");
	if(argc>2){ 	
		fprintf(stderr,"Usage: myls [directory]\n");	
		return 1;
	}else if(argc==2)
	{
		strcpy(d, argv[1]);
	}
	dir=opendir(d);
	file1=fopen(d,"r");
	if(error(dir, file1, d)){
		return 1;
	}else{
		fclose(file1);
		free(d);
//		turn = 1;
		node* nameOfFile=malloc(sizeof(node));
		nameOfFile->str=malloc(129);
		nameOfFile->next=NULL;
		while((read = readdir(dir))!=NULL){		
			insert(read->d_name,nameOfFile);
		}
		printNode(nameOfFile);
		closedir(dir);
	}

	return 0;
}

int error(DIR *dir, FILE *file1, char *d){

	if(dir==NULL&&file1==NULL){ 	
		fprintf(stderr,"%s: No such file or directory\n",d);	
		return 1;
	}
	if(dir==NULL){ 	
		fprintf(stderr,"%s: Not a directory\n", d);	
		return 1;
	}
	return 0;
}
void printNode(node *nameOfFile){
	while(nameOfFile!=NULL){
	printf("%s\n", nameOfFile->str);
	free(nameOfFile->str);
	node *temp=nameOfFile;
	nameOfFile=nameOfFile->next;
	free(temp);
	}
}
void insert(char *str, node *nameOfFile){
	node *newNameOfFile = malloc(129);
	if(strcmp(nameOfFile->str,"")==0)	{
		strcpy(nameOfFile->str,str);
		return;
	}
	newNameOfFile->str=malloc(129);
	strcpy(newNameOfFile->str,str);
	newNameOfFile->next=NULL;

	if(strcmp(str,nameOfFile->str)<0){
		strcpy(newNameOfFile->str,nameOfFile->str);
		newNameOfFile->next=nameOfFile->next;
		strcpy(nameOfFile->str,str);
		nameOfFile->next=newNameOfFile;	
		return;
	}else if(nameOfFile->next!=NULL){
		insert(str,nameOfFile->next);
		return;
	}
	else{
		nameOfFile->next=newNameOfFile;
	}
	
}
