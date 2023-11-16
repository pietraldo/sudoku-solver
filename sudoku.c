#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include "array_possibilities.h"
#include "board_correctness.h"
#include "solving.h"
#include "stack.h"

#define N 9
#define ERR(source) (perror(source), fprintf(stderr, "%s:%d\n", __FILE__, __LINE__), exit(EXIT_FAILURE))

extern char* optarg;
extern int opterr, optind, optopt;

void usage();
void solve(int** board);
void printBoard(int** board);
void printBoard2(int** board);
void freeAlocatedBoard(int** board);
void printBoardOfPossibilities(int arr[N][N][10]);
int** readBoardFromFile(char* file_path);
int** readBoardFromConsole();

int show_all_solutions = 0;
int just_count_how_many_is_solutions=0;

int main(int argc, char* argv[])
{
    int option;
    char* file_path = NULL;
    int** board;

    // reading arguments to program
    while ((option = getopt(argc, argv, "ac")) != -1)
    {
        switch (option)
        {
            case 'a':
                printf("option a\n");
                show_all_solutions = 1;
                break;
            case 'c':
                printf("option c\n");
                just_count_how_many_is_solutions=1;
                break;
            case '?':
                usage();
        }
    }

    // if file name was given => get file name
    if (optind < argc)
    {
        printf("plik: %s\n", argv[optind]);
        file_path = argv[optind];
    }

    // read board
    if (file_path != NULL)
        board=readBoardFromFile(file_path);
    else
        board=readBoardFromConsole();

    printf("Loaded Board: \n");
    printBoard(board);

    // solving sudoku
    printf("\n\nSolved sudoku: \n");
    solve(board);
    
    int arr[N][N][10], i, j, k;
    int ans, ans2;

    /*ans = check(board);
    printf("Checked board: %d\n", ans);

    int** copy = copyBoard(board);
    if (copy == NULL)
        ERR("copying board");

    initializeArrWithOnes(arr);
    giveArrayPossibilities(board, arr);
    // printBoardOfPossibilities(arr);

    while (writeDigitIfOnePossibility(board, arr) == 1)
    {
        initializeArrWithOnes(arr);
        giveArrayPossibilities(board, arr);
    }

    printBoard2(board);
    printBoard2(copy);

    // free memory
    for (i = 0; i < W; i++)
    {
        free(copy[i]);
    }
    free(copy);

    printf("---------------------------------------\n\n");
    
    node* stack = NULL;
    int** copy1 = copyBoard(board);
    int** copy2 = copyBoard(board);
    int** copy3 = copyBoard(board);
    copy1[0][0] = 1;
    copy2[0][0] = 2;
    copy3[0][0] = 3;
    
    addToStack(&stack, copy1);
    addToStack(&stack, copy2);
    addToStack(&stack, copy3);

    int** stackBoard;
    while ((stackBoard = deleteLastStack(&stack)) != NULL)
    {
        printf("\n");
        printBoard2(stackBoard);

        for (i = 0; i < W; i++)
        {
            free(stackBoard[i]);
        }
        free(stackBoard);
    }*/

    

    freeAlocatedBoard(board);
    
    return EXIT_SUCCESS;
}

void solve(int** board)
{
    node* stack=NULL; // important that is NULL
    int** stack_board, **new_board;
    int arr[N][N][10],i,j,k, empty,ans, solved=0;

    /*do
    {
        initializeArrWithOnes(arr);
        giveArrayPossibilities(board, arr);
    }while(writeDigitIfOnePossibility(board, arr)==1);

    stack_board=copyBoard(board);
    addToStack(&stack,stack_board);
    stack_board=deleteLastStack(&stack);
    freeAlocatedBoard(stack_board);
    stack_board=deleteLastStack(&stack);
    freeAlocatedBoard(stack_board);*/

    stack_board=copyBoard(board);
    addToStack(&stack,stack_board);

    int num=0;
    while((stack_board=deleteLastStack(&stack))!=NULL)
    {
        if(check(stack_board)==0)
        {
            freeAlocatedBoard(stack_board);
            continue;
        } 

        do
        {
            initializeArrWithOnes(arr);
            giveArrayPossibilities(stack_board, arr);
        }while (writeDigitIfOnePossibility(stack_board, arr) == 1);

        initializeArrWithOnes(arr);
        giveArrayPossibilities(stack_board, arr);
        //printBoardOfPossibilities(arr);
        
        // add new possibilities to stack
        
        empty=1;
        for(i=0; i<N; i++)
        {
            for(j=0; j<N; j++)
            {
                for(k=1; k<10; k++)
                {
                    if(arr[i][j][k]!=0)
                    {
                        empty=0;
                        new_board=copyBoard(stack_board);
                        new_board[i][j]=k;
                        //printf("%d %d\n",i,j);
                        //printBoard2(new_board);
                        addToStack(&stack,new_board);
                    }
                }
                if(empty==0)
                    break;
            }
            if(empty==0)
                    break;
        }
        num++;
        if(num==20)
        {
            //exit(0);
        }
            
        //printf("next\n");
        if(empty==1)
        {
            ans=check(stack_board);
            if(ans==1)
            {
                if(just_count_how_many_is_solutions==1)
                {
                    solved++;
                    if(solved%1000==0)
                        printf("%d ",solved);
                    if(solved%10000==0)
                        printf("\n");
                }
                if(just_count_how_many_is_solutions==0)
                    printBoard(stack_board);
                if(show_all_solutions==0)
                {
                    freeAlocatedBoard(stack_board);
                    while((stack_board=deleteLastStack(&stack))!=NULL)
                        freeAlocatedBoard(stack_board);
                    return;
                }
            }
                
            
        }

        // free memory of board taken from stack
        freeAlocatedBoard(stack_board);
    }
}

