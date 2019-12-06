#ifndef SUDOKU_H
#define SUDOKU_H
#define MAX_SIZE 9

struct element{
  int value;
  int row;
  int column;
  int box;
  int full;
  int fixed;
};

void print( struct element matriz[MAX_SIZE][MAX_SIZE] );

void start( struct element sudoku[MAX_SIZE][MAX_SIZE] );

int check( struct element sudoku[MAX_SIZE][MAX_SIZE] );

void update( struct element sudoku[MAX_SIZE][MAX_SIZE] );

#endif
