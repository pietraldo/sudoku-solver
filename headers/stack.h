#ifndef _STACK
#define _STACK
#define W 9
#define C 9

struct node
{
    int** value;
    struct node* next;
} typedef node;

int** copyBoard(int** board);
int addToStack(node** first, int** board);  // return 0 if success, -1 failure
int** deleteLastStack(node** first);
#endif