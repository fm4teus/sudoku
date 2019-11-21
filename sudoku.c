#include <stdio.h>
#include "sudoku.h"
#define MAX 9

void print( int matriz[MAX][MAX] );

void start(
  int sudoku[MAX][MAX], int row[MAX][MAX],
  int column[MAX][MAX], int box[MAX][MAX],
  int full[MAX][MAX]);

int check(
  int sudoku[MAX][MAX], int row[MAX][MAX],
  int column[MAX][MAX], int box[MAX][MAX],
  int full[MAX][MAX]);

void update(
  int sudoku[MAX][MAX], int row[MAX][MAX],
  int column[MAX][MAX], int box[MAX][MAX],
  int full[MAX][MAX]);

void print( int matriz[MAX][MAX] ){
    int i, j;
    for(i=0; i<MAX; i++){
        for(j=0; j<MAX; j++){
          if(matriz[i][j] == 0)
              printf("  ");
          else
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void start(
  int sudoku[MAX][MAX], int row[MAX][MAX],
  int column[MAX][MAX], int box[MAX][MAX],
  int full[MAX][MAX]) {
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
            box[i][j] = 0;
            column[i][j] = 0;
            row[i][j] = 0;
            full[i][j] = 0;
            sudoku[i][j] = v[cont];
            cont++;
            if(sudoku[i][j] != 0)
              full[i][j] = 1;
        }
    }


    fclose(fr);
}

int check(
  int sudoku[MAX][MAX], int row[MAX][MAX],
  int column[MAX][MAX], int box[MAX][MAX],
  int full[MAX][MAX]){
    int i, j;
    for(i=0; i<MAX; i++){
        for(j=0; j<MAX; j++){
            box[i][j] = 0;
            column[i][j] = 0;
            row[i][j] = 0;
            full[i][j] = 0;

            if(sudoku[i][j] != 0)
              full[i][j] = 1;
        }
    }
    for(i=0; i<MAX; i++){
        for(j=0; j<MAX; j++){
            if(full[i][j] != 0){
                column[j][ sudoku[i][j] - 1 ] = 1;
                row[i][ sudoku[i][j] - 1 ] = 1;
                box[( i/3 + j/3 ) + 2 * (i/3) ][ sudoku[i][j] - 1] = 1;
            }
        }
    }
    for(i=0; i<MAX; i++){
        for(j=0; j<MAX; j++){
            if(column[i][j] == 0 || row[i][j] == 0 || box[i][j] == 0)
                return 0;
        }
    }
    return 1;
  }

  void update(
    int sudoku[MAX][MAX], int row[MAX][MAX],
    int column[MAX][MAX], int box[MAX][MAX],
    int full[MAX][MAX]){
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
          if(full[i][j] == 0){
            full[i][j] = 1;
            sudoku[i][j] = input;
            column[j][input - 1] = 1;
            row[i][input - 1] = 1;
            box[( i/3 + j/3 ) + 2 * (i/3) ][ input - 1] = 1;
          }
          else{
            column[j][ sudoku[i][j] - 1 ] = 0;
            row[i][ sudoku[i][j] - 1 ] = 0;
            box[( i/3 + j/3 ) + 2 * (i/3) ][ sudoku[i][j] - 1] = 0;
            sudoku[i][j] = input;
            column[j][input - 1] = 1;
            row[i][input - 1] = 1;
            box[( i/3 + j/3 ) + 2 * (i/3) ][ input - 1] = 1;
          }
      }
      else
        printf("\n\n---ENTRADA INVALIDA---\n\n");
    }
