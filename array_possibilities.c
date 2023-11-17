#include <stdio.h>

#include "array_possibilities.h"

void giveArrayPossibilities(int** board, int arr[N][N][10])
{
    int i, j, k, digit;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            digit = board[i][j];
            if (digit != 0)
            {
                crossRows(arr, i, j, digit);
                crossColumns(arr, i, j, digit);
                crossSquares(arr, i, j, digit);

                // clearing because in this filed board[i][j] is digit
                for (k = 1; k < 10; k++)
                {
                    arr[i][j][k] = 0;
                }
            }
        }
    }
}

void crossRows(int arr[N][N][10], int i, int j, int digit)
{
    int k;
    for (k = 0; k < N; k++)
        arr[i][k][digit] = 0;
}

void crossColumns(int arr[N][N][10], int i, int j, int digit)
{
    int k;
    for (k = 0; k < N; k++)
        arr[k][j][digit] = 0;
}

void crossSquares(int arr[N][N][10], int i, int j, int digit)
{
    int k;
    for (k = 0; k < N; k++)
        arr[(i / 3) * 3 + k / 3][(j / 3) * 3 + k % 3][digit] = 0;
}

void initializeArrWithOnes(int arr[N][N][10])
{
    int i, j, k;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            for (k = 0; k < 10; k++)
            {
                if (k == 0)
                {
                    arr[i][j][k] = 1;
                    continue;
                }
                arr[i][j][k] = 1;
            }
        }
    }
}
