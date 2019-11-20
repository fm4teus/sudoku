#ifndef SUDOKU_H
#define SUDOKU_H
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

#endif
