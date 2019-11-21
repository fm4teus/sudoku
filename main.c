#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"

#define MAX 9

int main(){

    int i, j, flag = 0, input, sudoku[MAX][MAX],
    row[MAX][MAX], column[MAX][MAX],
    box[MAX][MAX], full[MAX][MAX];

    start(sudoku, row, column, box, full);
    flag = check(sudoku, row, column, box, full);
    print(sudoku);
    while (flag != 1) {
      printf("SUDOKU AINDA NAO RESOLVIDO,\n\n");
      update(sudoku, row, column, box, full);
      flag = check(sudoku, row, column, box, full);
      print(sudoku);
    }
    printf("SUDOKU RESOLVIDO, PARABENS!\n\n");

    return 0;
}
