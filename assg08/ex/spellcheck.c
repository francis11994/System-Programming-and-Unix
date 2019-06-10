#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
	char *data;
	struct node *next;
}	Node;

Node *getDictionary(FILE *dictionaryFile);
void readInputLine(char *line,Node *dictionary,int isUnique);
void exits();
void toLowercase(char *str);
int hasElement(char *str,Node *node);
char *dictionaryName=NULL,*inputName=NULL;

int main(int argc,char *argv[]){
	//read Command line arguement
	int isUnique=0,i;
	for(i=1;i<argc;i++){
		if(strcmp("-u",argv[i])==0){
			if(isUnique){
				fprintf(stderr,"Error: duplicateargument -u\n");
				exits();
			}
			else isUnique=1;
		}
		else if(strcmp("-d",argv[i])==0){
			++i;
			if(dictionaryName!=NULL){
				fprintf(stderr,"Error: duplicate argument -d\n");
				exits();
			}
			if(argv[i]==NULL){
				fprintf(stderr,"Error: miss dictionary file name\n");
				exits();
			}
			if(*argv[i]=='-'){
				fprintf(stderr,"Error: file name starts with '-': &s\n",argv[i]);
			}
			dictionaryName=strdup(argv[i]);
		}
		else if(strcmp("-i",argv[i])==0){
			++i;
			if(inputName!=NULL){
				fprintf(stderr,"Error: duplicate argument -i\n");
				exits();
			}
			if(argv[i]==NULL){
				fprintf(stderr,"Error: miss input file name\n");
				exits();
			}
			if(*argv[i]=='-'){
				fprintf(stderr,"Error: file name starts with '-': %s\n",argv[i]);
				exits();
			}
			inputName=strdup(argv[i]);
		}
		else{
			fprintf(stderr,"Error: unrecognized argument %s\n",argv[i]);
			exits();
		}
	}
	if(dictionaryName==NULL){
		fprintf(stderr,"Error: No dictionary specified\n");
		exits();
	}
	//open file
	FILE *dictionaryFile=NULL, *inputFile=NULL;
	dictionaryFile=fopen(dictionaryName,"r");
	if(dictionaryFile==NULL){
		fprintf(stderr,"%s: No such file or directory\n",dictionaryName);
		exits();
	}
	free(dictionaryName);
	if(inputName==NULL)			inputFile=stdin;
	else {
		inputFile=fopen(inputName,"r");
		if(dictionaryFile==NULL){
			fprintf(stderr,"%s: No such file or directory\n",inputName);
			exits();
		}
		free(inputName);
	}
	//read dictionary file
	Node *dictionaryList=malloc(sizeof(Node));
	dictionaryList=getDictionary(dictionaryFile);

	//run input file
	char *line=malloc(513);
	
	while(fgets(line,513,inputFile)!=NULL){
		readInputLine(line,dictionaryList,isUnique);
	}

	free(line);
	Node *temp=dictionaryList;
	while(dictionaryList!=NULL){
		temp=dictionaryList->next;
		free(dictionaryList->data);
		free(dictionaryList);
		dictionaryList=temp;
}
	return 0;
}

Node *getDictionary(FILE *dictionaryFile){
	char *line=malloc(65);
	if(line==NULL){fprintf(stderr,"Out of memory"); exit(1);}
	Node *dictionary=NULL,*newNode=NULL;
	while(fgets(line,65,dictionaryFile)!=NULL){
		if(*(line+strlen(line)-1)=='\n')
			*(line+strlen(line)-1)=0;
		toLowercase(line);
		Node *temp=dictionary;
		newNode=malloc(sizeof(Node));
		newNode->data=strdup(line);
		if(newNode==NULL||newNode->data==NULL){	fprintf(stderr,"Out of memory"); exit(1);}
		if(dictionary==NULL)	dictionary=newNode;
		else {	while(temp->next!=NULL)		temp=temp->next;	temp->next=newNode;		}	
	}
	free(line);
	return dictionary;
}

void readInputLine(char *line, Node *dictionary,int isUnique){
	int i=0;
	char *word=NULL;
	toLowercase(line);
	word=strtok(line," ");
	while(word!=NULL){
		if(hasElement(word,dictionary)!=1){	
			printf("%s\n", word);
			if(isUnique){
				Node *temp=dictionary,*newNode=malloc(sizeof(Node));
				newNode->data=strdup(word);
				if(newNode==NULL||newNode->data==NULL){	fprintf(stderr,"Out of memory"); exit(1);}
				if(dictionary==NULL)	dictionary=newNode;
				else{while(temp->next!=NULL) temp=temp->next;	temp->next=newNode;
				}
			}
		}
		word=strtok(NULL," ");
	}
}

void toLowercase(char *str){
	while(*str!=0){
		if(*str>='A'&&*str<='Z')	*str=*str-'A'+'a';
		if(*str>'z'||*str<'a')		*str=' ';
		++str;
	}
}

int hasElement(char *str,Node *node){
	int i=0;
	while(node!=NULL){
		if(strcmp(str,node->data)==0)
			i=1;
		node=node->next;
	}
	return i;
}

void exits(){
	if(dictionaryName!=NULL)
		free(dictionaryName);
	if(inputName!=NULL)
		free(inputName);
	exit(1);
}