void freeAlocatedBoard(int** board)
{
    if(board==NULL) return;
    int i;
    for (i = 0; i < W; i++)
    {
        free(board[i]);
    }
    free(board);
}

void usage()
{
    fprintf(stderr, "USAGE: [-a] [file_path]\n");
    exit(EXIT_FAILURE);
}
void printBoard(int** board)
{
    int i, j;
    for (i = 0; i < N; i++)
    {
        if (i % 3 == 0)
            printf("+++++++++++++++++++++++++++++++++++++\n");
        else
            printf("+---+---+---+---+---+---+---+---+---+\n");

        for (j = 0; j < N; j++)
        {
            if (board[i][j] == 0)
            {
                if (j % 3 == 0)
                    printf("+   ");
                else
                    printf("|   ");
                continue;
            }
            if (j % 3 == 0)
                printf("+ %d ", board[i][j]);
            else
                printf("| %d ", board[i][j]);
        }
        printf("+\n");
    }
    printf("+++++++++++++++++++++++++++++++++++++\n");
}
void printBoard2(int** board)
{
    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (board[i][j] != 0)
                printf("%d ", board[i][j]);
            else
                printf("  ");
        }
        printf("\n");
    }
    printf("\n");
}
void printBoardOfPossibilities(int arr[N][N][10])
{
    int i, j, k;
    for (i = 0; i < N; i++)
    {
        printf(
            "+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+---------"
            "--"
            "+\n");
        printf(
            "|           |           |           |           |           |           |           |           |         "
            "  "
            "|\n");
        for (j = 0; j < N; j++)
        {
            printf("| ");
            for (k = 1; k < 10; k++)
            {
                if (arr[i][j][k] == 1)
                {
                    printf("%d", k);
                }
                else
                {
                    printf(" ");
                }
            }
            printf(" ");
        }
        printf("|\n");
        printf(
            "|           |           |           |           |           |           |           |           |         "
            "  "
            "|\n");
    }
    printf(
        "+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+"
        "\n");
}

int** readBoardFromFile(char* file_path)
{
    struct stat statbuf;
    int ch, index = 0,i,j, **board;

    // initialize board
    if((board = (int**)malloc((sizeof(int*) * N)))==NULL) return NULL;
    for(i=0; i<N; i++)
        if((board[i]= (int*)malloc(sizeof(int) * N))==NULL) return NULL;
        
    if (stat(file_path, &statbuf) == -1)
    {
        if (errno == ENOENT)
            ERR("file doesn't exists");
        ERR("errror during checking file");
    }
    if (!S_ISREG(statbuf.st_mode))
        ERR("not regular file");

    FILE* file;
    file = fopen(file_path, "r");
    if (file == NULL)
        ERR("error in opening file");
    // Reading file
    while ((ch = fgetc(file)) != EOF)
    {
        if (index >= W * C)
            break;
        if (ch == '\n')
            continue;
        if (!(ch - '0' >= 0 && ch - '0' <= 9))
            continue;
        board[index / W][index % C] = ch - '0';
        index++;
    }
    // closing file
    if (fclose(file) != 0)
        ERR("file close");
    return board;
}
int** readBoardFromConsole()
{
    int c, index = 0,i,**board;
    if((board = (int**)malloc((sizeof(int*) * N)))==NULL) return NULL;
    for(i=0; i<N; i++)
        if((board[i]= (int*)malloc(sizeof(int) * N))==NULL) return NULL;
    
    printf("Reading board from console...\n");
    while ((c = fgetc(stdin)) != EOF)
    {
        if (index >= W * C)
            break;
        if (c == EOF)
            ERR("error in reading board from console");
        if (!(c - '0' >= 0 && c - '0' <= 9))
            continue;
        board[index / W][index % C] = c - '0';
        index++;
    }
    return board;
}
