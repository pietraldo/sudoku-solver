#include <stdio.h>

#include "board_correctness.h"

int checkRow(int** board, int num)
{
    int digits[10] = {0}, i, index;

    for (i = 0; i < N; i++)
    {
        index = board[num][i];
        if (index != 0 && digits[index] == 1)
            return 0;
        digits[index] = 1;
    }

    for (i = 1; i < N; i++)
    {
        if (digits[i] != 1)
            return 2;
    }
    return 1;
}
int checkColumn(int** board, int num)
{
    int digits[10] = {0}, i, index;

    for (i = 0; i < N; i++)
    {
        index = board[i][num];
        if (index != 0 && digits[index] == 1)
            return 0;
        digits[index] = 1;
    }

    for (i = 1; i < N; i++)
    {
        if (digits[i] != 1)
            return 2;
    }
    return 1;
}
int checkSquare(int** board, int num)
{
    int digits[10] = {0}, i, index;

    for (i = 0; i < N; i++)
    {
        index = board[(num / 3) * 3 + i / 3][(num % 3) * 3 + i % 3];
        if (index != 0 && digits[index] == 1)
            return 0;
        digits[index] = 1;
    }

    for (i = 1; i < N; i++)
    {
        if (digits[i] != 1)
            return 2;
    }
    return 1;
}
int check(int** board)
{
    int ans = 1, ans_row, ans_col, ans_sq, i;
    for (i = 0; i < N; i++)
    {
        ans_row = checkRow(board, i);
        ans_col = checkColumn(board, i);
        ans_sq = checkSquare(board, i);

        if (ans_row == 0 || ans_col == 0 || ans_sq == 0)
            return 0;
        if (ans_row == 2 || ans_col == 2 || ans_sq == 2)
            ans = 2;
    }
    return ans;
}