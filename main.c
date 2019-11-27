#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"

#define MAX 9


int main(){

    int i, j, flag = 0, input;
    struct element sudoku[MAX][MAX]; 
    start(sudoku);
    flag = check(sudoku);
    print(sudoku);
    
    while (flag != 1) {
      printf("SUDOKU AINDA NAO RESOLVIDO,\n\n");
      update(sudoku);
      flag = check(sudoku);
      print(sudoku);
    }
    printf("SUDOKU RESOLVIDO, PARABENS!\n\n");

    return 0;
}
