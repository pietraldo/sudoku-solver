#include "../headers/stack.h"
#include <stdio.h>
#include <stdlib.h>

int** copyBoard(int** board)
{
    int i, j;
    int** copy = (int**)malloc((sizeof(int*) * W));
    if (copy == NULL)
        return NULL;
    for (i = 0; i < C; i++)
    {
        copy[i] = (int*)malloc(sizeof(int) * C);
        if (copy[i] == NULL)
            return NULL;
    }

    for (i = 0; i < W; i++)
    {
        for (j = 0; j < C; j++)
        {
            copy[i][j] = board[i][j];
        }
    }

    return copy;
}

int addToStack(node** first, int** board)
{
    node* p = malloc(sizeof(node));
    if (p == NULL)
        return -1;
    p->next = *first;
    *first = p;
    p->value = board;
    return 0;
}
int** deleteLastStack(node** first)
{
    if (*first == NULL)
        return NULL;
    int** value = (*first)->value;

    node* deleted = (*first);
    *first = (*first)->next;
    free(deleted);

    return value;
}