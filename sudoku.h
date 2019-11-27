#ifndef SUDOKU_H
#define SUDOKU_H
#define MAX 9

struct element{
  int value;
  int row;
  int column;
  int box;
  int full;
  int fixed;
};

void print( struct element matriz[MAX][MAX] );

void start( struct element sudoku[MAX][MAX] );

int check( struct element sudoku[MAX][MAX] );

void update( struct element sudoku[MAX][MAX] );

#endif
