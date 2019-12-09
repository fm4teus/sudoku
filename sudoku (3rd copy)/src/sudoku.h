#ifndef SUDOKU_H
#define SUDOKU_H

#include <stdbool.h>

#define MAX_SIZE 9
#define MAX_NAME 12
#define MAX_RANK 10

typedef struct{
	char name[MAX_NAME];
	int time;
}high_score;

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

void get_highscore( char* buffer, char* name, int time );

int box_number( int i, int j );

#endif
