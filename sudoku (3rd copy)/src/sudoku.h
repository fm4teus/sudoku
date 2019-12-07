#ifndef SUDOKU_H
#define SUDOKU_H
#define MAX_SIZE 9

#include <stdbool.h>

typedef struct{
  int value;
  bool row;
  bool column;
  bool box;
  bool full;
  bool fixed;
}element;

void print( element matriz[MAX_SIZE][MAX_SIZE] );

void start( element sudoku[MAX_SIZE][MAX_SIZE] );

bool check( element sudoku[MAX_SIZE][MAX_SIZE] );

void update( element sudoku[MAX_SIZE][MAX_SIZE], int i, int j, int input );

#endif
