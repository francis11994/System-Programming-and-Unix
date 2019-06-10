/*
* File: battleship.c
* Author: Francis Kim
* Purpose: play the battleship game which is a guessing game where two players take turns trying to guess the locations where their opponent has placed a set of "ships" on a 10x10 grid
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// convert(num, length) -- this is convert our input from characters to integer. length is length of our input and num is ASCII number.
int convert(int num, int length){
	int a;
	int empty = num - 48;
	if(empty <= 9 && empty >= 0){
	for(a = length; a >= 1; a--){
		if(a == 1){
			empty = empty*1;
		}
		if(a >= 2){
			empty = empty*10;
		}
	}
	}else{
		empty = 0;
	}
	return empty;
}
/* setBoard(board, x1, y1, x2, y2, ship, whatShip[], whatShip1[10][10]) -- this function set up the initial board that we input each ship location, and also check the
*  error catches. In addition, it gives own board for each ship.
*/
int setBoard(int board[10][10], int x1, int y1, int x2, int y2, int ship, char whatShip[], int whatShip1[10][10]){

	int start;
	
	if(((x2-x1)+1)==ship || ((x1-x2)+1)==ship){
		if(x1>x2){
			for(start=x1; start >= x2; start--){
				if(board[9-y1][start] == 1){
					fprintf(stderr, "Illegal placement [%s %d %d %d %d]: overlap at (%d, %d)\n", whatShip, x1, y1, x2, y2, start, 9-(9-y1));	
					return 1;
				}
				board[9-y1][start]=1;
				whatShip1[9-y1][start]=1;
			}
		}else if(x2>x1){
			for(start=x2; start >= x1; start--){
				if(board[9-y1][start] == 1){
					fprintf(stderr, "Illegal placement [%s %d %d %d %d]: overlap at (%d, %d)\n", whatShip, x1, y1, x2, y2, start, 9-(9-y1));
					return 1;
				}
				board[9-y1][start]=1;
				whatShip1[9-y1][start]=1;
			}
		}
	}else if(((y2-y1)+1)==ship || ((y1-y2)+1)==ship){
		if(y1>y2){
			for(start=y1; start >= y2; start--){
				if(board[9-start][x1] == 1){
					fprintf(stderr, "Illegal placement [%s %d %d %d %d]: overlap at(%d, %d)\n", whatShip, x1, y1, x2, y2, start, 9-(9-start));
					return 1;
				}
				board[9-start][x1]=1;
				whatShip1[9-start][x1]=1;
			}
		}else if(y2>y1){
			for(start=y2; start >= y1; start--){
				if(board[9-start][x1] == 1){
					fprintf(stderr, "Illegal placement [%s %d %d %d %d]: overlap at (%d, %d)\n", whatShip, x1, y1, x2, y2, start, 9-(9-start));
					return 1;
				}
				board[9-start][x1]=1;
				whatShip1[9-start][x1]=1;
			}
		}
	}else{
		if(y1 == y2){
		fprintf(stderr, "Illegal placement: Incorrect length %d for shiptype = %s\n", abs(x1-x2)+1, whatShip);
		}
		if(x1 == x2){
		fprintf(stderr, "Illegal placement: Incorrect length %d for shiptype = %s\n", abs(y1-y2)+1, whatShip);
		}
		return 1;
	}
	return 0;
}

// main() -- This is my main function to start battleship game. Determine location of each ships and manipulate each ship's statement such as hit, miss, sunk, etc.

