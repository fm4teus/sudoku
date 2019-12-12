#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "sudoku.h"
#define MAX_SIZE 9

void print( element matriz[MAX_SIZE][MAX_SIZE] );

void start( element sudoku[MAX_SIZE][MAX_SIZE] , int level);

bool check( element sudoku[MAX_SIZE][MAX_SIZE] );

void update( element sudoku[MAX_SIZE][MAX_SIZE], int i, int j, int input );

void get_highscore( char* buffer, char* name, int time , int level );

int box_number( int i, int j );

void print( element matriz[MAX_SIZE][MAX_SIZE] ){
    int i, j;
    for(i=0; i<MAX_SIZE; i++){
        for(j=0; j<MAX_SIZE; j++){
          if(matriz[i][j].value == 0)
              printf("  ");
          else
            printf("%d ", matriz[i][j].value);
        }
        printf("\n");
    }
    printf("\n");
}

void start( element sudoku[MAX_SIZE][MAX_SIZE] , int level ) {
    int i, j, v[MAX_SIZE*MAX_SIZE], cont = 0;
    char temp;
    FILE *fr;
    switch (level)
    {
    case EASY:
        fr = fopen("files/sdk_easy.txt", "r");
        break;
    case MEDIUM:
        fr = fopen("files/sdk_medium.txt", "r");
        break;
    case HARD:
        fr = fopen("files/sdk_hard.txt", "r");
        break;
    }
    
    if(fr == NULL){
	    printf("Erro ao ler arquivo\n");
	    exit(-1);
    }
    srand(time(0));
    
    fseek(fr, (rand()%15) * (MAX_SIZE*MAX_SIZE + 2) * sizeof(char), SEEK_SET );
    
    for(i=0, j=0; ; i++){
        fscanf(fr, "%c", &temp);
        if( temp >= 48 && temp <= 57 ){
            v[j] = temp - 48;
            j++;
        }
        else if(temp == '.')
            break;
    }
    for(i=0; i<MAX_SIZE; i++){
        for(j=0; j<MAX_SIZE; j++){
            sudoku[i][j].box = false;
            sudoku[i][j].column = false;
            sudoku[i][j].row = false;
            sudoku[i][j].full = false;
            sudoku[i][j].value = v[cont];
            cont++;
            if(sudoku[i][j].value != 0){
              sudoku[i][j].full = true;
              sudoku[i][j].fixed = true;
            }
            else
              sudoku[i][j].fixed = false;
        }
    }
    fclose(fr);
}

bool check( element sudoku[MAX_SIZE][MAX_SIZE] ){
    int i, j;
    for(i=0; i<MAX_SIZE; i++){
        for(j=0; j<MAX_SIZE; j++){
            sudoku[i][j].box = false;
            sudoku[i][j].column = false;
            sudoku[i][j].row = false;
            sudoku[i][j].full = false;

            if(sudoku[i][j].value != 0)
              sudoku[i][j].full = true;
        }
    }
    for(i=0; i<MAX_SIZE; i++){
        for(j=0; j<MAX_SIZE; j++){
            if(sudoku[i][j].full == true){
                sudoku[j][ sudoku[i][j].value - 1 ].column = true;
                sudoku[i][ sudoku[i][j].value - 1 ].row = true;
                sudoku[ box_number(i,j) ][ sudoku[i][j].value - 1].box = true;
            }
        }
    }
    for(i=0; i<MAX_SIZE; i++){
        for(j=0; j<MAX_SIZE; j++){
            if(sudoku[i][j].column == false || sudoku[i][j].row == false || sudoku[i][j].box == false)
                return false;
        }
    }
    return true;
  }

  void update( element sudoku[MAX_SIZE][MAX_SIZE] , int i, int j, int input){
      if(
        i >= 0 && i <= 8 &&
        j >= 0 && j <= 8 &&
        input >= 1 && input <= 9
        && sudoku[i][j].fixed == false){
          if(sudoku[i][j].full == false){
            sudoku[i][j].full = true;
            sudoku[i][j].value = input;
            sudoku[j][input - 1].column = true;
            sudoku[i][input - 1].row = true;
            sudoku[ box_number(i,j) ][ input - 1].box = true;
          }
          else{
            sudoku[j][ sudoku[i][j].value - 1 ].column = false;
            sudoku[i][ sudoku[i][j].value - 1 ].row = false;
            sudoku[ box_number(i,j) ][ sudoku[i][j].value - 1].box = false;
            sudoku[i][j].value = input;
            sudoku[j][input - 1].column = true;
            sudoku[i][input - 1].row = true;
            sudoku[ box_number(i,j) ][ input - 1].box = true;
          }
      }
      else if(sudoku[i][j].fixed == true)
        printf("\n\n---POSIÇÃO NÃO PODE SER ALTERADA---\n\n");
      else
        printf("\n\n---ENTRADA INVALIDA---\n\n");
    }

void get_highscore( char* buffer , char* name, int time , int level ){
    int i = 0, j = 0;

	high_score rank[MAX_RANK], t;

    char file[2*MAX_NAME];
    switch (level)
    {
    case EASY:
        sprintf(file, "files/HS_easy.txt");
        break;
    case MEDIUM:
        sprintf(file, "files/HS_medium.txt");
        break;
    case HARD:
        sprintf(file, "files/HS_hard.txt");
        break;
    }

	FILE *fr;
	fr = fopen( file , "r" );
	if( !fr ){
		printf("Erro ao abrir arquivo!\n ");
		exit(-1);
	}
	for( i=0; i<MAX_RANK; i++){
		fscanf(fr, "%s %d\n", rank[i].name, &rank[i].time);
	}
	fclose(fr);

    // insertion sort na lista de highscores
    if(time < rank[MAX_RANK - 1].time){
        rank[MAX_RANK - 1].time = time;
        strcpy( rank[MAX_RANK - 1].name, name);
        for(i=1; i<MAX_RANK; i++){
		    j=i;
		    while(j > 0 && rank[j-1].time > rank[j].time){
			    t = rank[j];
			    rank[j] = rank[j-1];
			    rank[j-1] = t;
			    j--;	
		    }
	    }
    }

	sprintf( buffer, "%s %d\n%s %d\n%s %d\n%s %d\n%s %d\n%s %d\n%s %d\n%s %d\n%s %d\n%s %d\n",
	rank[0].name, rank[0].time,
	rank[1].name, rank[1].time,
    rank[2].name, rank[2].time,
    rank[3].name, rank[3].time,
    rank[4].name, rank[4].time,
    rank[5].name, rank[5].time,
    rank[6].name, rank[6].time,
    rank[7].name, rank[7].time,
    rank[8].name, rank[8].time,
	rank[9].name, rank[9].time);

	fr = fopen( file, "w");
	if( !fr ){
		printf("Erro ao abrir arquivo!\n ");
		exit(-1);
	}
	fputs(buffer, fr);
	fclose(fr);
}

int box_number(int i, int j){
    return  ( i/3 + j/3 ) + 2 * (i/3);
}
