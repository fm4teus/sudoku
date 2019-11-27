#include <stdio.h>
#include "sudoku.h"
#define MAX 9

void print( struct element matriz[MAX][MAX] );

void start( struct element sudoku[MAX][MAX] );

int check( struct element sudoku[MAX][MAX] );

void update( struct element sudoku[MAX][MAX] );

void print( struct element matriz[MAX][MAX] ){
    int i, j;
    for(i=0; i<MAX; i++){
        for(j=0; j<MAX; j++){
          if(matriz[i][j].value == 0)
              printf("  ");
          else
            printf("%d ", matriz[i][j].value);
        }
        printf("\n");
    }
    printf("\n");
}

void start( struct element sudoku[MAX][MAX] ) {
    int i, j, v[MAX*MAX], cont = 0;
    char temp;
    FILE *fr;
    fr = fopen("sudoku.txt", "r");
    for(i=0, j=0; ; i++){
        fscanf(fr, "%c", &temp);
        if( temp >= 48 && temp <= 57 ){
            v[j] = temp - 48;
            j++;
        }
        else if(temp == '.')
            break;
    }
    for(i=0; i<MAX; i++){
        for(j=0; j<MAX; j++){
            sudoku[i][j].box = 0;
            sudoku[i][j].column = 0;
            sudoku[i][j].row = 0;
            sudoku[i][j].full = 0;
            sudoku[i][j].value = v[cont];
            cont++;
            if(sudoku[i][j].value != 0){
              sudoku[i][j].full = 1;
              sudoku[i][j].fixed = 1;
            }
            else
              sudoku[i][j].fixed = 0;
        }
    }
    fclose(fr);
}

int check( struct element sudoku[MAX][MAX] ){
    int i, j;
    for(i=0; i<MAX; i++){
        for(j=0; j<MAX; j++){
            sudoku[i][j].box = 0;
            sudoku[i][j].column = 0;
            sudoku[i][j].row = 0;
            sudoku[i][j].full = 0;

            if(sudoku[i][j].value != 0)
              sudoku[i][j].full = 1;
        }
    }
    for(i=0; i<MAX; i++){
        for(j=0; j<MAX; j++){
            if(sudoku[i][j].full != 0){
                sudoku[j][ sudoku[i][j].value - 1 ].column = 1;
                sudoku[i][ sudoku[i][j].value - 1 ].row = 1;
                sudoku[( i/3 + j/3 ) + 2 * (i/3) ][ sudoku[i][j].value - 1].box = 1;
            }
        }
    }
    for(i=0; i<MAX; i++){
        for(j=0; j<MAX; j++){
            if(sudoku[i][j].column == 0 || sudoku[i][j].row == 0 || sudoku[i][j].box == 0)
                return 0;
        }
    }
    return 1;
  }

  void update( struct element sudoku[MAX][MAX] ){
      int i, j, input;
      printf("Insira uma posicao: ");
      scanf("%d %d", &i, &j);
      printf("Insira um valor: ");
      scanf("%d", &input);
      printf("\n");
      i--;
      j--;
      if(
        i >= 0 && i <= 8 &&
        j >= 0 && j <= 8 &&
        input >= 1 && input <= 9){
          if(sudoku[i][j].full == 0){
            sudoku[i][j].full = 1;
            sudoku[i][j].value = input;
            sudoku[j][input - 1].column = 1;
            sudoku[i][input - 1].row = 1;
            sudoku[( i/3 + j/3 ) + 2 * (i/3) ][ input - 1].box = 1;
          }
          else{
            sudoku[j][ sudoku[i][j].value - 1 ].column = 0;
            sudoku[i][ sudoku[i][j].value - 1 ].row = 0;
            sudoku[( i/3 + j/3 ) + 2 * (i/3) ][ sudoku[i][j].value - 1].box = 0;
            sudoku[i][j].value = input;
            sudoku[j][input - 1].column = 1;
            sudoku[i][input - 1].row = 1;
            sudoku[( i/3 + j/3 ) + 2 * (i/3) ][ input - 1].box = 1;
          }
      }
      else
        printf("\n\n---ENTRADA INVALIDA---\n\n");
    }
