#ifndef SUDOKU_H
#define SUDOKU_H

#include <stdbool.h>

#define MAX_SIZE 9
#define MAX_NAME 11
#define MAX_RANK 10
#define EASY 0
#define MEDIUM 1
#define HARD 2
#define MAX_GAMES 15

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

void start( element sudoku[MAX_SIZE][MAX_SIZE] , int level);

bool check( element sudoku[MAX_SIZE][MAX_SIZE] );

void update( element sudoku[MAX_SIZE][MAX_SIZE], int i, int j, int input );

void get_highscore( char* buffer, char* name, int time , int level );

int box_number( int i, int j );

#endif
