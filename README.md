# sudoku-solver

This program solve sudoku. It is wriiten in C in POSIX standard. 

## Installation

To install this project, follow these steps:

1. Clone the repository:

    ```bash
    git clone https://github.com/pietraldo/sudoku-solver.git
    ```

2. Navigate to the project directory:

    ```bash
    cd sudoku-solver
    ```

3. Make binary file

    ```bash
    make prog
    ```

## Usage

To use this project, run the following command:
 ```bash
 ./prog
  ```
You can load sudoku board from file
 ```bash
 ./prog someExampleBoards/board1
  ```
If you want to program write all posible solutions, add flag a
 ```bash
 ./prog someExampleBoards/board1 -a
  ```
If you want to program count all posible solutions, add flag a and flag c
 ```bash
 ./prog someExampleBoards/board1 -a -c
  ```
You can also give a empty sudoku board (contains 81 zeros) and program will start write
all posible sudokus
 ```bash
 ./prog someExampleBoards/empty -a 
  ```
## Boards

Sudoku boards must be in this format
 ```bash
308504900
900000020
000100000
060000007
005908200
000030000
000010400
003020000
050403060
  ```
