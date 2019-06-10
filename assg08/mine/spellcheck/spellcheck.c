/*
  *Author: Francis Kim
  *File: spellcheck.c
  *Purpose: test command-line arguments and file I/O.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static int dashD=0;
static int dashI=0;
static int dashU=0;
static int count=0;
static int count1=0;
static int check=0;
static int open=0;
static int order=0;
static int num1 = 0;
static int s=0;
static int filecount=0;
typedef struct s{
	char *str;
	struct s *next;
} node;

//int error(char *original) -- check the error of command line
int error(char *original){
	char *copy;
	
	copy = original;
	if(strcmp(copy, "-d")==0 && count1==0){
		dashD++, count1++;
		order=1;
		
		if(dashD>1 && check==0){
			fprintf(stderr,"duplicate arguments: (-d)\n");
			check++;
		}
		return 0;
	}else if(strcmp(copy, "-i")==0 && count1==0){
		dashI++, count1++;
		order=2;
		if(dashI>1 && check==0){
			fprintf(stderr,"duplicate arguments: (-i)\n");
			check++;
		}
		return 0;
	}else if(strcmp(copy, "-u")==0 && count1 != 1){
		dashU++;
		num1=1;
		if(dashU>1 && check==0){
			fprintf(stderr,"duplicate arguments: (-u)\n");
			check++;
		}
		return 0;
	}else if(((strcmp(copy, "-d")!=0 || strcmp(copy, "-i")!=0) && *copy == '-' && count==0 && check==0)|| (filecount>=2)){
		if(strcmp(copy, "-u")!=0){
		fprintf(stderr, "Unrecognized argument %s\n", copy);
		check++;
		}
		if(filecount >=2){
			s=1;
		}
		return 1;
	}else if((dashD==1 || dashI==1) && *copy=='-' && count==1 && check==0){
		fprintf(stderr, "Error: file name starts with '-': %s\n", copy);
		check++;
		return 1;
	}else{
		count1=0;
		count=0;
		open=1;
		filecount++;
	}
	return 1;
}
//char *changeCapital(char *original) -- change to Capital and make space when we meet charater out of a to z
char *changeCapital(char *original){
	char *copy, *real;
	copy = original;
	real = copy;
	while(*copy != '\0'){
		if(*copy >= 'A' && *copy <= 'Z'){
			*copy = *copy + 32; 
		}
		if(*copy<'a' || *copy>'z'){
			*copy=' ';
		}
		copy++;
	}
	
	return real;
}
//int findWord(char *str, node *check1) -- find a word that we input in the dictionary
int findWord(char *str, node *check1){
	int i=0;
	while(check1!=NULL){
		if(strcmp(str,check1->str)==0){
			i=1;
		}
		check1=check1->next;
	}
	return i;
}
//void freeN(node *freeNode, node *realStack) -- free the stack
void freeN(node *freeNode, node *realStack){
	while(realStack!=NULL){
		freeNode=realStack->next;
		free(realStack->str);
		free(realStack);
		realStack=freeNode;
	}
}

//int main(int argc, char *argv[]) -- read all input and operate all system
int main(int argc, char *argv[]){

	int i, num=0, save=0;
	node *realStack, *temp=NULL, *newNode=NULL, *temp1, *diction=NULL, *copyStack;
	size_t size=65, size1=513;
	char *c, *file, *read=NULL, *file2, *ch=NULL, *buffer=NULL, *change1="f", *change2="c";
	FILE *fp1,*fp2;
	for(i=1; i<argc; i++){
		if(error(argv[i])){
			if(open==1 && (dashD==1||dashI==1) && num==0){
				
				if(order == 1){
				fp1=fopen(argv[i], "r");
				file=argv[i];
				open=0;
				order=3;
				}else if(order == 2){
				fp2=fopen(argv[i], "r");
				file2=argv[i]; 
				open=0;
				order=3;
				}
			}else{
				if(s==1 || check >=1){
					return 1;
				}
			}
		}else{
			c=argv[i];
			count++;
			if(check==1){
				return 1;
			}
		}
	}
	
	if(count1==1 && check==0){
		fprintf(stderr, "no file provided %s\n", c);
		return 1;
	}else if(dashD == 0 && check==0){
		fprintf(stderr, "Error: No dictionary specified\n");
		return 1;
	}else if(fp1==NULL && check==0){
		fprintf(stderr, "%s: no such file or directory\n", file);
		return 1;
	}else if(fp2==NULL && check==0){
		fprintf(stderr, "%s: no such file or directory\n", file2);
		return 1;
	}
	//size = 65
	while(getline(&ch, &size, fp1) != EOF){	
		if(*(ch+strlen(ch)-1)=='\n'){
			*(ch+strlen(ch)-1)=0;
		}
		
		change1 = changeCapital(ch);
		
		newNode=malloc(sizeof(node));
		newNode->str=strdup(change1);
		if(newNode==NULL||newNode->str==NULL){
			fprintf(stderr, "Out of memory");
			exit(1);
		}
		if(diction==NULL){
			diction=newNode;
			temp=newNode;
			newNode->next = NULL;
		}else if(temp->next==NULL){
			temp->next = newNode;
			temp = newNode;
			newNode->next = NULL;
		}
	}	
	realStack = diction;
	copyStack = realStack;
	if(dashI==0){
		fp2 = stdin;
	}
	if(dashI==1 || dashI==0){
		//size1 = 513
		while(getline(&buffer, &size1, fp2) != EOF){
			change2 = changeCapital(buffer);
			read = strtok(change2, " ");
			while(read!=NULL){
				if(findWord(read,copyStack)!=1){
				printf("%s\n", read);
					if(num1){
						node *temp1=copyStack;
						node *newNode1=malloc(sizeof(node));
						newNode1->str=strdup(read);
						while(temp1->next != NULL){
							if(newNode1->str == temp1->str){
								save=1;
							}
							temp1 = temp1->next;
						}
						if(save==0){
						temp1->next=newNode1;
						newNode1->next=NULL;
						}
						save=0;
					}
				}
				read=strtok(NULL," ");
			}
		}
	}
	node *freeNode=realStack;
	freeN(freeNode, realStack);
	return 0;
}
