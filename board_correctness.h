#ifndef _CORRECTNESS
#define _CORRECTNESS
#define N 9

// returns-> not_correct:0, correct:1, not_complited:2
int check(int** board);
int checkRow(int** board, int num);
int checkColumn(int** board, int num);
int checkSquare(int** board, int num);

#endif