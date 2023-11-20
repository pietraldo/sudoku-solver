#include "../headers/solving.h"
#include <stdio.h>

int writeDigitIfOnePossibility(int** board, int arr[N][N][10])
{
    int i, j, k, first, second, writted = 0;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            first = 0;
            second = 0;
            for (k = 1; k < 10; k++)
            {
                if (arr[i][j][k] == 1)
                {
                    if (first == 0)
                    {
                        first = k;
                    }
                    else
                    {
                        second = k;
                        break;
                    }
                }
            }
            if (first != 0 && second == 0)  // if only one digit had one
            {
                // printf("i:%d j:%d d:%d\n",i,j,first);
                board[i][j] = first;
                writted = 1;
            }
        }
    }
    return writted;
}