#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sudoku.h"
#define MAX_SIZE 9

void print( element matriz[MAX_SIZE][MAX_SIZE] );

void start( element sudoku[MAX_SIZE][MAX_SIZE] );

bool check( element sudoku[MAX_SIZE][MAX_SIZE] );

void update( element sudoku[MAX_SIZE][MAX_SIZE], int i, int j, int input );

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

void start( element sudoku[MAX_SIZE][MAX_SIZE] ) {
    int i, j, v[MAX_SIZE*MAX_SIZE], cont = 0;
    char temp;
    FILE *fr;
    fr = fopen("src/test.txt", "r");
    if(fr == NULL){
	    printf("Erro ao ler arquivo\n");
	    exit(-1);
    }
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

int box_number(int i, int j){
    return  ( i/3 + j/3 ) + 2 * (i/3);
}
