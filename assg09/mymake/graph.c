/*
  Author: Francis Kim
  File: graph.c
  Purpose: Functions working in famrel.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mymake.h"

FILE *inputFile = NULL;
Node *target = NULL;
Node *copyTarget = NULL;
int error1 = 0;

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

void searchTarget(char *eachWord){
	if(strcmp(eachWord,"@target")){
		fprintf(stderr,"Missing @target\n"); 
		free(eachWord);	
		if(error1==2){
			
		}
		freeMemory();	
		
	}
}
void below(char *b){
	if(error1==1){
		fprintf(stderr, "Failed to add target%s\n", b);
	}
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
	if(error1==1){
		fprintf(stderr, "Failed to add target\n");
	}
	Node *newNode=malloc(sizeof(Node)),*next=target;
	newNode->num=0, newNode->head=strdup(r);
/*	if(error1==1){
		Node *node=malloc(65);
		node=NULL;
		node->right=target;
		target=node;
	}*/
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
			if(error1==1){
				fprintf(stderr, "Failed to add target\n");
			}
		}
		else{/*
			if(error1==1){
				Node *node=malloc(65);
				node=node->right;
				node=NULL;
				target=node;
			}*/
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
	if(error1==1){
		node=node->right;
		node=NULL;
		target=node;
	}
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
	if(error1==1){
		fprintf(stderr, "Failed to add target\n");
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
		printf("%s\n",pt1);
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
		printf("%s\n",node->head);
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
		}/*
		if(*eachWord=='@'){	
			fprintf(stderr,"Illegal eachWord: %s\n",eachWord);	
			free(eachWord);	
			freeMemory();	
		}*/
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
	fclose(inputFile);
	inputFile=NULL;
	
}