int main(){

	int board[10][10] = {{0}, {0}};
	int shipAA[10][10] = {{0}, {0}};
	int shipBB[10][10] = {{0}, {0}};
	int shipDD[10][10] = {{0}, {0}};
	int shipPP[10][10] = {{0}, {0}};
	int shipSS[10][10] = {{0}, {0}};
	int status, selectShip, add, count=0, prepareToStart=1;
	int x1=0,y1=0,x2=0,y2=0;
	int play=0;
	int shipA=5, shipB=4, shipD=3, shipP=2, shipS=3, A=0, B=0, D=0, P=0, S=0, finish=6;
	char input[1025];
	int a, length, error=0, set1 = 5;	
	int point, c, x3=0, y3=0, length1, times=0, Aship=5, Bship=4, Dship=3, Pship=2, set=0, Sship=3; // for count == 2
	char alpha[1]="A", alpha1[1]="B", alpha2[1]="D", alpha3[1]="P", alpha4[1]="S";
	while((status = scanf("%s", input) != EOF)){
	length = strlen(input);
	if(count == 0){		
		for(a=0; input[a] != '\0'; a++){
			
			if(prepareToStart >= 2){	
				if((input[a] < 48 || input[a] > 57) && input[a] != 45){		
					fprintf(stderr, "Input error: not enough values(read %d values out of 5)\n", error);
					return 1;
				}
			}	
			if(prepareToStart == 1){	
	
				if(input[0] == 65){
					selectShip = 3; //shipA
				}else if(input[0] == 66){
					selectShip = 4; //shipB
				}else if(input[0] == 68){
					selectShip = 5; //shipD
				}else if(input[0] == 80){
					selectShip = 6; //shipP
				}else if(input[0] == 83){
					selectShip = 7; //shipS
				}else{
					if(length == 1){
						fprintf(stderr, "ERROR: Unrecognized ship type %c \n", input[0]);
						return 1;
					}
					if(input[0] < 48 || input[0] > 57){
						error++;
						set1 = 6;
						prepareToStart++;
					}
					if(set1 == 5){
					fprintf(stderr, "Input error: not enough values(read %d values out of 5)\n", error);
					return 1;
					}
				}
				if(a>=1){
				prepareToStart++;
				}
			}
			if(prepareToStart == 2){
				add = convert(input[a], length);
				x1 = x1 + add;
			}
			if(prepareToStart == 3){
				add = convert(input[a], length);
				y1 = y1 + add;
			}
			if(prepareToStart == 4){
				add = convert(input[a], length);
				x2 = x2 + add;
			}
			if(prepareToStart == 5){
				add = convert(input[a], length);
				y2 = y2 + add;
			}
			length--;	
		}
			if(input[0] == 45){
				if(prepareToStart == 2){
					x1 = x1*-1;
				}else if(prepareToStart == 3){
					y1 = y1*-1;
				}else if(prepareToStart == 4){
					x2 = x2*-1;
				}else if(prepareToStart == 5){
					y2 = y2*-1;
				}
			}
		error++;
		prepareToStart++;
		if(prepareToStart >= 6){
			count = 1;
		}
	}
	if(count == 1){
		if((x1>9 || x1<0) || (y1>9 || y1<0) || (x2>9 || x2<0) || (y2>9 || y2<0) || (selectShip == 8) || ((y1 != y2) && (x1 != x2))){
			if(set1 == 6){
				x1 = x1*-1;
			}	
			printf("Illegal placement: invalid coordinates: (%d, %d), (%d, %d)\n", x1, y1, x2, y2);
			return 1;
		}
		
			if(selectShip == 3){ //shipA
				A++;
				if(setBoard(board, x1, y1, x2, y2, shipA, "A", shipAA)==1){
					return 1;
				}
			}else if(selectShip == 4){ //shipB
				B++;
				if(setBoard(board, x1, y1, x2, y2, shipB, "B", shipBB)==1){
					return 1;
				}
			}else if(selectShip == 5){ //shipD
				D++;
				if(setBoard(board, x1, y1, x2, y2, shipD, "D", shipDD)==1){
					return 1;
				}
			}else if(selectShip == 6){ //shipP
				P++;
				if(setBoard(board, x1, y1, x2, y2, shipP, "P", shipPP)==1){
					return 1;
				}
			}else if(selectShip == 7){ //shipS
				S++;
				if(setBoard(board, x1, y1, x2, y2, shipS, "S", shipSS)==1){
					return 1;
				}
			}
			if(play <= 4){
				count = 0;
				prepareToStart = 1;
				error = 0;
				x1=0,y1=0,x2=0,y2=0;
				play++;
			}
			if(play == 5){
				count = 2;
			}
			if(count == 2){
				if(A==0 || B==0 || D==0 || P==0 || S==0){
					fprintf(stderr, "Error: not all ship types placed\n");
					return 1;
				}
			}
	}else if(count == 2){
		length1 = strlen(input);		
			for(c=0; input[c] != '\0'; c++){
				if((input[c] < 48 || input[c] > 57) && input[c] != 45){
					fprintf(stderr, "error: illegal input character(s)\n");
					return 1;
				}
				point = convert(input[c], length1);
				if(times==0){
					x3 = x3 + point;
				}
				if(times==1){
					y3 = y3 + point;
				}	
				length1--;
			}
			if(input[0] == 45){
				if(times==0){
					x3 = x3*-1;
				}
				if(times==1){
					y3 = y3*-1;
				}
			}	
		times++;
		if(times==2){
			if(x3 > 9 || y3 > 9){
				fprintf(stderr, "error: illegal guess\n");
			}else if(x3 < 0 || y3 < 0){
				fprintf(stderr, "error: illegal guess (%d, %d)\n", x3, y3);
				return 1;
			}else if(shipAA[9-y3][x3]==1){
				if(board[9-y3][x3] == 1){
					if(Aship > 0){
						Aship--;
					}
					if(Aship==0){
						printf("%c sunk\n", alpha[Aship]);
						set = 1;
					}	 
				}
				if(set == 0){
					printf("hit\n");
				}
				board[9-y3][x3]=0;
			}else if(shipBB[9-y3][x3]==1){
				if(board[9-y3][x3] == 1){
					if(Bship > 0){
						Bship--;
					}
					if(Bship == 0){
						printf("%c sunk\n", alpha1[Bship]);
						set = 1;
					}
				}
				if(set == 0){
					printf("hit\n");
				}
				board[9-y3][x3]=0;
				
			}else if(shipDD[9-y3][x3]==1){
				if(board[9-y3][x3] == 1){
					if(Dship > 0){
						Dship--;
					}
					if(Dship == 0){
						printf("%c sunk\n", alpha2[Dship]);
						set = 1;
					}
				}
				if(set == 0){
					printf("hit\n");
				}
				board[9-y3][x3]=0;
			}else if(shipPP[9-y3][x3]==1){
				if(board[9-y3][x3]==1){
					if(Pship > 0){
						Pship--;
					}
					if(Pship == 0){
						printf("%c sunk\n", alpha3[Pship]);
						set = 1;
					}
				}
				if(set == 0){
					printf("hit\n");
				}
				board[9-y3][x3]=0;
			}else if(shipSS[9-y3][x3]==1){
				if(board[9-y3][x3]==1){
					if(Sship > 0){
						Sship--;
					}
					if(Sship == 0){
						printf("%c sunk\n", alpha4[Sship]);
						set = 1;
					}
				}
				if(set == 0){
					printf("hit\n");
				}
				board[9-y3][x3]=0;
			}else{
				printf("miss\n");
			}
			set = 0;
		 	times = 0;
			x3 = 0, y3 = 0;
		}	
		if(Aship==0 && Bship==0 && Dship==0 && Pship==0 && Sship==0){
			finish = 5;
			printf("all ships sunk: game over\n");
			return 0;
		}	
	}
		
	}
	if(finish != 5){
		error = -1;
		fprintf(stderr, "Input error: not enough value (read values %d out of 5)\n", error);
	}
	return 0;
}
