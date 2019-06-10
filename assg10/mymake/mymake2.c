/*
  Author: Francis Kim
  File: mymake.c
  Purpose: implements part the core funcionality of the make utility
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include "mymake2.h"

FILE *inputFile = NULL;
FILE *inputFile2 = NULL;
FILE *inputFile3 = NULL;
DIR *dir = NULL;
Node *target = NULL;
Node *currentDir = NULL;
Node *temp=NULL;
struct dirent *read;
static int trueOrFalse=0;
static int terminate=0;


int checkError(int arg, FILE *input, char *ch){
	if(arg<=2 || arg>=4){
		fprintf(stderr,"Usage ./mymake <input file> <target>\n");
		return 1;
	}
	if(input==NULL){	
		fprintf(stderr,"%s: No such file or directory\n",ch); 
		return 1;
	}
	return 0;
}

void currentfiles(char *in){
	//need to free
	if(currentDir==NULL){
		temp=malloc(sizeof(Node));
		temp->head = strdup(in);
		currentDir=temp;
		temp->right=NULL;
	}else if(temp->right==NULL){
		Node *temp1=malloc(sizeof(Node));
		temp1->head=strdup(in);
		temp->right=temp1;
		temp=temp1;
		temp1->right=NULL;
	}
}

void searchTarget(char *eachWord){
	if(strcmp(eachWord,"@target")){
		fprintf(stderr,"Missing @target\n"); 
		free(eachWord);	
		freeMemory();	
		
	}
}
void below(char *b){
	if(checkword(b)){	
		fprintf(stderr,"Failed to add target %s\n",b); 
		free(b); 
		freeMemory();
	}
	Node *node=malloc(sizeof(Node));
	actToBelow(node, b);
	free(b);
}
void right(char *r){
	Node *newNode=malloc(sizeof(Node)),*next=target;
	newNode->num=0, newNode->head=strdup(r);
	newNode->right=NULL, newNode->below=NULL;
	free(r);
	while(next->right!=NULL)
		next=next->right;
	next->right=newNode;
}

char* save(FILE *f){
	int i=0,chr=-1;
	char *words=malloc(65), *pt=NULL;
	while(!feof(f)){
	chr=fgetc(f);
	if(chr==' '||chr=='\n'||chr=='\t'||chr==EOF){
		if(i==0){
			continue;
		}
		else{
			break;
		}
	}
	*(words+i)=chr;
	i++;
	}
	if(i>0){	
		*(words+i)=0;
		return words;

	}
	free(words);
	return pt;
}
void actToBelow(Node *node, char *b){
	node->num=0;
	node->head = strdup(b);
	node->right=NULL;
	node->below=target;
	target=node;
}
void missingError(char *eachWord){
	free(eachWord);
	if((eachWord=save(inputFile))==NULL){ 	
		fprintf(stderr,"Bad or missing target: @target\n");	
		freeMemory();
	}
	if(*eachWord=='@'){	
		fprintf(stderr,"Bad or missing target: %s\n",eachWord); 
		free(eachWord);
		freeMemory();
	}
	below(eachWord);
	if((eachWord=save(inputFile))==NULL){ 	
		fprintf(stderr,"Missing :\n");
		freeMemory();	
	}
	if(strcmp(eachWord,":")){	
		fprintf(stderr,"Missing :\n");	
		free(eachWord);
		freeMemory();
	}
	
}
void get(char* pt1,char* pt2){
	Node *node=target,*ri;
	while(node!=NULL&&strcmp(node->head,pt1)){
		node=node->below;
	}
	if(node==NULL){ 
		below(strdup(pt1));
		target->num=2;
		temp=currentDir;
		while(temp!=NULL){
			if(strcmp(temp->head,pt1)==0){
				trueOrFalse=1;
			}
			temp=temp->right;
		}
		if(trueOrFalse==0){
			printf("Missing dependency: %s\n", pt1);
			terminate=1;
		}
		trueOrFalse=0;

		return;
	}
	if(node->num==1){
		printf("Circular dependency %s <- %s dropped\n",pt1,pt2);
		return;
	}
	if(node->num==0){
		node->num=1;
		ri=node->right;
		while(ri!=NULL){
			get(ri->head,ri->head);
			ri=ri->right;
		}
		node->num=2;
		return;
	}
}


void specifyError(char *eachWord){
	if(eachWord==NULL){ 	
			fprintf(stderr,"Missing @cmd\n");	
			freeMemory();	
		}
		free(eachWord);
		if((eachWord=save(inputFile))==NULL){ 	
			fprintf(stderr,"Missing command\n");	
			freeMemory();	
		}
		if(!strcmp(eachWord,"@target")){ 	
			fprintf(stderr,"Missing command\n");	
			free(eachWord);	
			freeMemory();	
		}
		if(*eachWord=='@'){	
			fprintf(stderr,"Illegal eachWord: %s\n",eachWord);	
			free(eachWord);	
			freeMemory();	
		}
		free(eachWord);
}
int checkword(char *f){
	int a=0;
	Node *temp=target;
	while(temp!=NULL && temp->head!=NULL){
		if(!strcmp(temp->head,f)){
			a=1;
		}
		temp=temp->below;
	}
	return a;
}
void freeMemory(){
	if(inputFile!=NULL) fclose(inputFile);
	Node *temp,*t;
	while(target!=NULL){
		temp=target->right;
		while(temp!=NULL){
			t=temp->right;
			if(temp->head!=NULL) free(temp->head);
			free(temp);
			temp=t;
		}
		temp=target->below;
		if(target->head!=NULL){
			free(target->head);
		}
		free(target);
		target=temp;
	}
	exit(1);
}

void final(char *fi, FILE *inputFile){
	if(!checkword(fi)){	
		fprintf(stderr,"Target %s not found\n",fi); 
		freeMemory();
	}
	get(fi,NULL);
	//fclose(inputFile);
	//inputFile=NULL;
}

//int main(int argc, char *argv[])--combined all functions and work together
int main(int argc, char *argv[]){
	char *eachWord, *words=NULL,*reads,*copywords,*save1,*ch2=NULL,*reads2=malloc(165), *copywords1,*save2;
	size_t size=65, size1=65;
	int count=0, turn=0, count1=0,turn1=0,count2=0, count3=0, num,count4=0, count5=0;
	// check error
	inputFile=fopen(argv[1],"r");
	inputFile2=fopen(argv[1],"r");
	
	dir=opendir(".");
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
		while((read=readdir(dir))!=NULL){
			if(strcmp(read->d_name,".")==0 || strcmp(read->d_name,"..")==0){
			}else{
				//printf("%s\n",read->d_name);
				currentfiles(read->d_name);
			}
		}
		final(argv[2], inputFile);
		if(terminate==1){
			return 1;
		}
		while(getline(&words,&size,inputFile2)!=EOF){
			reads=strtok(words," \n");
			while(reads!=NULL){
				if(strcmp(reads,"@target")==0){
					if(count==1){
						save1='\0';
					}
					turn=1;
					count=0;
				}else if(turn==1){
					if(strcmp(argv[2],reads)==0){
						turn=2;
					}else{
						turn=0;
					}
				}else if(strcmp(reads,"@cmd")==0){
					count=1;
				}else if(strcmp(reads,":")==0){
					count2=1;
				}else if(count2==1 && turn==2 && count!=1){
					inputFile3=fopen(argv[1],"r");
					//printf("%s\n", reads);
					count3=0,count4=0;
					while(getline(&ch2,&size1,inputFile3)!=EOF){
						while(sscanf(ch2,"%s%n",reads2,&num)==2){
							if(strcmp(reads2,"@target")==0){
								count5=1;
								if(count3==2){
								*save2='\0';
								//printf("here\n");
								printf("%s\n", copywords1);
								system(copywords1);
								count3=0;
								break;
								}
								
							}else if(count5==1){
								if(strcmp(reads2,reads)==0){
								count3=1;
								}else{
									count5=0;
								}
							}else if(count3==1 && strcmp(reads2,"@cmd")==0){
								//printf("here\n");
								count3=2;
							}else if(count3==2){
								
								if(count4==0){
								save2=malloc(195*sizeof(char));
								copywords1=save2;
								count4++;
								}
								while(*reads2!='\0'){
									*save2=*reads2;
									save2++;
									reads2++;
								}
								*save2=' ';
								save2++;
							}
							ch2=ch2+num;
						}
					}
					//printf("here\n");
					

				}else if(count==1 && turn==2){
					
					count1=1;
					if(turn1==0){
						save1=malloc(65*sizeof(char));
						copywords=save1;
						turn1++;
					}
					//reads=strtok(words,"\n");
					while(*reads!='\0'){
						*save1=*reads;
						save1++;
						reads++;
					}
					*save1=' ';
					save1++;
				}
					reads=strtok(NULL," \n");
			}
		//	printf("here\n");
		}
		//fclose(inputFile2);
		if(count1==1){
			printf("%s\n", copywords);
			system(copywords);
		}
		//fclose(inputFile3);
		
		fclose(inputFile2);
		fclose(inputFile);
		
	}
	return 0;
}
