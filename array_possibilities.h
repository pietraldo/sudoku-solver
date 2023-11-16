#ifndef _ARRAY
#define _ARRAY
#define N 9


// gets an array of ones and delete one if there is already 
// this digit in row, square or column
void giveArrayPossibilities(int** board, int arr[N][N][10]); 
void crossRows(int arr[N][N][10], int i, int j, int digit); 
void crossColumns(int arr[N][N][10], int i, int j, int digit); 
void crossSquares(int arr[N][N][10], int i, int j, int digit); 

void initializeArrWithOnes(int arr[N][N][10]);

#endif