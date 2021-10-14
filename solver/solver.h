#ifndef SOLVER_H
#define SOLVER_H

void PrintSudoku(char sudoku[9][9]);

int AlreadyInLine(char sudoku[9][9], unsigned y, char val);

int AlreadyInColumn(char sudoku[9][9], unsigned x, char val);

int AlreadyInSquare(char soduku[9][9], unsigned x, unsigned y, char val);

void Solve(char sudoku[9][9]);
