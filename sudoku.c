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
int just_count_how_many_is_solutions = 0;

int main(int argc, char* argv[])
{
    int option;
    char* file_path = NULL;
    int** board;

    // reading arguments to program
    printf("\nProgram options: \n");
    while ((option = getopt(argc, argv, "ac")) != -1)
    {
        switch (option)
        {
            case 'a':
                printf("option: show all solutions\n");
                show_all_solutions = 1;
                break;
            case 'c':
                printf("option: just count posible solutions\n");
                just_count_how_many_is_solutions = 1;
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
        board = readBoardFromFile(file_path);
    else
        board = readBoardFromConsole();

    printf("\nLoaded Board: \n");
    printBoard(board);

    // solving sudoku
    printf("\n\nSolved sudoku: \n");
    solve(board);

    freeAlocatedBoard(board);

    return EXIT_SUCCESS;
}

void solve(int** board)
{
    node* stack = NULL;  // important that is NULL
    int **stack_board, **new_board;
    int arr[N][N][10], i, j, k, empty, ans, solved = 0;

    stack_board = copyBoard(board);
    addToStack(&stack, stack_board);

    // we solving until stack is empty
    while ((stack_board = deleteLastStack(&stack)) != NULL)
    {
        // checking if board is correct
        if (check(stack_board) == 0)
        {
            freeAlocatedBoard(stack_board);
            continue;
        }

        // writing to board digits that are only posibility
        do
        {
            initializeArrWithOnes(arr);
            giveArrayPossibilities(stack_board, arr);
        } while (writeDigitIfOnePossibility(stack_board, arr) == 1);

        // now we have situations where is posssible to write to all remained fields at least two digits
        // so we write first posibility and add it to stack and write second and add to stack.
        // for example in field (1,1) we can write 3 and 5 and in field (2,8) we can write 3,5,6 so we copy board
        // and write in position (1,1) 3 and add it to stack and then we copy board and wwrite in position (1,1) 5 and
        // we exit for
        empty = 1;
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                for (k = 1; k < 10; k++)
                {
                    if (arr[i][j][k] != 0)
                    {
                        empty = 0;
                        new_board = copyBoard(stack_board);
                        new_board[i][j] = k;
                        addToStack(&stack, new_board);
                    }
                }
                if (empty == 0)
                    break;
            }
            if (empty == 0)
                break;
        }

        // we can not write anything to board
        if (empty == 1)
        {
            // so we check if board is correct
            if (check(stack_board) == 1)
            {
                solved++;  // board is correct
                if (just_count_how_many_is_solutions == 1)
                {
                    printf(".");
                    if (solved % 10 == 0)
                        printf(" (%d)\n", solved);
                }
                else if (just_count_how_many_is_solutions == 0)
                    printBoard(stack_board);

                // user want just to write one solution so we have to free alocated memory on stack and we exit
                if (show_all_solutions == 0)
                {
                    freeAlocatedBoard(stack_board);
                    while ((stack_board = deleteLastStack(&stack)) != NULL)
                        freeAlocatedBoard(stack_board);
                    printf("\nNumber of solutions: %d\n", solved);
                    return;
                }
            }
        }

        // free memory of board taken from stack
        freeAlocatedBoard(stack_board);
    }

    printf("\nNumber of solutions: %d\n", solved);
}

void freeAlocatedBoard(int** board)
{
    if (board == NULL)
        return;
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
    int ch, index = 0, i, j, **board;

    // initialize board
    if ((board = (int**)malloc((sizeof(int*) * N))) == NULL)
        return NULL;
    for (i = 0; i < N; i++)
        if ((board[i] = (int*)malloc(sizeof(int) * N)) == NULL)
            return NULL;

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
    int c, index = 0, i, **board;
    if ((board = (int**)malloc((sizeof(int*) * N))) == NULL)
        return NULL;
    for (i = 0; i < N; i++)
        if ((board[i] = (int*)malloc(sizeof(int) * N)) == NULL)
            return NULL;

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
